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
#include "CLevel.hpp"
#include "CGameOptions.hpp"
#include "CDebugOptions.hpp"
#include "SystemUtilities.hpp"
#include <sstream>

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
bool                        CSwingGame::smExitRequested = false;
EGameState                  CSwingGame::smGameState = kGameStateFrontEnd;
std::list<CUpdateable *>    CSwingGame::smTheUpdateables;
std::list<CUpdateable *>    CSwingGame::smTheUpdateablesToAdd;
std::list<CUpdateable *>    CSwingGame::smTheUpdateablesToRemove;
std::list<CRenderable *>    CSwingGame::smTheRenderables;
CGameLocation               *CSwingGame::smCurrentLocation = NULL;


// =============================================================================
// CSwingGame constructor/destructor
// -----------------------------------------------------------------------------
CSwingGame::CSwingGame() :  mWindowTitle("SwingGame v0.0"),
                            mWindow(NULL),
                            mFPS(0),
                            mUPS(0),
                            mExitCode(EXIT_SUCCESS)
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
    mWindow = new CWindow(CGameOptions::smWindowWidth,
                          CGameOptions::smWindowHeight,
                          mWindowTitle);
    
    // Enter the front end menu
    GoToLocation(kGameLocationFrontEnd);
    
    // Initialise other systems
    SystemUtilities::Init(mWindow);
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
        
        static CTime accumulatingTime;
        accumulatingTime += elapsedTime;
        
        ProcessEvents();
        
        Update(elapsedTime);
        
        // Only render if vsync is off or enough time has past
        if (!CGameOptions::smVsync
            || accumulatingTime.asSeconds() >= 1.0f / CGameOptions::smMaxFPS)
        {
            accumulatingTime = CTime();
            Render();
        }
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
    SAFE_DELETE(smCurrentLocation);
    TextUtilities::Cleanup();
    CTextureBank::Cleanup();
}

// =============================================================================
// CSwingGame::ExitGame
// Exit the game
// -----------------------------------------------------------------------------
void CSwingGame::ExitGame()
{
    DEBUG_LOG("Exit requested");
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
    // If we're not updating then we can add it now, otherwise add it to a list
    // to be added after the current update cycle
    if (!HasAllGameStates(kGameStateUpdating))
    {
        smTheUpdateables.push_back(theUpdateable);
    }
    else
    {
        smTheUpdateablesToAdd.push_back(theUpdateable);
    }
}

// =============================================================================
// CSwingGame::RegisterRenderable
// Add a renderable to the list
// -----------------------------------------------------------------------------
void CSwingGame::RegisterRenderable(CRenderable *theRenderable)
{
    smTheRenderables.push_back(theRenderable);
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
// CSwingGame::UnregisterRenderable
// Remove a given renderable from the list
// -----------------------------------------------------------------------------
void CSwingGame::UnregisterRenderable(CRenderable *theRenderable)
{
    smTheRenderables.remove(theRenderable);
}

// =============================================================================
// CSwingGame::GoToLocation
// Go to a game location (level/menu)
// -----------------------------------------------------------------------------
void CSwingGame::GoToLocation(EGameLocation theLocation)
{
    // If we're already in a location leave it
    if (smCurrentLocation != NULL)
    {
        smCurrentLocation->Exit();
        SAFE_DELETE(smCurrentLocation);
    }
    
    switch (theLocation)
    {
        case kGameLocationFrontEnd:
            DEBUG_LOG("Front end requested");
            smCurrentLocation = new CTextFrontEnd();
            break;
            
        case kGameLocationLevel1:
            DEBUG_LOG("Level 1 requested");
            smCurrentLocation = new CLevel("testLevel.xml");
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to front end");
            smCurrentLocation = new CTextFrontEnd();
            break;
    }
    
    smCurrentLocation->Enter();
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
    SystemUtilities::ClearInputEvents();
    
    CEvent theEvent;
    while (mWindow->pollEvent(theEvent))
    {
        switch (theEvent.type)
        {
            case CEvent::KeyPressed:
                // Keep a list of keypress events this cycle
                SystemUtilities::AddInputEvent(theEvent);
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
    
    // Count updates
    static int numUpdates;
    static CTime accumulatingElapsedTime;
    
    numUpdates++;
    accumulatingElapsedTime += elapsedTime;
    if (accumulatingElapsedTime.asSeconds() >= 1.0f) // Every second
    {
        mUPS = numUpdates;
        numUpdates = 0;
        accumulatingElapsedTime = CTime();
    }
    
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
    // Add any updateables which were requested this cycle
    while (!smTheUpdateablesToAdd.empty())
    {
        smTheUpdateables.push_back(smTheUpdateablesToAdd.front());
        smTheUpdateablesToAdd.pop_front();
    }
    
    // Unset game state
    UnsetGameState(kGameStateUpdating);
}

// =============================================================================
// CSwingGame::Render
// Render all CRenderable registered
// -----------------------------------------------------------------------------
void CSwingGame::Render()
{
    // Count frames
    static int numFrames = 0;
    static CClock theClock;
    static CTime elapsedTime;
    
    numFrames++;
    elapsedTime += theClock.restart();
    if (elapsedTime.asSeconds() >= 1.0f) // Every second
    {
        mFPS = numFrames;
        numFrames = 0;
        elapsedTime = CTime();
    }
    
    // Clear the window
    mWindow->clear();
    
    // Iterate through all registered renderables, drawing them all
    for (std::list<CRenderable *>::iterator it = smTheRenderables.begin();
         it != smTheRenderables.end();
         ++it)
    {
        (*it)->Draw(mWindow);
    }
    
    // In debug draw frame/update rate over everything else
#if SG_DEBUG
    if (CDebugOptions::smShowFramerate)
    {
        std::stringstream theStream;
        theStream << "FPS: " << mFPS << std::endl;
        theStream << "UPS: " << mUPS;
        mWindow->DrawTextAt(theStream.str(),
                            CGameOptions::smWindowWidth - 100,
                            5,
                            CColour::Red);
    }
#endif
    
    // Display the new window contents
    mWindow->display();
}





