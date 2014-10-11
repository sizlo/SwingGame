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
#include "SystemUtilities.hpp"

// =============================================================================
// CLevel constructor/destructor
// -----------------------------------------------------------------------------
CLevel::CLevel(std::string filename)    :   mPlayer("player.png")
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
    mObstacles.push_back(theObstacle);
}

// =============================================================================
// CLevel::Update
// Update the level
// -----------------------------------------------------------------------------
void CLevel::Update(CTime elapsedTime)
{
    // Temporary
    CVector2i playerPos = SystemUtilities::GetMousePosition();
    playerPos.x = std::max(0, playerPos.x);
    playerPos.x = std::min(1024-20, playerPos.x);
    playerPos.y = std::max(0, playerPos.y);
    playerPos.y = std::min(768-40, playerPos.y);
    mPlayer.setPosition(playerPos.x, playerPos.y);
    
    if (CKeyboard::isKeyPressed(CKeyboard::R))
    {
        mPlayer.rotate(360 * elapsedTime.asSeconds());
    }
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
    for (std::list<SLevelItem>::iterator it = mObstacles.begin();
         it != mObstacles.end();
         ++it)
    {
        theWindow->DrawShape((*it).mShape);
    }
    
    // Temporary
    theWindow->DrawSprite(mPlayer);
}





