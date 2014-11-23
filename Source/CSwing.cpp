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
// CSwing constructor/destructor
// -----------------------------------------------------------------------------
CSwing::CSwing(CPhysicsBody *theBob, CLevel *theParentLevel)
:   mBob(theBob),
    mParentLevel(theParentLevel),
    mAttached(false),
    mMaxLength(500.0f)
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
        mLength = GetDistanceToBob();
        
        // Throw away any velocity that isn't perpendicular to the swing
        CVector2f v = mBob->GetVelocity();
        CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
        mBob->SetVelocity(newV);
        
        // Register ourselves now we're active
        CSwingGame::RegisterRenderable(this);
        CSwingGame::RegisterUpdateable(this);
    }
}

// =============================================================================
// CSwing::Detach
// -----------------------------------------------------------------------------
void CSwing::Detach()
{
    if (mAttached)
    {
        mAttached = false;
        CSwingGame::UnregisterUpdateable(this);
        CSwingGame::UnregisterRenderable(this);
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
    theWindow->DrawLine(mBob->GetPosition(), mOrigin, CColour::Black);
}

// =============================================================================
// CSwing::Update
// -----------------------------------------------------------------------------
void CSwing::Update(CTime elapsedTime)
{
    // Adjust the velocity so it is perpendicular to the swing
    CVector2f v = mBob->GetVelocity();
    CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
    newV.Normalise();
    newV *= v.GetMagnitude();
    mBob->SetVelocity(newV);
    
    // Make sure the bob isn't further away from the origin than the length of
    // the swing
    CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
    float distance = bobToOrigin.GetMagnitude();
    if (distance > mLength)
    {
        // Move by the difference between the distance and length
        float moveDistance = distance - mLength;
        bobToOrigin.Normalise();
        bobToOrigin *= moveDistance;
        mBob->GetShape()->move(bobToOrigin);
    }
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
    bool theResult = false;
    
    // Find the direction from the bob to the aim point
    CVector2f bobPosition = mBob->GetPosition();
    CVector2f aimDirection = theAimPoint - bobPosition;
    aimDirection.Normalise();
    
    // Create a line from the bob to the max distance away that a swing could
    // reach in the aim direction
    CLine longestPossile = CLine(bobPosition,
                                 bobPosition + (aimDirection * mMaxLength));
    
    // Find the closest intersection of this line and any obstacle lines to the
    // bob
    *anchor = longestPossile.GetEnd();
    float currentDistanceToAnchor = mMaxLength;
    
    std::list<CPhysicsBody *> theObstacles = mParentLevel->GetObstacles();
    FOR_EACH_IN_LIST(CPhysicsBody*, theObstacles)
    {
        std::list<CVector2f> theIntersections;
        if (CollisionHandler::AreIntersecting(longestPossile,
                                              *((*it)->GetShape()),
                                              &theIntersections))
        {
            theResult = true;
            FOR_EACH_IN_LIST(CVector2f, theIntersections)
            {
                CVector2f thisIntersection = (*it);
                CVector2f bobToThis = thisIntersection - bobPosition;
                float distanceToThis = bobToThis.GetMagnitude();
                if (distanceToThis < currentDistanceToAnchor)
                {
                    *anchor = thisIntersection;
                    currentDistanceToAnchor = distanceToThis;
                }
            }
        }
    }
    
    return theResult;
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