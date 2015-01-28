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
    mPlayer->Init(mStartPosition);
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
    
    FOR_EACH_IN_LIST(CPhysicsBody *, mObstacles)
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
    
    // Check for completion
    if (HasPlayerReachedGoal())
    {
        DEBUG_LOG("GOAL!");
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



