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
#include "CFlexibleSwing.hpp"
#include "CSpringSwing.hpp"

// =============================================================================
// Static variables
// -----------------------------------------------------------------------------
static CVector2f sJumpVelocity = CVector2f(0.0f, -250.0f);

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
    thePoints.push_back(CVector2f(-mSmallestRadius, -mSmallestRadius));
    thePoints.push_back(CVector2f(mSmallestRadius,  -mSmallestRadius));
    thePoints.push_back(CVector2f(mSmallestRadius,  mSmallestRadius));
    thePoints.push_back(CVector2f(-mSmallestRadius, mSmallestRadius));
    
    SetShape(CConvexShape(thePoints));
    GetShape()->setFillColor(CColour(255, 0, 255));
    
    float mass = 1.0f; // Read from file?
    SetInverseMass(1.0f / mass);
}

CPlayer::~CPlayer()
{
    
}

// =============================================================================
// CPlayer::Update
// -----------------------------------------------------------------------------
void CPlayer::Update(CTime elapsedTime)
{
    HandleInput();
    
    // Now simulate the physics until we've simulated the entire elapsedTime
    while (elapsedTime > CTime::Zero)
    {
        // Find the acceleration applied by any physics items
        CVector2f acceleration = HandlePhysics();
        
        // Now try to move based on our velocity
        CTime timeSimulated = MoveUntilCollision(elapsedTime, acceleration);
        elapsedTime -= timeSimulated;
    }
}

// =============================================================================
// CPlayer::ShouldUpdateForState
// -----------------------------------------------------------------------------
bool CPlayer::ShouldUpdateForState(EGameState theState)
{
    // Only update if we're not paused
    if ((theState & kGameStatePaused) != 0)
    {
        return false;
    }
    
    return CUpdateable::ShouldUpdateForState(theState);
}

// =============================================================================
// CPlayer::Draw
// -----------------------------------------------------------------------------
void CPlayer::Draw(CWindow *theWindow)
{
    // Colour the player by the colour of the swing we will fire
    GetShape()->setFillColor(mSwings[mSwingToFire]->GetColour());
    theWindow->DrawShape(*GetShape());
}

// =============================================================================
// CPlayer::Init
// -----------------------------------------------------------------------------
void CPlayer::Init()
{
    // Register any update/renderables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterRenderable(this);
    
    mSwings[kSwingTypeRigid] = new CSwing(this, mParentLevel);
    mSwings[kSwingTypeFlexible] = new CFlexibleSwing(this, mParentLevel);
    mSwings[kSwingTypeSpring] = new CSpringSwing(this, mParentLevel);
}

// =============================================================================
// CPlayer::Cleanup
// -----------------------------------------------------------------------------
void CPlayer::Cleanup()
{
    SAFE_DELETE(mSwings[kSwingTypeRigid]);
    SAFE_DELETE(mSwings[kSwingTypeFlexible]);
    SAFE_DELETE(mSwings[kSwingTypeSpring]);
    
    // Unregister update/renderables
    CSwingGame::UnregisterUpdateable(this);
    CSwingGame::UnregisterRenderable(this);
}

// =============================================================================
// CPlayer::StartLevel
// -----------------------------------------------------------------------------
void CPlayer::StartLevel(SStartPosition theStartPos)
{
    GetShape()->setPosition(theStartPos.mPosition);
    SetVelocity(theStartPos.mVelocity);
    
    for (int i = 0; i < kSwingTypeMax; i++)
    {
        mSwings[i]->Detach();
    }
    
    mSwingToFire = kSwingTypeRigid;
    mCurrentSwing = mSwings[mSwingToFire];
    
    mCurrentSwing->AttemptToAttach(theStartPos.mSwingTarget);
}

// =============================================================================
// CPlayer::HandleInput
// -----------------------------------------------------------------------------
void CPlayer::HandleInput()
{
#if SG_DEBUG    // In debug move the player to the mouse pos if r shift is down
    if (CKeyboard::isKeyPressed(CKeyboard::RShift))
    {
        GetShape()->setPosition(SystemUtilities::GetMousePosition());
        HandleCollisions();
        
        // Reset velocity
        SetVelocity(CVector2f(0.0f, 0.0f));
    }
#endif
    
    // Connect the swing on left mouse click
    CVector2f mousePos;
    if (SystemUtilities::WasButtonPressedThisCycle(CMouse::Left, &mousePos))
    {
        // Detach the current swing before we try to fire the next
        mCurrentSwing->Detach();
        
        // Update the current swing type and try to attach it
        mCurrentSwing = mSwings[mSwingToFire];
        mCurrentSwing->AttemptToAttach(mousePos);
    }
    
    // Disconnect on right click
    if (SystemUtilities::WasButtonPressedThisCycle(CMouse::Right, &mousePos))
    {
        // We specifically requested this detach so respond to it
        mCurrentSwing->Detach(true);
    }
    
    // Jump on space
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Space))
    {
        // Only jump if we're attached to a swing, and detach it when we do
        if (mCurrentSwing->IsAttached())
        {
            mCurrentSwing->Detach();
            SetVelocity(GetVelocity() + sJumpVelocity);
        }
    }
    
    // Change swing type
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Num1))
    {
        mSwingToFire = kSwingTypeRigid;
    }
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Num2))
    {
        mSwingToFire = kSwingTypeFlexible;
    }
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Num3))
    {
        mSwingToFire = kSwingTypeSpring;
    }
}

// =============================================================================
// CPlayer::HandlePhysics
// Return the resulting acceleration of the player
// -----------------------------------------------------------------------------
CVector2f CPlayer::HandlePhysics()
{
    CVector2f acceleration = mParentLevel->GetGravityAcceleration();
    
    acceleration = mCurrentSwing->AttenuateGravity(acceleration);
    
    return acceleration;
}

// =============================================================================
// CPlayer::HandleCollisions
// Return true if we resolved a collision
// -----------------------------------------------------------------------------
bool CPlayer::HandleCollisions(bool shouldResolve /* = false */)
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
            
            if (shouldResolve)
            {
                // Resolve the collision
                CollisionHandler::Resolve(this, (*it), correctionVector);
            }
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
    
    // If we don't need to move bail out
    if (totalDistance == 0)
    {
        return elapsedTime;
    }
    
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

// =============================================================================
// CPlayer::MoveFixedDistanceUntilCollision
// -----------------------------------------------------------------------------
void CPlayer::MoveFixedDistanceUntilCollision(CVector2f offset)
{
    // Find out how far we want to move
    CVector2f totalOffset = offset;
    float totalDistance = totalOffset.GetMagnitude();
    
    // Break it down into a number of smaller offsets
    int numSteps = ceil(totalDistance / mSmallestRadius);
    CVector2f smallOffset = totalOffset / (numSteps * 1.0f);
    
    // Apply these until we collide
    bool haveCollided = false;
    for (int i = 0; i < numSteps && !haveCollided; i++)
    {
        // Move by the small offset
        GetShape()->move(smallOffset);
        haveCollided = HandleCollisions();
    }
}

// =============================================================================
// CPlayer::IsColliding
// -----------------------------------------------------------------------------
bool CPlayer::IsColliding()
{
    // Let HandleCollisions do this check
    return HandleCollisions(false);
}