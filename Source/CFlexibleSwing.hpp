//
//  CFlexibleSwing.h
//  SwingGame
//
//  Created by Tim Brier on 30/11/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CFlexibleSwing__
#define __SwingGame__CFlexibleSwing__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CFlexibleSwing : public CSwing
{
public:
    CFlexibleSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CFlexibleSwing();
    
    virtual void AttemptToAttach(CVector2f theAimPoint);
    virtual void Detach();
    
    virtual void Draw   (CWindow *theWindow);
    virtual void Update (CTime elapsedTime);
    
protected:
    virtual void HandleInput(CTime elapsedTime);
    virtual void RespondToCollisionAt(CVector2f intersectionPoint);
    
private:
    float                   GetInactiveLength();
    
    std::list<CVector2f>    mPreviousOrigins;
};

#endif /* defined(__SwingGame__CFlexibleSwing__) */
