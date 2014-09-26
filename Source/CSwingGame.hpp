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

// =============================================================================
// Enums
// -----------------------------------------------------------------------------
enum EGameState
{
    kGameStateFrontEnd  = 1 << 0,
    kGameStateInGame    = 1 << 1,
    kGameStatePaused    = 1 << 2,
    kGameStateInactive  = 1 << 3
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
    
    // Set/unset GameState flags
    void SetGameState       (EGameState theState);
    void UnsetGameState     (EGameState theState);
    // Returns true only if the current gamestate has all the given flags
    bool HasAllGameStates   (EGameState theState);
    
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
    
    // The current game state
    EGameState mGameState;
    
    // Temporary
    CSprite *mSprite;
};


#endif /* defined(__SwingGame__SwingGame__) */
