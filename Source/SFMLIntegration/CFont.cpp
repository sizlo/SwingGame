//
//  CFont.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CFont.hpp"
#include "../SystemUtilities.hpp"

// =============================================================================
// CFont constructor/destructor
// -----------------------------------------------------------------------------
// Loads the font from the given filename
CFont::CFont(std::string filename) : sf::Font()
{
    bool result = loadFromFile(SystemUtilities::GetResourcePath() + filename);
    if (!result)
    {
        DEBUG_LOG("Error loading font file: %s", filename.c_str());
    }
}

CFont::~CFont()
{
    
}