//
//  CLevel.hpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CLevel__
#define __SwingGame__CLevel__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CGameLocation.hpp"
#include "SFMLIntegration.hpp"
#include "CRenderable.hpp"
#include "CUpdateable.hpp"
#include "CPlayer.hpp"
#include <list>

// =============================================================================
// Data structures
// -----------------------------------------------------------------------------
struct SStartPosition
{
    CVector2f mPosition;
    CVector2f mSwingTarget;
};

struct SLevelItem
{
    CVector2f           mPosition;
    CConvexShape        mShape;
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLevel : public CGameLocation, public CRenderable, public CUpdateable
{
public:
    CLevel(std::string filename);
    ~CLevel();
    
    void Enter();
    void Exit();
    
    // Setters
    void SetName            (std::string    theName);
    void SetStartPosition   (SStartPosition thePosition);
    void SetGoal            (SLevelItem     theGoal);
    void SetBackground      (CSprite        theBackground);
    void AddObstacle        (SLevelItem     theObstacle);
    
    // Update the level
    void Update(CTime elapsedTime);
    // Draw the level
    void Draw(CWindow *theWindow);
    
private:
    std::string             mName;
    
    // Start and goal
    SStartPosition          mStartPosition;
    SLevelItem              mGoal;
    
    // Background sprite
    CSprite                 mBackground;
    
    // Obstacles
    std::list<SLevelItem>   mObstacles;
    
    // The player
    CPlayer                 mPlayer;
};

#endif /* defined(__SwingGame__CLevel__) */
