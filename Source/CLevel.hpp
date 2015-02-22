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
#include "CRenderable.hpp"
#include "CUpdateable.hpp"
#include "CPlayer.hpp"
#include "CollisionHandler.hpp"
#include "CLevelEndMenu.hpp"
#include "CPauseMenu.hpp"
#include <list>

// =============================================================================
// Data structures
// -----------------------------------------------------------------------------
struct SStartPosition
{
    CVector2f   mPosition;
    CVector2f   mSwingTarget;
    CVector2f   mVelocity;
    ESwingTypes mSwingType;
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
    
    void StartLevel();
    void PauseLevel();
    void ResumeLevel();
    
    void ReactToFocusLost();
    void ReactToFocusGained();
    
    // Setters
    void SetName            (std::string    theName);
    void SetStartPosition   (SStartPosition thePosition);
    void SetGoal            (CPhysicsBody   theGoal);
    void SetBackground      (CSprite        theBackground);
    void AddObstacle        (CPhysicsBody   theObstacle);
    void SetTutorialText    (CText          theText);
    
    // Getters
    std::list<CPhysicsBody *>   GetObstacles();
    CVector2f                   GetGravityAcceleration();
    
    // Update the level
    void Update(CTime elapsedTime);
    // Draw the level
    void Draw(CWindow *theWindow);
    
private:
    bool HasPlayerReachedGoal();
    bool HasPlayerLeftLevel();
    
    void WinLevel();
    void FailLevel();
    
    std::string                 mName;
    
    // Start and goal
    SStartPosition              mStartPosition;
    CPhysicsBody                mGoal;
    
    // Background sprite
    CSprite                     mBackground;
    
    // Obstacles
    std::list<CPhysicsBody *>   mObstacles;
    
    // The player
    CPlayer                     *mPlayer;
    
    // Physics parameters
    CVector2f                   mGravityAcceleration;
    
    CLevelEndMenu               *mCompletedMenu;
    CLevelEndMenu               *mFailedMenu;
    CPauseMenu                  *mPauseMenu;
    
    CText                       mTutorialText;
    
    CPauseableClock             mLevelClock;
    
    bool                        mShouldResumeOnFocusGained;
};

#endif /* defined(__SwingGame__CLevel__) */
