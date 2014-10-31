//
//  CPhysicsBody.cpp
//  SwingGame
//
//  Created by Tim Brier on 30/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CPhysicsBody.hpp"
#include <limits>

// =============================================================================
// CPhysicsBody constructor
// -----------------------------------------------------------------------------
CPhysicsBody::CPhysicsBody() :  mInverseMass(0.0f), // Infinite mass by default
                                mVelocity(0.0f, 0.0f)
{

}

// =============================================================================
// Getters
// -----------------------------------------------------------------------------
float CPhysicsBody::GetInverseMass()
{
    return mInverseMass;
}

float CPhysicsBody::GetMass()
{
    // Check for divide by 0
    if (mInverseMass == 0.0f)
    {
        DEBUG_LOG("Requesting infinite mass")
        return std::numeric_limits<float>::max();
    }
    else
    {
        return 1.0f / mInverseMass;
    }
}

CVector2f CPhysicsBody::GetVelocity()
{
    return mVelocity;
}

CConvexShape * CPhysicsBody::GetShape()
{
    return &mShape;
}

CVector2f CPhysicsBody::GetPosition()
{
    return mShape.getPosition();
}

// =============================================================================
// Setters
// -----------------------------------------------------------------------------
void CPhysicsBody::SetInverseMass(float theInverseMass)
{
    mInverseMass = theInverseMass;
}

void CPhysicsBody::SetVelocity(CVector2f theVelocity)
{
    mVelocity = theVelocity;
}

void CPhysicsBody::AddVelocity(CVector2f theVelocity)
{
    mVelocity += theVelocity;
}

void CPhysicsBody::SetShape(CConvexShape theShape)
{
    mShape = theShape;
}