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
#include "CRenderable.hpp"

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CLevel;
class CPlayer;

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSwing : public CRenderable, public CUpdateable
{
public:
    CSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CSwing();
    
    void AttemptToAttach(CVector2f theAimPoint);
    void Detach();
    
    CVector2f AttenuateGravity(CVector2f gravity);
    
    void Draw(CWindow *theWindow);
    void Update(CTime elapsedTime);
    
    bool IsAttached();
    
private:
    float       GetDistanceToBob();
    bool        IsThereAValidAnchor(CVector2f theAimPoint, CVector2f *anchor);
    CVector2f   GetPerpendicularDirection();
    
    void        HandleInput(CTime elapsedTime);
    void        HandleCollisions();
    void        RespondToCollisionAt(float distanceFromOrigin);
    
    bool                    mAttached;
    CVector2f               mOrigin;
    CVector2f               mOriginDrawPoint;
    float                   mLength;
    CPlayer                 *mBob;
    CLevel                  *mParentLevel;
};


#endif /* defined(__SwingGame__CSwing__) */
