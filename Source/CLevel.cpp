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
CLevel::CLevel(std::string filename)
{
    XMLInterpreter::ProcessLevel(filename, this);
    mGravityAcceleration = CVector2f(0.0f, 500.0f); // Read from file?
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
    mEndMenu = new CLevelEndMenu(this);
    
    // Start the level
    StartLevel();
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
    SAFE_DELETE(mEndMenu);
    
    FOR_EACH_IN_LIST(CPhysicsBody *, mObstacles)
    {
        SAFE_DELETE((*it));
    }
}

// =============================================================================
// CLevel::Init
// Starts the level
// -----------------------------------------------------------------------------
void CLevel::StartLevel()
{
    // Unpause
    CSwingGame::UnsetGameState(kGameStatePaused);
    
    mPlayer->StartLevel(mStartPosition);
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
void CLevel::SetGoal(CPhysicsBody theGoal)
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
void CLevel::AddObstacle(CPhysicsBody theObstacle)
{
    mObstacles.push_back(new CPhysicsBody(theObstacle));
}

// =============================================================================
// CLevel::GetObstacles
// -----------------------------------------------------------------------------
std::list<CPhysicsBody *> CLevel::GetObstacles()
{
    return mObstacles;
}

// =============================================================================
// CLevel::GetGravityAcceleration
// -----------------------------------------------------------------------------
CVector2f CLevel::GetGravityAcceleration()
{
    return mGravityAcceleration;
}

// =============================================================================
// CLevel::Update
// Update the level
// -----------------------------------------------------------------------------
void CLevel::Update(CTime elapsedTime)
{
    // Pause game on esc
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Escape))
    {
        if (!CSwingGame::HasAllGameStates(kGameStatePaused))
        {
            CSwingGame::SetGameState(kGameStatePaused);
        }
        else
        {
            CSwingGame::UnsetGameState(kGameStatePaused);
        }
    }
    
    // Restart the level on R
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::R))
    {
        StartLevel();
    }
    
    // Check for completion
    if (HasPlayerReachedGoal())
    {
        // Pause the game
        CSwingGame::SetGameState(kGameStatePaused);
        mEndMenu->Enter();
    }
    
    // Check for player leaving the level
    if (HasPlayerLeftLevel())
    {
        // Kill them!
        
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
    theWindow->DrawShape(*(mGoal.GetShape()));
    
    // Draw all level items
    FOR_EACH_IN_LIST(CPhysicsBody *, mObstacles)
    {
        theWindow->DrawShape(*((*it)->GetShape()));
    }
}

// =============================================================================
// CLevel::HasPlayerReachedGoal
// -----------------------------------------------------------------------------
bool CLevel::HasPlayerReachedGoal()
{
    bool result = false;
    
    CVector2f cv;
    if (CollisionHandler::AreColliding(*(mPlayer->GetShape()),
                                       *(mGoal.GetShape()),
                                       &cv,
                                       kCDLhsInside))
    {
        result = true;
    }
    
    return result;
}

// =============================================================================
// CLevel::HasPlayerLeftLevel
// -----------------------------------------------------------------------------
bool CLevel::HasPlayerLeftLevel()
{
    bool theResult = false;
    
    // Check if the player is completely outside any of the window boundaries
    CFloatRect playerGlobalBounds = mPlayer->GetShape()->getGlobalBounds();
    CFloatRect viewBounds = CFloatRect(GameOptions::viewLeft,
                                       GameOptions::viewTop,
                                       GameOptions::viewWidth,
                                       GameOptions::viewHeight);
    if (!playerGlobalBounds.intersects(viewBounds))
    {
        theResult = true;
    }
    
    return theResult;
}



