//
//  TextUtilties.cpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "TextUtilties.hpp"

namespace TextUtilities
{

// =============================================================================
// Namespace globals
// -----------------------------------------------------------------------------
CFont * theFonts[kFontTypeMax];

// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
std::string GetFontFileName(EFontType fontType)
{
    std::string theResult;
    
    switch (fontType)
    {
        case kFontTypeSansation:    // Fall through
        case kFontTypeDefault:      // Fall through
        default: theResult = "sansation.ttf";
    }
    
    return theResult;
}

// =============================================================================
// TextUtilities::GetFont
// Load or get the desired font
// -----------------------------------------------------------------------------
CFont * GetFont(EFontType fontType)
{
    // If this is the first time we're loading a font initialise smFonts
    static bool firstRun = true;
    if (firstRun)
    {
        firstRun = false;
        for (int i = 0; i < kFontTypeMax; i++)
            theFonts[i] = NULL;
    }
    
    // Load the font file if we haven't already
    if (theFonts[fontType] == NULL)
    {
        theFonts[fontType] = new CFont(GetFontFileName(fontType));
    }
    
    return theFonts[fontType];
}

// =============================================================================
// TextUtilities::DeleteFonts
// Delete all loaded fonts
// -----------------------------------------------------------------------------
void DeleteFonts()
{
    for (int i = 0; i < kFontTypeMax; i++)
        SAFE_DELETE(theFonts[i]);
}

// =============================================================================
// CTextUtilities::Cleanup
// Cleanup before quitting
// -----------------------------------------------------------------------------
void Cleanup()
{
    DeleteFonts();
}

} // namespace TextUtilities