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
#include "CUpdateable.hpp"

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CLevel;
class CPlayer;

// =============================================================================
// Enums
// -----------------------------------------------------------------------------
enum ESwingTypes
{
    kSwingTypeRigid,
    kSwingTypeFlexible,
    kSwingTypeSpring,
    kSwingTypeMax
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSwing : public CRenderable, public CUpdateable
{
public:
    CSwing(CPlayer *theBob, CLevel *theParentLevel);
    ~CSwing();
    
    virtual void AttemptToAttach(CVector2f theAimPoint);
    virtual void Detach(bool shouldRespond = false);
    
    virtual CVector2f AttenuateGravity(CVector2f gravity);
    
    virtual void Draw(CWindow *theWindow);
    virtual void Update(CTime elapsedTime);
    virtual bool ShouldUpdateForState(EGameState theState);
    
    virtual bool IsAttached();
    virtual CColour GetColour();
    
protected:
    virtual float       GetDistanceToBob();
    virtual bool        IsThereAValidAnchor(CVector2f theAimPoint,
                                            CVector2f *anchor);
    virtual CVector2f   GetPerpendicularDirection();
    
    virtual void        HandleInput(CTime elapsedTime);
    virtual void        HandleCollisions();
    
    virtual void        DrawAnchorPoint(CWindow *theWindow,
                                        CVector2f theAnchor);
    virtual void        DrawSwingSection(CWindow *theWindow,
                                 CVector2f start,
                                 CVector2f end);
    
    virtual void        RespondToAttach();
    virtual void        RespondToDetach();
    virtual void        RespondToCollisionAt(CVector2f intersectionPoint);
    virtual void        AdjustDirectionToGoThrough(CVector2f targetPoint);
    
    bool                mAttached;
    CVector2f           mOrigin;
    CVector2f           mOriginDrawPoint;
    float               mLength;
    CPlayer             *mBob;
    CLevel              *mParentLevel;
    CColour             mColour;
    
    static float        smMaxLength;
    static float        smClimbSpeed;
    static float        smCollisionIgnoreDistance;
    static float        smAnchorGap;
    static float        smReflectionScaleFactor;
};


#endif /* defined(__SwingGame__CSwing__) */
