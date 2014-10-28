//
//  CLevel.cpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CLevel.hpp"
#include "CSwingGame.hpp"
#include "XMLInterpreter.hpp"

// =============================================================================
// CLevel constructor/destructor
// -----------------------------------------------------------------------------
CLevel::CLevel(std::string filename)
{
    XMLInterpreter::ProcessLevel(filename, this);
}

CLevel::~CLevel()
{
    
}

// =============================================================================
// CLevel::Enter
// -----------------------------------------------------------------------------
void CLevel::Enter()
{
    // Set the game state
    CSwingGame::SetGameState(kGameStateInGame);
    
    // Register any renderables and updateables
    CSwingGame::RegisterRenderable(this);
    CSwingGame::RegisterUpdateable(this);
    
    // Initialise anything we need to
    mPlayer = new CPlayer(this);
    mPlayer->Init();
}

// =============================================================================
// CLevel::Exit
// -----------------------------------------------------------------------------
void CLevel::Exit()
{
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateInGame);
    
    // Unregister all renderables and updateables
    CSwingGame::UnregisterRenderable(this);
    CSwingGame::UnregisterUpdateable(this);
    
    // Cleanup anything we need to
    mPlayer->Cleanup();
    SAFE_DELETE(mPlayer);
    
    FOR_EACH_IN_LIST(SLevelItem *, mObstacles)
    {
        SAFE_DELETE((*it));
    }
}

// =============================================================================
// CLevel::SetName
// -----------------------------------------------------------------------------
void CLevel::SetName(std::string theName)
{
    mName = theName;
}

// =============================================================================
// CLevel::SetStartPosition
// -----------------------------------------------------------------------------
void CLevel::SetStartPosition(SStartPosition thePosition)
{
    mStartPosition = thePosition;
}

// =============================================================================
// CLevel::SetGoal
// -----------------------------------------------------------------------------
void CLevel::SetGoal(SLevelItem theGoal)
{
    mGoal = theGoal;
}

// =============================================================================
// CLevel::SetBackground
// -----------------------------------------------------------------------------
void CLevel::SetBackground(CSprite theBackground)
{
    mBackground = theBackground;
}

// =============================================================================
// CLevel::AddObstacle
// -----------------------------------------------------------------------------
void CLevel::AddObstacle(SLevelItem theObstacle)
{
    mObstacles.push_back(new SLevelItem(theObstacle));
}

// =============================================================================
// CLevel::GetObstacles
// -----------------------------------------------------------------------------
std::list<SLevelItem *> CLevel::GetObstacles()
{
    return mObstacles;
}

// =============================================================================
// CLevel::Update
// Update the level
// -----------------------------------------------------------------------------
void CLevel::Update(CTime elapsedTime)
{

}

// =============================================================================
// CLevel::Draw
// Draw the level
// -----------------------------------------------------------------------------
void CLevel::Draw(CWindow *theWindow)
{
    // Draw the background
    theWindow->draw(mBackground);
    
    // Draw the goal
    theWindow->DrawShape(mGoal.mShape);
    
    // Draw all level items
    FOR_EACH_IN_LIST(SLevelItem *, mObstacles)
    {
        theWindow->DrawShape((*it)->mShape);
    }
}





