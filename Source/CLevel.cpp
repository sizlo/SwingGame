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
: mTutorialText()
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
    std::string completedTitle = mName + " completed";
    mCompletedMenu = new CLevelEndMenu(completedTitle, this);
    std::string failedTitle = mName + " failed";
    mFailedMenu = new CLevelEndMenu(failedTitle, this);
    mPauseMenu = new CPauseMenu(this);
    
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
    SAFE_DELETE(mCompletedMenu);
    SAFE_DELETE(mFailedMenu);
    SAFE_DELETE(mPauseMenu);
    
    FOR_EACH_IN_LIST(CPhysicsBody *, mObstacles)
    {
        SAFE_DELETE((*it));
    }
}

// =============================================================================
// CLevel::StartLevel
// Starts the level
// -----------------------------------------------------------------------------
void CLevel::StartLevel()
{
    // Unpause
    CSwingGame::UnsetGameState(kGameStatePaused);
    
    mPlayer->StartLevel(mStartPosition);
    
    mLevelClock.Restart();
}

// =============================================================================
// CLevelPauseLevel
// -----------------------------------------------------------------------------
void CLevel::PauseLevel()
{
    CSwingGame::SetGameState(kGameStatePaused);
    
    // Pause clocks
    mLevelClock.Pause();
    mPlayer->PauseClocks(true);
}

// =============================================================================
// CLevel::ResumeLevel
// -----------------------------------------------------------------------------
void CLevel::ResumeLevel()
{
    CSwingGame::UnsetGameState(kGameStatePaused);
    
    // Unpause clocks
    mLevelClock.Resume();
    mPlayer->PauseClocks(false);
}

// =============================================================================
// CLevel:ReactToFocusLost
// -----------------------------------------------------------------------------
void CLevel::ReactToFocusLost()
{
    mShouldResumeOnFocusGained = false;
    
    // Pause the game if it isn't already
    if (!CSwingGame::HasAllGameStates(kGameStatePaused))
    {
        PauseLevel();
        mShouldResumeOnFocusGained = true;
    }
}

// =============================================================================
// CLevel:ReactToFocusGained
// -----------------------------------------------------------------------------
void CLevel::ReactToFocusGained()
{
    if (mShouldResumeOnFocusGained)
    {
        ResumeLevel();
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
// CLevel::SetTutorialText
// -----------------------------------------------------------------------------
void CLevel::SetTutorialText(CText theText)
{
    mTutorialText = theText;
    mTutorialText.setColor(CColour::Black);
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
    // Open the pause menu on esc
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Escape))
    {
        PauseLevel();
        mPauseMenu->Enter();
    }
    
    // Restart the level on R
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::R))
    {
        StartLevel();
    }
    
    // Check for completion
    if (HasPlayerReachedGoal())
    {
        WinLevel();
    }
    
    // Check for player leaving the level
    if (HasPlayerLeftLevel())
    {
        FailLevel();
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
    
    // Draw the tutorial text
    theWindow->draw(mTutorialText);
    
    // Draw the clock time
    std::list<CVector2f> points;
    points.push_back(CVector2f(0.0f, 0.0f));
    points.push_back(CVector2f(50.0f, 0.0f));
    points.push_back(CVector2f(50.0f, 20.0f));
    points.push_back(CVector2f(0.0f, 20.0f));
    CConvexShape clockBG(points);
    clockBG.setPosition(CVector2f(924.0f, 28.0f));
    clockBG.setFillColor(CColour::Yellow);
    theWindow->DrawShape(clockBG);
    CTime elapsed = mLevelClock.GetElapsedTime();
    theWindow->DrawTextAt(elapsed.AsString(), 929, 30, CColour::Black);
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

// =============================================================================
// CLevel::WinLevel
// -----------------------------------------------------------------------------
void CLevel::WinLevel()
{
    // Pause the game
    PauseLevel();
    
    std::map<std::string, CTime> bestTimes = XMLInterpreter::ReadBestTimes("times.xml");
    
    // Do we have a best time for this level
    CTime thisTime = mLevelClock.GetElapsedTime();
    CTime bestTime = thisTime;
    std::string key = mName;
    std::replace(key.begin(), key.end(), ' ', '_');
    if (bestTimes.count(key) > 0)
    {
        bestTime = bestTimes[key];
    }
    
    // Was this time better than our best
    if (thisTime < bestTime)
    {
        bestTime = thisTime;
    }
    
    // Save out best times
    bestTimes[key] = bestTime;
    XMLInterpreter::WriteBestTimes("times.xml", bestTimes);
    
    
    std::string timeString = "Your time: ";
    timeString += thisTime.AsString();
    timeString += "\nBest time: ";
    timeString += bestTime.AsString();
    mCompletedMenu->SetExtraText(timeString);
    
    mCompletedMenu->Enter();
}

// =============================================================================
// CLevel::FailLevel
// -----------------------------------------------------------------------------
void CLevel::FailLevel()
{
    PauseLevel();
    
    mFailedMenu->Enter();
}



