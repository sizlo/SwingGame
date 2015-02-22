//
//  SwingGame.hpp
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__SwingGame__
#define __SwingGame__SwingGame__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"
#include "TextUtilties.hpp"
#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "GameState.hpp"
#include <list>

// =============================================================================
// Forward Declarations
// -----------------------------------------------------------------------------
class CDebugHelper;

// =============================================================================
// Structs
// -----------------------------------------------------------------------------
struct SUpdateableRegistrationRequest
{
    bool            mShouldRegister;
    CUpdateable     *mUpdateable;
};

// =============================================================================
// Class Definition
// -----------------------------------------------------------------------------
class CSwingGame
{
public:
    CSwingGame();
    ~CSwingGame();
    
    // Initialise the game
    void Init();
    // Enter the main loop, returns program exit code
    int Run();
    // Cleanup before quitting
    void Cleanup();
    
    // Exit the game
    static void ExitGame();
    
    // Set/unset GameState flags
    static void SetGameState       (EGameState theState);
    static void UnsetGameState     (EGameState theState);
    // Returns true only if the current gamestate has all the given flags
    static bool HasAllGameStates   (EGameState theState);
    
    // Register/unregister updatable/renderables
    static void RegisterUpdateable  (CUpdateable    *theUpdateable);
    static void RegisterRenderable  (CRenderable    *theRenderable);
    static void UnregisterUpdateable(CUpdateable    *theUpdateable);
    static void UnregisterRenderable(CRenderable    *theRenderable);
    
    // Go to a game location
    static void GoToLocation(EGameLocation theLocation,
                             std::string filename = std::string());
    
    static CDebugHelper * GetDebugHelper();
private:
    // Process all events recieved this cylce
    void ProcessEvents();
    // Update all CUpdatables registered
    void Update(CTime elapsedTime);
    // Render all CRenderables registered
    void Render();
    
    // The game window
    std::string mWindowTitle;
    CWindow *mWindow;
    
    // Frames per second and updates per second
    int mFPS;
#if !USE_SFML_VSYNC
    int mUPS;
#endif

    // When set we won't run one update cycle
    bool mShouldSkipUpdateFrame;
    
    // The code returned on program exit
    int mExitCode;
    // Has an exit been requested
    static bool smExitRequested;
    
    // The current game state
    static EGameState smGameState;
    
    // Updateable and renderable lists
    static std::list<CUpdateable *> smTheUpdateables;
    static std::list<SUpdateableRegistrationRequest>
                                    smUpdateableRegistrationRequests;
    static std::list<CRenderable *> smTheRenderables;
    
    // The current game location (menu/level)
    static CGameLocation *smCurrentLocation;
};


#endif /* defined(__SwingGame__SwingGame__) */
