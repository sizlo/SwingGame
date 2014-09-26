//
//  SwingGame.cpp
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSwingGame.hpp"

// =============================================================================
// CSwingGame constructor/destructor
// -----------------------------------------------------------------------------
CSwingGame::CSwingGame() :  mWindowWidth(1024),
                            mWindowHeight(800),
                            mWindowTitle("SwingGame v0.0"),
                            mWindow(NULL),
                            mExitCode(EXIT_SUCCESS),
                            mGameState(static_cast<EGameState>(0)),
                            mSprite(NULL)
{
    
}

CSwingGame::~CSwingGame()
{
    
}

// =============================================================================
// SwingGame::Init
// Initialise the game
// -----------------------------------------------------------------------------
void CSwingGame::Init()
{
    // Create the game window
    mWindow = new CWindow(mWindowWidth, mWindowHeight, mWindowTitle);
    
    // Set the initial game state
    SetGameState(kGameStateFrontEnd);
    
    // Initialise other systems
    InitSFML();
}

// =============================================================================
// SwingGame::Run
// Enter the main loop, returns program exit code
// -----------------------------------------------------------------------------
int CSwingGame::Run()
{
    CClock theClock;
    
    while (mWindow->isOpen())
    {
        CTime elapsedTime = theClock.restart();
        
        ProcessEvents();
        Update(elapsedTime);
        Render();
    }
    
    return mExitCode;
}

// =============================================================================
// SwingGame::Cleanup
// Cleanup before quitting
// -----------------------------------------------------------------------------
void CSwingGame::Cleanup()
{
    SAFE_DELETE(mWindow);
    CTextUtilities::Cleanup();
}

// =============================================================================
// CSwingGame::SetGameState
// Set given GameState flags
// -----------------------------------------------------------------------------
void CSwingGame::SetGameState(EGameState theState)
{
    mGameState = static_cast<EGameState>(mGameState | theState);
}

// =============================================================================
// CSwingGame::UnsetGameState
// Unset the given GameState flags
// -----------------------------------------------------------------------------
void CSwingGame::UnsetGameState(EGameState theState)
{
    mGameState = static_cast<EGameState>(mGameState & ~theState);
}

// =============================================================================
// CSwingGame::HasAllGameStates
// Returns true only if the current state has all the given flags
// -----------------------------------------------------------------------------
bool CSwingGame::HasAllGameStates(EGameState theState)
{
    EGameState theResult = static_cast<EGameState>(mGameState & theState);
    return theResult == theState;
}

// =============================================================================
// CSwingGame::ProcessEvents
// Process all events recieved this cycle
// -----------------------------------------------------------------------------
void CSwingGame::ProcessEvents()
{
    // Eventually this will handle window focus events and keyboard/mouse events
    DEBUG_LOG("Process Events - Not fully implemented");
    
    CEvent theEvent;
    while (mWindow->pollEvent(theEvent))
    {
        // Close window : exit
        if (theEvent.type == CEvent::Closed) {
            mWindow->close();
        }
    }
}

// =============================================================================
// CSwingGame::Update
// Update all registered CUpdatables
// -----------------------------------------------------------------------------
void CSwingGame::Update(CTime elapsedTime)
{
    // Eventually this will go through a list of updateable items and call each
    // ones update method
    DEBUG_LOG("Update - Unimplemented");
    
    // For now lets just create a sprite that follows the mouse
    if (mSprite == NULL)
    {
        // This will leak, but its temporary so oh well
        mSprite = new CSprite("square.png");
    }
    mSprite->setPosition(sf::Mouse::getPosition(*mWindow).x,
                          sf::Mouse::getPosition(*mWindow).y);
}

// =============================================================================
// CSwingGame::Render
// Render all CRenderables registered
// -----------------------------------------------------------------------------
void CSwingGame::Render()
{
    // Eventually this will go through a list of renderable items and call each
    // ones render method
    DEBUG_LOG("Render - Unimplemented");
    
    // For now render the one sprite following the mouse
    mWindow->clear();
    mWindow->draw(*mSprite);
    mWindow->display();
}





