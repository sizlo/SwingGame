//
//  CPullingSwing.hpp
//  SwingGame
//
//  Created by Tim Brier on 24/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CPullingSwing__
#define __SwingGame__CPullingSwing__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPullingSwing : public CSwing
{
public:
    CPullingSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CPullingSwing();
    
    void Update(CTime elapsedTime);
    
    CVector2f AttenuateGravity(CVector2f gravity);
    
private:
    void RespondToAttach();
        
    static float smPullSpeedIncrement;
    static float smPullSpeedMax;
    static float smDetachLength;
};

#endif /* defined(__SwingGame__CPullingSwing__) */
