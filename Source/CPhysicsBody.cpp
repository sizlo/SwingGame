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
CPhysicsBody::CPhysicsBody() :  // Initialise mass to max value since most
                                // objects will be static 
                                mMass(std::numeric_limits<float>::max()),
                                mVelocity(0.0f, 0.0f),
                                mForce(0.0f, 0.0f)
{
    
}

// =============================================================================
// Getters
// -----------------------------------------------------------------------------
float CPhysicsBody::GetMass()
{
    return mMass;
}

CVector2f CPhysicsBody::GetVelocity()
{
    return mVelocity;
}

CVector2f CPhysicsBody::GetForce()
{
    return mForce;
}

CConvexShape * CPhysicsBody::GetShape()
{
    return &mShape;
}

// =============================================================================
// Setters
// -----------------------------------------------------------------------------
void CPhysicsBody::SetMass(float theMass)
{
    mMass = theMass;
}

void CPhysicsBody::SetVelocity(CVector2f theVelocity)
{
    mVelocity = theVelocity;
}

void CPhysicsBody::AddVelocity(CVector2f theVelocity)
{
    mVelocity += theVelocity;
}

void CPhysicsBody::SetForce(CVector2f theForce)
{
    mForce = theForce;
}

void CPhysicsBody::ApplyForce(CVector2f theForce)
{
    mForce += theForce;
}

void CPhysicsBody::SetShape(CConvexShape theShape)
{
    mShape = theShape;
}