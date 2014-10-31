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

// =============================================================================
// CSwing constructor/destructor
// -----------------------------------------------------------------------------
CSwing::CSwing(CPhysicsBody *theBob) :  mBob(theBob),
                                        mAttached(false)
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
    theWindow->DrawLine(mBob->GetPosition(), mOrigin);
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
    // For now just say the aim point is valid
    *anchor = theAimPoint;
    return true;
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