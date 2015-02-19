//
//  CRigidSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 19/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CRigidSwing.hpp"

// =============================================================================
// CRigidSwing constructor/destructor
// -----------------------------------------------------------------------------
CRigidSwing::CRigidSwing(CPlayer *theBob, CLevel *theParentLevel)
:   CSwing(theBob, theParentLevel)
{
    
}

CRigidSwing::~CRigidSwing()
{
    
}

// =============================================================================
// CRigidSwing::CanJumpFrom
// -----------------------------------------------------------------------------
bool CRigidSwing::CanJumpFrom()
{
    // We can jump from rigid swings
    return IsAttached();
}