//
//  CSpringSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 07/12/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSpringSwing.hpp"
#include "CPlayer.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
float CSpringSwing::smMinStretchFactor = 1.0f;
float CSpringSwing::smMaxStretchFactor = 7.5f;
float CSpringSwing::smLaunchMultiplier = 500.0f;


// =============================================================================
// CSpringSwing constructor/destructor
// -----------------------------------------------------------------------------
CSpringSwing::CSpringSwing(CPlayer *theBob, CLevel *theParentLevel)
:   CSwing(theBob, theParentLevel)
{
    // Make it purpley
    mColour = CColour(135, 38, 87);
}

CSpringSwing::~CSpringSwing()
{
    
}

// =============================================================================
// CSpringSwing::AttemptToAttach
// -----------------------------------------------------------------------------
void CSpringSwing::AttemptToAttach(CVector2f theAimPoint)
{
    // Call the parent method
    CSwing::AttemptToAttach(theAimPoint);
    
    // Remember the original length
    mOriginalLength = mLength;
}

// =============================================================================
// CSpringSwing::AttenuateGravity
// -----------------------------------------------------------------------------
CVector2f CSpringSwing::AttenuateGravity(CVector2f gravity)
{
    // Don't alter gravity
    return gravity;
}

// =============================================================================
// CSpringSwing::Update
// -----------------------------------------------------------------------------
void CSpringSwing::Update(CTime elapsedTime)
{
    if (mAttached)
    {
        // Update the length
        mLength = GetDistanceToBob();
        
        HandleInput(elapsedTime);
        HandleCollisions();
    }
}

// =============================================================================
// CSpringSwing::HandleInput
// -----------------------------------------------------------------------------
void CSpringSwing::HandleInput(CTime elapsedTime)
{
    // Do nothing
}

// =============================================================================
// CSpringSwing::RespondToAttach
// -----------------------------------------------------------------------------
void CSpringSwing::RespondToAttach()
{
    // Do nothing
}

// =============================================================================
// CSpringSwing::RespondToDetach
// -----------------------------------------------------------------------------
void CSpringSwing::RespondToDetach()
{
    // Shoot the player off towards the origin with a velocity related to how
    // far the spring has stretched
    CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
    bobToOrigin.Normalise();
    
    float finalLength = GetDistanceToBob();
    float stretchedFactor = finalLength / mOriginalLength;
    stretchedFactor = std::min(stretchedFactor, smMaxStretchFactor);
    
    // Only apply the springyness if we were stretched enough
    if (stretchedFactor >= smMinStretchFactor)
    {
        CVector2f launchVel = bobToOrigin * smLaunchMultiplier * stretchedFactor;
        mBob->SetVelocity(launchVel + mBob->GetVelocity());
    }
}

// =============================================================================
// CSpringSwing::RespondToCollisionAt
// -----------------------------------------------------------------------------
void CSpringSwing::RespondToCollisionAt(CVector2f intersectionPoint)
{
    // Break on collision
    Detach();
}