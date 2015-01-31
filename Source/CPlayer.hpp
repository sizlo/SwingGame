//
//  CPlayer.hpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CPlayer__
#define __SwingGame__CPlayer__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CPhysicsBody.hpp"
#include "CSwing.hpp"

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CLevel;
struct SStartPosition;

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPlayer : public CUpdateable, public CRenderable, public CPhysicsBody
{
public:
    CPlayer(CLevel *theParentLevel);
    ~CPlayer();
    
    void Update(CTime elapsedTime);
    bool ShouldUpdateForState(EGameState theState);
    void Draw(CWindow *theWindow);
    
    void Init();
    void Cleanup();
    void StartLevel(SStartPosition theStartPos);
    
    void MoveFixedDistanceUntilCollision(CVector2f offset);
    
private:
    void        HandleInput();
    CVector2f   HandlePhysics();
    bool        HandleCollisions();
    
    // Move for the given amount of time with the given acceleration or until
    // we collide
    CTime MoveUntilCollision(CTime elapsedTime, CVector2f acceleration);
    
    CLevel *mParentLevel;
    
    // The smallest distance from the centre of the player to it's outer edge
    float mSmallestRadius;
    
    // The different swing types
    CSwing *mSwings[kSwingTypeMax];

    // The swing type we'll fire next
    ESwingTypes mSwingToFire;
    
    // The swing we're currently attached to
    CSwing *mCurrentSwing;
};

#endif /* defined(__SwingGame__CPlayer__) */
