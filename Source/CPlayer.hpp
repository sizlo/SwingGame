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

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CLevel;
struct SLevelItem;
struct SStartPosition;

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPlayer : public CUpdateable, public CRenderable
{
public:
    CPlayer(CLevel *theParentLevel);
    ~CPlayer();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Init(SStartPosition theStartPos);
    void Cleanup();
    
    // Move by the given offset in a way that prevents the player phasing
    // through objects
    void Move(float offsetX, float offsetY);
    void Move(CVector2f offset);
    
private:
    void HandleInput(CTime elapsedTime);
    void HandleCollisions();
    
    CConvexShape    mShape;
    CLevel          *mParentLevel;
    
    // The smallest distance from the centre of the player to it's outer edge
    float mSmallestRadius;
};

#endif /* defined(__SwingGame__CPlayer__) */
