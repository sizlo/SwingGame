//
//  CSpringSwing.h
//  SwingGame
//
//  Created by Tim Brier on 07/12/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CSpringSwing__
#define __SwingGame__CSpringSwing__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"

// =============================================================================
// Class Definition
// -----------------------------------------------------------------------------
class CSpringSwing : public CSwing
{
public:
    CSpringSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CSpringSwing();
    
    virtual void AttemptToAttach(CVector2f theAimPoint);
    virtual CVector2f AttenuateGravity(CVector2f gravity);
    
    virtual void Update(CTime elapsedTime);
    
    virtual void HandleInput(CTime elapsedTime);
    
protected:
    virtual void RespondToAttach();
    virtual void RespondToDetach();
    virtual void RespondToCollisionAt(CVector2f intersectionPoint);
    
private:
    float mOriginalLength;
    
    static float smMinStretchFactor;
    static float smLaunchMultiplier;
    static float smMaxStretchFactor;
};

#endif /* defined(__SwingGame__CSpringSwing__) */
