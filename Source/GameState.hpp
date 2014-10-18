//
//  GameState.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_GameState_hpp
#define SwingGame_GameState_hpp

// =============================================================================
// Game state enum
// -----------------------------------------------------------------------------
enum EGameState
{
    kGameStateFrontEnd  = 1 << 0,
    kGameStateInGame    = 1 << 1,
    kGameStatePaused    = 1 << 2,
    kGameStateInactive  = 1 << 3,
    kGameStateUpdating  = 1 << 4
};

#endif
