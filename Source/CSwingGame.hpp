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
#include "SFMLIntegration.hpp"
#include "CTextUtilties.hpp"
#include "CUpdateable.hpp"
#include "CDrawable.hpp"
#include "CMenu.hpp"
#include <list>

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
    
    // Register/unregister updatable/drawables
    static void RegisterUpdateable  (CUpdateable    *theUpdateable);
    static void RegisterDrawable    (CDrawable      *theDrawable);
    static void UnregisterUpdateable(CUpdateable    *theUpdateable);
    static void UnregisterDrawable  (CDrawable      *theDrawable);
    
    // Was a keypress event recieved for the given key this cycle
    static bool WasKeyPressedThisCycle(CKeyboard::Key theKey);
    
private:
    // Process all events recieved this cylce
    void ProcessEvents();
    // Update all CUpdatables registered
    void Update(CTime elapsedTime);
    // Render all CRenderables registered
    void Render();
    
    // The game window
    const unsigned int mWindowWidth;
    const unsigned int mWindowHeight;
    std::string mWindowTitle;
    CWindow *mWindow;
    
    // The code returned on program exit
    int mExitCode;
    // Has an exit been requested
    static bool smExitRequested;
    
    // The current game state
    static EGameState smGameState;
    
    // Updateable and drawable lists
    static std::list<CUpdateable *> smTheUpdateables;
    static std::list<CUpdateable *> smTheUpdateablesToRemove;
    static std::list<CDrawable *>   smTheDrawables;
    
    // Key/mouse event lists
    static std::list<CEvent> smTheKeyPresses;
    
    // The front end menu
    CMenu *mFrontEndMenu;
};


#endif /* defined(__SwingGame__SwingGame__) */
