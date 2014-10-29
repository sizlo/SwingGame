//
//  SFMLIntegration.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_SFMLIntegration_hpp
#define SwingGame_SFMLIntegration_hpp

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CClock.hpp"
#include "CColour.hpp"
#include "CEvent.hpp"
#include "CFloatRect.hpp"
#include "CImage.hpp"
#include "CKeyboard.hpp"
#include "CMouse.hpp"
#include "CTexture.hpp"
#include "CTime.hpp"
#include "CVector2.hpp"
#include "CFont.hpp"
#include "CMusic.hpp"
#include "CConvexShape.hpp"
#include "CSprite.hpp"
#include "CText.hpp"
#include "CWindow.hpp"
#include "CView.hpp"

#include "../GameOptions.hpp"


// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
static void InitSFML(sf::Window *theWindow)
{
    // When we're not in debug mode redirect SFML errors to nowhere
#if !SG_DEBUG
    sf::err().rdbuf(NULL);
#endif
    
    // Don't repeat keypress events
    theWindow->setKeyRepeatEnabled(false);
    
#if USE_SFML_VSYNC
    // Set frame rate limit
    if (GameOptions::doVsync)
    {
        theWindow->setFramerateLimit(GameOptions::maxFPS);
    }
#endif
}

#endif
