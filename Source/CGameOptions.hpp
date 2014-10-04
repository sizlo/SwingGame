//
//  CGameOptions.hpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CGameOptions_hpp
#define SwingGame_CGameOptions_hpp

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CGameOptions
{
public:
    static unsigned int smWindowHeight;
    static unsigned int smWindowWidth;
    static bool         smVsync;
    static unsigned int smMaxFPS;
};

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
unsigned int    CGameOptions::smWindowHeight    = 768;
unsigned int    CGameOptions::smWindowWidth     = 1024;
bool            CGameOptions::smVsync           = true;
unsigned int    CGameOptions::smMaxFPS          = 60;

#endif
