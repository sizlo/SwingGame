//
//  CSwing.hpp
//  SwingGame
//
//  Created by Tim Brier on 31/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CSwing__
#define __SwingGame__CSwing__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"
#include "CPhysicsBody.hpp"
#include "CRenderable.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSwing : public CRenderable, public CUpdateable
{
public:
    CSwing(CPhysicsBody *theBob);
    ~CSwing();
    
    void AttemptToAttach(CVector2f theAimPoint);
    void Detach();
    
    CVector2f AttenuateGravity(CVector2f gravity);
    
    void Draw(CWindow *theWindow);
    void Update(CTime elapsedTime);
    
private:
    float       GetDistanceToBob();
    bool        IsThereAValidAnchor(CVector2f theAimPoint, CVector2f *anchor);
    CVector2f   GetPerpendicularDirection();
    
    bool                    mAttached;
    CVector2f               mOrigin;
    float                   mLength;
    CPhysicsBody            *mBob;
};


#endif /* defined(__SwingGame__CSwing__) */
