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
#include "CFrontEnd.hpp"
#include "CTextureBank.hpp"
#include "CLevel.hpp"
#include "GameOptions.hpp"
#include "DebugOptions.hpp"
#include "SystemUtilities.hpp"
#include <sstream>

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
bool                        CSwingGame::smExitRequested = false;
EGameState                  CSwingGame::smGameState = kGameStateFrontEnd;
std::list<CUpdateable *>    CSwingGame::smTheUpdateables;
std::list<SUpdateableRegistrationRequest>
                            CSwingGame::smUpdateableRegistrationRequests;
std::list<CRenderable *>    CSwingGame::smTheRenderables;
CGameLocation               *CSwingGame::smCurrentLocation = NULL;

// =============================================================================
// Non member variables
// -----------------------------------------------------------------------------
#if SG_DEBUG
CDebugHelper *theDebugHelper;
#endif

// =============================================================================
// CSwingGame constructor/destructor
// -----------------------------------------------------------------------------
CSwingGame::CSwingGame() :  mWindowTitle("SwingGame v" SG_VERSION_STRING),
                            mWindow(NULL),
                            mFPS(0),
                            mShouldSkipUpdateFrame(false),
#if !USE_SFML_VSYNC
                            mUPS(0),
#endif
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
    // Initialise game options
    GameOptions::Init();

    // Create the game window
    mWindow = new CWindow(GameOptions::windowWidth,
                          GameOptions::windowHeight,
                          mWindowTitle,
                          GameOptions::fullscreen);
    
    // Use a view to make the game resolution independant
    CView theView(CFloatRect(GameOptions::viewLeft, GameOptions::viewTop,
                             GameOptions::viewWidth, GameOptions::viewHeight));

    // If we want to preserve the games original aspect ratio then set a viewport
    if (GameOptions::preserveAspect)
    {
        float vpLeft = 0.0f;
        float vpTop = 0.0f;
        float vpWidth = 1.0f;
        float vpHeight = 1.0f;

        float windowAspect = (float) GameOptions::windowWidth / (float) GameOptions::windowHeight;
        float viewAspect = GameOptions::viewWidth / GameOptions::viewHeight;

        if (windowAspect > viewAspect)
        {
            // The window aspect is wider than the view aspect
            // The viewport will use the full window height
            // Calculate what percentage of the view height that is
            float percent = (float) GameOptions::windowHeight / GameOptions::viewHeight;
            // Now use this to calculate the viewport width in pixels
            float vpWidthPx = GameOptions::viewWidth * percent;
            // Now work out what percent of the window width this is
            vpWidth = vpWidthPx / (float) GameOptions::windowWidth;

            // Now work out how far along the window we need to put this is order to center it
            vpLeft = (1.0f - vpWidth) / 2.0f;
        }
        else if (windowAspect < viewAspect)
        {
            // The window aspect is taller than the view aspect
            // Do similar calculations to above but in other dimension
            float percent = (float) GameOptions::windowWidth / GameOptions::viewWidth;
            float vpHeightPx = GameOptions::viewHeight * percent;
            vpHeight = vpHeightPx / (float) GameOptions::windowHeight;
            vpTop = (1.0f - vpHeight) / 2.0f;
        }

        theView.setViewport(CFloatRect(vpLeft, vpTop, vpWidth, vpHeight));
    }


    mWindow->setView(theView);
    
    if ((GameOptions::windowWidth * 1.0f) / GameOptions::windowHeight
        != GameOptions::viewWidth / GameOptions::viewHeight)
    {
        DEBUG_LOG("View aspect ratio doesn't match window aspect ratio");
    }
    
    // Enter the front end menu
    GoToLocation(kGameLocationFrontEnd);
    
    // Initialise other systems
    SystemUtilities::Init(mWindow);
    InitSFML(mWindow);
    
    // Create and register any lifetime updateables
#if SG_DEBUG
    theDebugHelper = new CDebugHelper();
    RegisterUpdateable(theDebugHelper);
#endif
}

// =============================================================================
// SwingGame::Run
// Enter the main loop, returns program exit code
// -----------------------------------------------------------------------------
int CSwingGame::Run()
{
    CClock  theUpdateClock;
#if !USE_SFML_VSYNC
    CClock  theRenderClock;
    CTime   timeSinceLastRender = CTime::Zero;
#endif
    
    while (mWindow->isOpen())
    {
        ProcessEvents();
        
        CTime timeSinceLastUpdate = theUpdateClock.restart();
        if (!mShouldSkipUpdateFrame)
        {
            Update(timeSinceLastUpdate);
        }
        mShouldSkipUpdateFrame = false;
       
#if !USE_SFML_VSYNC
        // Only render if vsync is off or enough time has past
        timeSinceLastRender += theRenderClock.restart();
        if (!GameOptions::doVsync
            || timeSinceLastRender.asSeconds() >= 1.0f / GameOptions::maxFPS)
        {
            timeSinceLastRender = CTime::Zero;
            Render();
        }
#else
        Render();
#endif
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
#if SG_DEBUG
    SAFE_DELETE(theDebugHelper);
#endif
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
        SUpdateableRegistrationRequest theRequest;
        theRequest.mShouldRegister = true;
        theRequest.mUpdateable = theUpdateable;
        smUpdateableRegistrationRequests.push_back(theRequest);
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
        SUpdateableRegistrationRequest theRequest;
        theRequest.mShouldRegister = false;
        theRequest.mUpdateable = theUpdateable;
        smUpdateableRegistrationRequests.push_back(theRequest);
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
// CSwingGame::GetDebugHelper
// -----------------------------------------------------------------------------
CDebugHelper * CSwingGame::GetDebugHelper()
{
#if SG_DEBUG
    return theDebugHelper;
#else
    return NULL;
#endif
}

// =============================================================================
// CSwingGame::GoToLocation
// Go to a game location (level/menu)
// -----------------------------------------------------------------------------
void CSwingGame::GoToLocation(EGameLocation theLocation,
                              std::string filename /* = std::string() */)
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
            smCurrentLocation = new CFrontEnd();
            break;
            
        case kGameLocationLevel:
            DEBUG_LOG("%s requested", filename.c_str());
            smCurrentLocation = new CLevel(filename);
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to front end");
            smCurrentLocation = new CFrontEnd();
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
    // Clear the last cycles keypress/mouse event list
    SystemUtilities::ClearInputEvents();
    
    CEvent theEvent;
    while (mWindow->pollEvent(theEvent))
    {
        switch (theEvent.type)
        {
            case CEvent::KeyPressed:
                // Hack to enable cmd+q / alt+f4 functionality
#if SG_MAC
                if (theEvent.key.code == CKeyboard::Q
                    && (CKeyboard::isKeyPressed(CKeyboard::LSystem)
                        || CKeyboard::isKeyPressed(CKeyboard::RSystem)))
                {
                    ExitGame();
                }
#elif SG_WINDOWS
                if (theEvent.key.code == CKeyboard::F4
                    && (CKeyboard::isKeyPressed(CKeyboard::LAlt)))
                {
                    ExitGame();
                }
#endif
                // Fall through to mouse press
                
            case CEvent::MouseButtonPressed:
                // Keep a list of key and mouse press events this cycle
                SystemUtilities::AddInputEvent(theEvent);
                break;
                
                
            case CEvent::Closed:
                // Exit on close event
                ExitGame();
                break;

            case CEvent::GainedFocus:
                smCurrentLocation->ReactToFocusGained();
                
                // Skip a frame when we gain focus
                mShouldSkipUpdateFrame = true;
                break;

            case CEvent::LostFocus:
                smCurrentLocation->ReactToFocusLost();
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
    
#if !USE_SFML_VSYNC
    // Count updates
    static int numUpdates;
    static CTime accumulatingElapsedTime;
    
    numUpdates++;
    accumulatingElapsedTime += elapsedTime;
    if (accumulatingElapsedTime.asSeconds() >= 1.0f) // Every second
    {
        mUPS = numUpdates;
        numUpdates = 0;
        accumulatingElapsedTime = CTime::Zero;
    }
#endif
    
#if SG_DEBUG
    if (DebugOptions::useSlowMotion)
    {
        elapsedTime /= 10.0f;
    }
#endif
    
    // Iterate through the registered updateables, updating each in turn
    FOR_EACH_IN_LIST(CUpdateable *, smTheUpdateables)
    {
        // Only update when in an appropriate state
        if ((*it)->ShouldUpdateForState(smGameState))
        {
            (*it)->Update(elapsedTime);
        }
    }
    
    // Add or remove any updateables that were requested this cycle
    while (!smUpdateableRegistrationRequests.empty())
    {
        SUpdateableRegistrationRequest thisRequest =
                                    smUpdateableRegistrationRequests.front();
        smUpdateableRegistrationRequests.pop_front();
        
        if (thisRequest.mShouldRegister)
        {
            smTheUpdateables.push_back(thisRequest.mUpdateable);
        }
        else
        {
            smTheUpdateables.remove(thisRequest.mUpdateable);
        }
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
        elapsedTime = CTime::Zero;
    }
    
    // Clear the window
    mWindow->clear();
    
    // Iterate through all registered renderables, drawing them all
    FOR_EACH_IN_LIST(CRenderable *, smTheRenderables)
    {
        (*it)->Draw(mWindow);
    }
    
    // In debug draw frame/update rate over everything else
#if SG_DEBUG
    if (DebugOptions::showFramerate)
    {
        std::stringstream theStream;
        theStream << "FPS: " << mFPS;
#if !USE_SFML_VSYNC
        theStream << std::endl << "UPS: " << mUPS;
#endif
        mWindow->DrawTextAt(theStream.str(),
                            GameOptions::viewWidth - 100,
                            5,
                            CColour::Red);
    }
    
    theDebugHelper->Draw(mWindow);
#endif
    
#if SG_DEBUG && 1
    mWindow->clear(CColour::White);
    
    // Square
    float length = 100.0f;
    std::list<CVector2f> points;
    points.push_back(CVector2f(-length, -length));
    points.push_back(CVector2f(-length, length));
    points.push_back(CVector2f(length, length));
    points.push_back(CVector2f(length, -length));
    CConvexShape square(points);
    square.setFillColor(CColour::Blue);
    square.setPosition(300.0f, 300.0f);
    
    // Triangle
    points.clear();
    points.push_back(CVector2f(0.0f, -length));
    points.push_back(CVector2f(length, length));
    points.push_back(CVector2f(-length, length));
    CConvexShape triangle(points);
    triangle.setFillColor(CColour::Black);
    triangle.setPosition(500.0f, 600.0f);
    
    // Circle
    CCircleShape circle(length);
    circle.setFillColor(CColour::Yellow);
    circle.setPosition(800.0f, 300.0f);
    
    mWindow->DrawShape(square);
    mWindow->DrawShape(triangle);
    mWindow->DrawShape(circle);
#endif
    
    // Display the new window contents
    mWindow->display();
}





