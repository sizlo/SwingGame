//
//  CTextUtilties.cpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CTextUtilties.hpp"

// =============================================================================
// Static member variables
// -----------------------------------------------------------------------------
CFont * CTextUtilities::smFonts[kFontTypeMax];

// =============================================================================
// CTextUtilities::GetFont
// Load or get the desired font
// -----------------------------------------------------------------------------
CFont * CTextUtilities::GetFont(EFontType fontType)
{
    // If this is the first time we're loading a font initialise smFonts
    static bool firstRun = true;
    if (firstRun)
    {
        firstRun = false;
        for (int i = 0; i < kFontTypeMax; i++)
            smFonts[i] = NULL;
    }
    
    // Load the font file if we haven't already
    if (smFonts[fontType] == NULL)
    {
        smFonts[fontType] = new CFont(GetFontFileName(fontType));
    }
    
    return smFonts[fontType];
}

// =============================================================================
// CTextUtilities::DeleteFonts
// Delete all loaded fonts
// -----------------------------------------------------------------------------
void CTextUtilities::DeleteFonts()
{
    for (int i = 0; i < kFontTypeMax; i++)
        SAFE_DELETE(smFonts[i]);
}

// =============================================================================
// CTextUtilities::GetFontFileName
// -----------------------------------------------------------------------------
std::string CTextUtilities::GetFontFileName(EFontType fontType)
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
// CTextUtilities::Cleanup
// Cleanup before quitting
// -----------------------------------------------------------------------------
void CTextUtilities::Cleanup()
{
    DeleteFonts();
}