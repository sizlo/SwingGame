//
//  CTextUtilties.hpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CTextUtilties__
#define __SwingGame__CTextUtilties__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"
#include "Enums.hpp"

// =============================================================================
// Class Definition
// -----------------------------------------------------------------------------
class CTextUtilities
{
public:
    // Load or get the desired font
    static CFont * GetFont(EFontType fontType);
    // Delete all loaded fonts
    static void DeleteFonts();
    
    // Cleanup before quitting
    static void Cleanup();
    
private:
    static std::string GetFontFileName(EFontType fontType);
    
    static CFont *smFonts[kFontTypeMax];
};

#endif /* defined(__SwingGame__CTextUtilties__) */
