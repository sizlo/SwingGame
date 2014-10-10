//
//  Enums.hpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_Enums_hpp
#define SwingGame_Enums_hpp

// =============================================================================
// Font type
// -----------------------------------------------------------------------------
enum EFontType
{
    kFontTypeSansation,
    kFontTypeDefault,
    kFontTypeMax
};

// =============================================================================
// Game state
// -----------------------------------------------------------------------------
enum EGameState
{
    kGameStateFrontEnd  = 1 << 0,
    kGameStateInGame    = 1 << 1,
    kGameStatePaused    = 1 << 2,
    kGameStateInactive  = 1 << 3,
    kGameStateUpdating  = 1 << 4
};

// =============================================================================
// Game location
// -----------------------------------------------------------------------------
enum EGameLocation
{
    kGameLocationFrontEnd,
    kGameLocationLevel1
};

#endif
