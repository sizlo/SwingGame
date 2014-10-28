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
    
    void Init();
    void Cleanup();
    
private:
    void HandleInput();
    void HandleCollisions();
    
    CConvexShape    mShape;
    CLevel          *mParentLevel;
};

#endif /* defined(__SwingGame__CPlayer__) */
