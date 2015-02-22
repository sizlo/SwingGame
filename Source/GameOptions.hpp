//
//  GameOptions.hpp
//  SwingGame
//
//  Created by Tim Brier on 05/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__GameOptions__
#define __SwingGame__GameOptions__

// =============================================================================
// namespace definition
// -----------------------------------------------------------------------------
namespace GameOptions
{
    // Public globals
    extern unsigned int windowHeight;
    extern unsigned int windowWidth;
    extern float        viewLeft;
    extern float        viewTop;
    extern float        viewHeight;
    extern float        viewWidth;
    extern bool         doVsync;
    extern unsigned int maxFPS;

    extern void Init();
};

#endif /* defined(__SwingGame__GameOptions__) */
