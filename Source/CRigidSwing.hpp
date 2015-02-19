//
//  CRigidSwing.h
//  SwingGame
//
//  Created by Tim Brier on 19/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CRigidSwing__
#define __SwingGame__CRigidSwing__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CRigidSwing : public CSwing
{
public:
    CRigidSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CRigidSwing();
    
    bool CanJumpFrom();
};

#endif /* defined(__SwingGame__CRigidSwing__) */
