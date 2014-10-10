//
//  TextUtilties.hpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__TextUtilties__
#define __SwingGame__TextUtilties__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"
#include "Enums.hpp"

// =============================================================================
// Namespace Definition
// -----------------------------------------------------------------------------
namespace TextUtilities
{
    // Load or get the desired font
    CFont * GetFont(EFontType fontType);
    // Delete all loaded fonts
    void DeleteFonts();
    
    // Cleanup before quitting
    void Cleanup();
};

#endif /* defined(__SwingGame__TextUtilties__) */
