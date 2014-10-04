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
#include "CTextFrontEnd.hpp"
#include "CTextureBank.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
bool                        CSwingGame::smExitRequested = false;
EGameState                  CSwingGame::smGameState = kGameStateFrontEnd;
std::list<CUpdateable *>    CSwingGame::smTheUpdateables;
std::list<CUpdateable *>    CSwingGame::smTheUpdateablesToRemove;
std::list<CDrawable *>      CSwingGame::smTheDrawables;
std::list<CEvent>           CSwingGame::smTheKeyPresses;


// =============================================================================
// CSwingGame constructor/destructor
// -----------------------------------------------------------------------------
CSwingGame::CSwingGame() :  mWindowWidth(1024),
                            mWindowHeight(800),
                            mWindowTitle("SwingGame v0.0"),
                            mWindow(NULL),
                            mExitCode(EXIT_SUCCESS),
                            mFrontEndMenu(NULL)
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
    
    // Enter the front end menu
    mFrontEndMenu = new CTextFrontEnd();
    mFrontEndMenu->Enter();
    
    // Initialise other systems
    InitSFML(mWindow);
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
    SAFE_DELETE(mFrontEndMenu);
    CTextUtilities::Cleanup();
    CTextureBank::Cleanup();
}

// =============================================================================
// CSwingGame::ExitGame
// Exit the game
// -----------------------------------------------------------------------------
void CSwingGame::ExitGame()
{
    smExitRequested = true;
}

// =============================================================================
// CSwingGame::SetGameState
// Set given GameState flags
// -----------------------------------------------------------------------------
void CSwingGame::SetGameState(EGameState theState)
{
    smGameState = static_cast<EGameState>(smGameState | theState);
}

// =============================================================================
// CSwingGame::UnsetGameState
// Unset the given GameState flags
// -----------------------------------------------------------------------------
void CSwingGame::UnsetGameState(EGameState theState)
{
    smGameState = static_cast<EGameState>(smGameState & ~theState);
}

// =============================================================================
// CSwingGame::HasAllGameStates
// Returns true only if the current state has all the given flags
// -----------------------------------------------------------------------------
bool CSwingGame::HasAllGameStates(EGameState theState)
{
    EGameState theResult = static_cast<EGameState>(smGameState & theState);
    return theResult == theState;
}

// =============================================================================
// CSwingGame::RegisterUpdateable
// Add an updateable to the list
// -----------------------------------------------------------------------------
void CSwingGame::RegisterUpdateable(CUpdateable *theUpdateable)
{
    smTheUpdateables.push_back(theUpdateable);
}

// =============================================================================
// CSwingGame::RegisterDrawable
// Add a drawable to the list
// -----------------------------------------------------------------------------
void CSwingGame::RegisterDrawable(CDrawable *theDrawable)
{
    smTheDrawables.push_back(theDrawable);
}

// =============================================================================
// CSwingGame::UnregisterUpdateable
// Remove a given updateable from the list
// -----------------------------------------------------------------------------
void CSwingGame::UnregisterUpdateable(CUpdateable *theUpdateable)
{
    // If we're not updating go ahead and remove it, otherwise add it to a list
    // to be removed after the current update cycle
    if (!HasAllGameStates(kGameStateUpdating))
    {
        smTheUpdateables.remove(theUpdateable);
    }
    else
    {
        smTheUpdateablesToRemove.push_back(theUpdateable);
    }
}

// =============================================================================
// CSwingGame::UnregisterDrawable
// Remove a given drawable from the list
// -----------------------------------------------------------------------------
void CSwingGame::UnregisterDrawable(CDrawable *theDrawable)
{
    smTheDrawables.remove(theDrawable);
}

// =============================================================================
// CSwingGame::WasKeyPressedThisCycle
// Was a keypress event recieved for the given key this cycle
// -----------------------------------------------------------------------------
bool CSwingGame::WasKeyPressedThisCycle(CKeyboard::Key theKey)
{
    bool theResult = false;
    
    for (std::list<CEvent>::iterator it = smTheKeyPresses.begin();
         it != smTheKeyPresses.end();
         ++it)
    {
        if ((*it).type == CEvent::KeyPressed && (*it).key.code == theKey)
        {
            theResult = true;
        }
    }
    
    return theResult;
}

// =============================================================================
// CSwingGame::ProcessEvents
// Process all events recieved this cycle
// -----------------------------------------------------------------------------
void CSwingGame::ProcessEvents()
{
    // Eventually this will handle window focus events and keyboard/mouse events
    // Only log once
    static bool hasLogged = false;
    if (!hasLogged)
    {
        DEBUG_LOG("Process Events - Not fully implemented");
        hasLogged = true;
    }
    
    // Clear the last cycles keypress/mouse event list
    smTheKeyPresses.clear();
    
    CEvent theEvent;
    while (mWindow->pollEvent(theEvent))
    {
        switch (theEvent.type)
        {
            case CEvent::KeyPressed:
                // Keep a list of keypress events this cycle
                smTheKeyPresses.push_back(theEvent);
                break;
                
            case CEvent::Closed:
                // Exit on close event
                ExitGame();
                break;
                
            default:
                break; // Do nothing
        }
    }
    
    // React to exit requests
    if (smExitRequested)
    {
        mWindow->close();
    }
}

// =============================================================================
// CSwingGame::Update
// Update all registered CUpdatables
// -----------------------------------------------------------------------------
void CSwingGame::Update(CTime elapsedTime)
{
    // Set game state
    SetGameState(kGameStateUpdating);
    
    // Iterate through the registered updateables, updating each in turn
    for (std::list<CUpdateable *>::iterator it = smTheUpdateables.begin();
         it != smTheUpdateables.end();
         ++it)
    {
        // Only update when in an appropriate state
        if ((*it)->ShouldUpdateForState(smGameState))
        {
            (*it)->Update(elapsedTime);
        }
    }
    
    // Remove any updateables whice were requested this cycle
    while (!smTheUpdateablesToRemove.empty())
    {
        smTheUpdateables.remove(smTheUpdateablesToRemove.front());
        smTheUpdateablesToRemove.pop_front();
    }
    
    // Unset game state
    UnsetGameState(kGameStateUpdating);
}

// =============================================================================
// CSwingGame::Render
// Render all CDrawables registered
// -----------------------------------------------------------------------------
void CSwingGame::Render()
{
    // Clear the window
    mWindow->clear();
    
    // Iterate through all registered drawables, drawing them all
    for (std::list<CDrawable *>::iterator it = smTheDrawables.begin();
         it != smTheDrawables.end();
         ++it)
    {
        (*it)->Draw(mWindow);
    }
    
    // Display the new window contents
    mWindow->display();
}





