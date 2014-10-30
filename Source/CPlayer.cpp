//
//  CPlayer.cpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"
#include "CPlayer.hpp"
#include "SystemUtilities.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "CLine.hpp"
#include "CollisionHandler.hpp"

// =============================================================================
// SUVAT Helper Methods
// -----------------------------------------------------------------------------
CVector2f GetVectorMoved(CVector2f u, CTime t, CVector2f a)
{
    // s = ut + 0.5at^2
    float ts = t.asSeconds();
    return (u * ts) + (0.5f * a * ts * ts);
}

CVector2f GetFinalVelocity(CVector2f u, CVector2f a, CTime t)
{
    // v = u + at
    float ts = t.asSeconds();
    return u + (a * ts);
}

// =============================================================================
// CPlayer constructor/destrctor
// -----------------------------------------------------------------------------
CPlayer::CPlayer(CLevel *theParentLevel) :  mParentLevel(theParentLevel)
{
    // Create the shape
    mSmallestRadius = 10.0f;
    
    std::list<CVector2f> thePoints;
    thePoints.push_back(CVector2f(0.0f,                 0.0f));
    thePoints.push_back(CVector2f(2 * mSmallestRadius,  0.0f));
    thePoints.push_back(CVector2f(2 * mSmallestRadius,  2 * mSmallestRadius));
    thePoints.push_back(CVector2f(0.0f,                 2 * mSmallestRadius));
    
    SetShape(CConvexShape(thePoints));
    GetShape()->setFillColor(CColour::Yellow);
    
    SetMass(1.0f); // Read from file?
}

CPlayer::~CPlayer()
{
    
}

// =============================================================================
// CPlayer::Update
// -----------------------------------------------------------------------------
void CPlayer::Update(CTime elapsedTime)
{
    DEBUG_LOG("UPDATE START - elapsedTime: %f", elapsedTime.asSeconds());
    
    HandleInput();
    
    // Now simulate the physics until we've simulated the entire elapsedTime
    while (elapsedTime > CTime::Zero)
    {
        // Find the forces applied by any physics items
        HandlePhysics();
        
        // Find acceleration using f=ma
        CVector2f acceleration = GetForce() / GetMass();
        // And zero the force out now we've applied it
        SetForce(CVector2f(0.0f, 0.0f));
        
        DEBUG_LOG("Attempting to simulate with u=(%f,%f), a=(%f,%f), t=%f",
                  GetVelocity().x, GetVelocity().y,
                  acceleration.x, acceleration.y,
                  elapsedTime.asSeconds());
        
        // Now try to move based on our velocity
        CTime timeSimulated = MoveUntilCollision(elapsedTime, acceleration);
        elapsedTime -= timeSimulated;
        
        DEBUG_LOG("Simulated %f", timeSimulated.asSeconds());
    }
    
    DEBUG_LOG("UPDATE END");
}

// =============================================================================
// CPlayer::Draw
// -----------------------------------------------------------------------------
void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(*GetShape());
}

// =============================================================================
// CPlayer::Init
// -----------------------------------------------------------------------------
void CPlayer::Init(SStartPosition theStartPos)
{
    // Register any update/renderables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterRenderable(this);
    
    GetShape()->setPosition(theStartPos.mPosition);
    SetVelocity(CVector2f(0.0f, 0.0f));
    SetForce(CVector2f(0.0f, 0.0f));
}

// =============================================================================
// CPlayer::Cleanup
// -----------------------------------------------------------------------------
void CPlayer::Cleanup()
{
    // Unregister update/renderables
    CSwingGame::UnregisterUpdateable(this);
    CSwingGame::UnregisterRenderable(this);
}

// =============================================================================
// CPlayer::HandleInput
// -----------------------------------------------------------------------------
void CPlayer::HandleInput()
{
#if SG_DEBUG    // In debug move the player to the mouse pos on left click if
                // right shift is down
    CVector2f mousePos;
    if (SystemUtilities::WasButtonPressedThisCycle(CMouse::Left, &mousePos)
        && CKeyboard::isKeyPressed(CKeyboard::RShift))
    {
        GetShape()->setPosition(SystemUtilities::GetMousePosition());
        HandleCollisions();
        
        // Reset velocity
        SetVelocity(CVector2f(0.0f, 0.0f));
    }
#endif
}

// =============================================================================
// CPlayer::HandlePhysics
// -----------------------------------------------------------------------------
void CPlayer::HandlePhysics()
{
    // Add a downward force from gravity
    ApplyForce(GetMass() * mParentLevel->GetGravityAcceleration());
}

// =============================================================================
// CPlayer::HandleCollisions
// Return true if we resolved a collision
// -----------------------------------------------------------------------------
bool CPlayer::HandleCollisions()
{
    bool didCollide = false;
    
    // Check for collisions against all level obstacles
    std::list<CPhysicsBody *> theObstacles = mParentLevel->GetObstacles();
    
    CVector2f correctionVector;
    FOR_EACH_IN_LIST(CPhysicsBody *, theObstacles)
    {
        if (CollisionHandler::AreColliding(*GetShape(),
                                           *((*it)->GetShape()),
                                           &correctionVector))
        {
            didCollide = true;
            
            // Resolve the collision
            CollisionHandler::Resolve(this, (*it), correctionVector);
        }
    }
    
    return didCollide;
}

// =============================================================================
// CPlayer::MoveUntilCollision
// Move for the given amount of time with the given acceleration or until
// we collide
// Return the time we actually simulated movement for
// -----------------------------------------------------------------------------
CTime CPlayer::MoveUntilCollision(CTime elapsedTime, CVector2f acceleration)
{
    // Find the total offset we've been requested to move
    CVector2f totalOffset;
    totalOffset = GetVectorMoved(GetVelocity(), elapsedTime, acceleration);
    float totalDistance = totalOffset.GetMagnitude();
    
    // Find how many timesteps we should use to make sure we don't move by
    // more than the shapes smallest "radius"
    int numTimesteps = ceil(totalDistance / mSmallestRadius);
    
    // Find how big this timesteps should be
    CTime timeStep = elapsedTime / (numTimesteps * 1.0f);
    
    // Now find how far we should move for each timestep
    CVector2f smallOffset = totalOffset / (numTimesteps * 1.0f);
    
    // And simulate these timesteps until we've done them all or we've collided
    bool haveCollided = false;
    CTime timeSimulatedSoFar = CTime::Zero;
    for (int i = 0; i < numTimesteps && !haveCollided; i++)
    {
        // Update velocity to what it will be at the end of this timestep
        SetVelocity(GetFinalVelocity(GetVelocity(), acceleration, timeStep));
        
        // Now move the shape and handle any collisions
        GetShape()->move(smallOffset);
        haveCollided = HandleCollisions();
        
        timeSimulatedSoFar += timeStep;
    }
    
    return timeSimulatedSoFar;
}