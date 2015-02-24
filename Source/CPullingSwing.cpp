//
//  CPullingSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 24/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CPullingSwing.hpp"
#include "CPlayer.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
float CPullingSwing::smPullSpeedIncrement = 450.0f;
float CPullingSwing::smPullSpeedMax = 500.0f;
float CPullingSwing::smDetachLength = CSwing::smMinLength;

// =============================================================================
// CPullingSwing constructor/destructor
// -----------------------------------------------------------------------------
CPullingSwing::CPullingSwing(CPlayer *theBob, CLevel *theParentLevel)
:   CSwing(theBob, theParentLevel)
{
    // Make it blue
    mColour = CColour::Blue;
}

CPullingSwing::~CPullingSwing()
{
    
}

// =============================================================================
// CPullingSwing::Update
// -----------------------------------------------------------------------------
void CPullingSwing::Update(CTime elapsedTime)
{
    if (mAttached)
    {
        // Update the length since the player will be closer now
        mLength = GetDistanceToBob();
        
        // Detach the player if they are close enough
        if (mLength <= smDetachLength)
        {
            Detach();
        }
        else
        {
            // Make sure the players velocity is towards the origin
            CVector2f v = mBob->GetVelocity();
            CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
            bobToOrigin.Normalise();
            v = v.GetComponentInDirection(bobToOrigin);
            
            // Accelerate the player towards the origin
            float timedInc = smPullSpeedIncrement * elapsedTime.asSeconds();
            CVector2f newV = v + (bobToOrigin * timedInc);
            
            // Clamp the new velocity
            if (newV.GetMagnitude() > smPullSpeedMax)
            {
                newV = bobToOrigin * smPullSpeedMax;
            }
            
            mBob->SetVelocity(newV);
        }
    }
}

// =============================================================================
// CPullingSwing::AttenuateGravity
// -----------------------------------------------------------------------------
CVector2f CPullingSwing::AttenuateGravity(CVector2f gravity)
{
    // Have no gravity when on this swing
    if (mAttached)
    {
        gravity = CVector2f(0.0f, 0.0f);
    }
    
    return gravity;
}

// =============================================================================
// CPullingSwing::RespondToAttach
// -----------------------------------------------------------------------------
void CPullingSwing::RespondToAttach()
{
    // Throw away all player velocity, we'll give them a vel towards the origin
    // in update
    mBob->SetVelocity(CVector2f(0.0f, 0.0f));
}