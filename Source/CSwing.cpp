//
//  CSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "CollisionHandler.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
float CSwing::smMaxLength = 500.0f;
float CSwing::smMinLength = 25.0f;
float CSwing::smClimbSpeed = 100.0f;
float CSwing::smCollisionIgnoreDistance = 1.0f;
float CSwing::smAnchorGap = 5.0f;
float CSwing::smReflectionScaleFactor = -1.0f;

// =============================================================================
// CSwing constructor/destructor
// -----------------------------------------------------------------------------
CSwing::CSwing(CPlayer *theBob, CLevel *theParentLevel)
:   mBob(theBob),
    mParentLevel(theParentLevel),
    mAttached(false),
    mColour(CColour::Black)
{
    
}

CSwing::~CSwing()
{
    // Unregister this x-able
    if (mAttached)
    {
        CSwingGame::UnregisterRenderable(this);
        CSwingGame::UnregisterUpdateable(this);
    }
}

// =============================================================================
// CSwing::AttemptToAttach
// Find the first point between the bob and the aim point to attach to
// -----------------------------------------------------------------------------
void CSwing::AttemptToAttach(CVector2f theAimPoint)
{
    // Attach the swing if we can find a valid anchor point
    CVector2f anchorPoint;
    if (IsThereAValidAnchor(theAimPoint, &anchorPoint))
    {
        // Make sure we detach from any existing swing
        Detach();
        
        // Now attach
        mAttached = true;
        
        mOrigin = anchorPoint;
        mOriginDrawPoint = mOrigin;
        mLength = GetDistanceToBob();
        
        RespondToAttach();
        
        // Register ourselves now we're active
        CSwingGame::RegisterRenderable(this);
        CSwingGame::RegisterUpdateable(this);
    }
}

// =============================================================================
// CSwing::Detach
// -----------------------------------------------------------------------------
void CSwing::Detach(bool shouldRespond /* = false */)
{
    if (mAttached)
    {
        mAttached = false;
        CSwingGame::UnregisterUpdateable(this);
        CSwingGame::UnregisterRenderable(this);
        
        if (shouldRespond)
        {
            RespondToDetach();
        }
    }
}

// =============================================================================
// CSwing::AttenuateGravity
// Alter the affect of gravity based on the swings angle
// -----------------------------------------------------------------------------
CVector2f CSwing::AttenuateGravity(CVector2f gravity)
{
    // If we're not attached then don't affect gravity
    if (!mAttached)
    {
        return gravity;
    }
    
    // Throw away any component of the gravity that isn't perpendicular to the
    // swing
    return gravity.GetComponentInDirection(GetPerpendicularDirection());
}

// =============================================================================
// CSwing::Draw
// -----------------------------------------------------------------------------
void CSwing::Draw(CWindow *theWindow)
{
    // The line
    DrawSwingSection(theWindow, mOrigin, mBob->GetPosition());
    
    // The anchor
    DrawAnchorPoint(theWindow, mOriginDrawPoint);
}

// =============================================================================
// CSwing::Update
// -----------------------------------------------------------------------------
void CSwing::Update(CTime elapsedTime)
{
    if (mAttached)
    {
        HandleInput(elapsedTime);
        
        // Adjust the velocity so it is perpendicular to the swing
        CVector2f v = mBob->GetVelocity();
        CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
        newV.Normalise();
        newV *= v.GetMagnitude();
        mBob->SetVelocity(newV);
        
        // Make sure the bob isn't further away from the origin than the length
        // of the swing
        CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
        float distance = bobToOrigin.GetMagnitude();
        if (distance != mLength)
        {
            // Move by the difference between the distance and length
            float moveDistance = distance - mLength;
            bobToOrigin.Normalise();
            bobToOrigin *= moveDistance;
            mBob->MoveFixedDistanceUntilCollision(bobToOrigin);
        }
        
        HandleCollisions();
    }
}

// =============================================================================
// CSwing::ShouldUpdateForGameState
// -----------------------------------------------------------------------------
bool CSwing::ShouldUpdateForState(EGameState theState)
{
    // Only update if we're not paused
    if ((theState & kGameStatePaused) != 0)
    {
        return false;
    }
    
    return CUpdateable::ShouldUpdateForState(theState);
}

// =============================================================================
// CSwing::CanJumpFrom
// -----------------------------------------------------------------------------
bool CSwing::CanJumpFrom()
{
    // Most swings can't be jumped from
    return false;
}

// =============================================================================
// CSwing::IsAttached
// -----------------------------------------------------------------------------
bool CSwing::IsAttached()
{
    return mAttached;
}

// =============================================================================
// CSwing::GetColour
// -----------------------------------------------------------------------------
CColour CSwing::GetColour()
{
    return mColour;
}

// =============================================================================
// CSwing::GetDistanceToBob
// -----------------------------------------------------------------------------
float CSwing::GetDistanceToBob()
{
    CVector2f bobPosition = mBob->GetPosition();
    CVector2f bobToOrigin = mOrigin - bobPosition;
    return bobToOrigin.GetMagnitude();
}

// =============================================================================
// CSwing::IsThereAValidAnchor
// -----------------------------------------------------------------------------
bool CSwing::IsThereAValidAnchor(CVector2f theAimPoint, CVector2f *anchor)
{
    bool validPointFound = false;
    
    // Find the direction from the bob to the aim point
    CVector2f bobPosition = mBob->GetPosition();
    CVector2f aimDirection = theAimPoint - bobPosition;
    aimDirection.Normalise();
    
    // Now start at the minimum swing length and sample at each unit point
    // along the possible rope points until we reach the max swing length
    // At each point see if an anchor collides with any obstacles
    // As soon as it collides this is the anchor point
    float currentLength = smMinLength;
    CVector2f currentSamplePoint = bobPosition + (aimDirection * currentLength);
    CCircleShape anchorShape(smAnchorGap);
    std::list<CPhysicsBody *> obstacles = mParentLevel->GetObstacles();
    CVector2f cv;
    
    while (!validPointFound && currentLength <= smMaxLength)
    {
        anchorShape.setPosition(currentSamplePoint);
        FOR_EACH_IN_LIST(CPhysicsBody*, obstacles)
        {
            CConvexShape obstacleShape = *((*it)->GetShape());
            if (CollisionHandler::AreColliding(anchorShape, obstacleShape, &cv))
            {
                validPointFound = true;
                anchor->x = currentSamplePoint.x;
                anchor->y = currentSamplePoint.y;
            }
        }
        
        // Now move to the next sample point
        currentLength += 1.0f;
        currentSamplePoint += aimDirection;
    }
    
    return validPointFound;
}

// =============================================================================
// CSwing::GetPerpendicularDirection
// -----------------------------------------------------------------------------
CVector2f CSwing::GetPerpendicularDirection()
{
    CVector2f originToBob = mBob->GetPosition() - mOrigin;
    originToBob.Normalise();
    
    CVector2f perpendicularDirection;
    perpendicularDirection.x = originToBob.y;
    perpendicularDirection.y = -originToBob.x;
    
    return perpendicularDirection;
}

// =============================================================================
// CSwing::HandleInput
// -----------------------------------------------------------------------------
void CSwing::HandleInput(CTime elapsedTime)
{
    CVector2f climbOffset = CVector2f(0.0f, 0.0f);
    CVector2f climbDirection = mOrigin - mBob->GetPosition();
    climbDirection.Normalise();
    
    // Climb while w is pressed
    if (CKeyboard::isKeyPressed(CKeyboard::W))
    {
        climbOffset += climbDirection * smClimbSpeed * elapsedTime.asSeconds();
    }
    
    // Descend while s is presses
    if (CKeyboard::isKeyPressed(CKeyboard::S))
    {
        climbOffset -= climbDirection * smClimbSpeed * elapsedTime.asSeconds();
    }
    
    if (climbOffset .GetMagnitude() > 0)
    {
        mBob->MoveFixedDistanceUntilCollision(climbOffset);
        mLength = GetDistanceToBob();
        mLength = std::min(mLength, smMaxLength);
        mLength = std::max(mLength, smMinLength);
    }
}

// =============================================================================
// CSwing::HandleCollisions
// -----------------------------------------------------------------------------
void CSwing::HandleCollisions()
{
    // Keep track of the closest intersection to the origin we care about
    bool validIntersectionFound = false;
    float distanceToClosestIntersection = smMaxLength;
    CVector2f closestIntersection;
    
    // Check for collisions with all obstacles in the level
    CLine theLine = CLine(mOrigin, mBob->GetPosition());
    std::list<CPhysicsBody *> theObstacles = mParentLevel->GetObstacles();
    FOR_EACH_IN_LIST(CPhysicsBody*, theObstacles)
    {
        CPhysicsBody *theObs = (*it);
        CConvexShape theShape = *(theObs->GetShape());
        
        std::list<CVector2f> theIntPoints;
        if (CollisionHandler::AreIntersecting(theLine, theShape, &theIntPoints))
        {
            FOR_EACH_IN_LIST(CVector2f, theIntPoints)
            {
                CVector2f thisIntersection = (*it);
                CVector2f originToInt = thisIntersection - mOrigin;
                float distanceToThisIntersection = originToInt.GetMagnitude();
                
                if (distanceToThisIntersection > smCollisionIgnoreDistance)
                {
                    validIntersectionFound = true;
                    
                    // Only record this if its closer to the origin
                    if (distanceToThisIntersection < distanceToClosestIntersection)
                    {
                        distanceToClosestIntersection = distanceToThisIntersection;
                        closestIntersection = thisIntersection;
                    }
                }
            }
        }
    }
    
    // If we found a collision we care about then handle it
    if (validIntersectionFound)
    {
        RespondToCollisionAt(closestIntersection);
    }
}

// =============================================================================
// CSwing::DrawAnchorPoint
// -----------------------------------------------------------------------------
void CSwing::DrawAnchorPoint(CWindow *theWindow, CVector2f theAnchor)
{
    CCircleShape theCircle = CCircleShape(smAnchorGap);
    theCircle.setPosition(theAnchor);
    theCircle.setOutlineColor(CColour::Black);
    theCircle.setOutlineThickness(1.0f);
    theCircle.setFillColor(CColour::Transparent);
    theWindow->draw(theCircle);
}


// =============================================================================
// CSwing::DrawSwingSection
// -----------------------------------------------------------------------------
void CSwing::DrawSwingSection(CWindow *theWindow,
                              CVector2f start,
                              CVector2f end)
{
    theWindow->DrawLine(CLine(start, end), mColour);
}

// =============================================================================
// CSwing::RespondToAttach
// -----------------------------------------------------------------------------
void CSwing::RespondToAttach()
{
    // Throw away any velocity that isn't perpendicular to the swing
    CVector2f v = mBob->GetVelocity();
    CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
    mBob->SetVelocity(newV);
}

// =============================================================================
// CSwing::RespondToDetach
// -----------------------------------------------------------------------------
void CSwing::RespondToDetach()
{
    // Do nothing for the basic swing type
}

// =============================================================================
// CSwing::RespondToCollisionAt
// -----------------------------------------------------------------------------
void CSwing::RespondToCollisionAt(CVector2f intersectionPoint)
{
    // Seperate the swing and the obstacle
    AdjustDirectionToGoThrough(intersectionPoint);
    
    // For this rigid swing we'll just reflect the players velocity
    // Apply a scaling factor as well so we can dampen it
    mBob->SetVelocity(mBob->GetVelocity() * smReflectionScaleFactor);
}

// =============================================================================
// CSwing::AdjustDirectionToGoThrough
// -----------------------------------------------------------------------------
void CSwing::AdjustDirectionToGoThrough(CVector2f targetPoint)
{
    CVector2f originToTarget = targetPoint - mOrigin;
    originToTarget.Normalise();
    originToTarget *= mLength;
    
    CVector2f newBobPosition = mOrigin + originToTarget;
    mBob->SetPosition(newBobPosition);
}