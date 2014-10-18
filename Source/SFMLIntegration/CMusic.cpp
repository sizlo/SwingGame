//
//  CMusic.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CMusic.hpp"
#include "../SystemUtilities.hpp"

// =============================================================================
// CMusic constructor/destructor
// -----------------------------------------------------------------------------
CMusic::CMusic(std::string filename) : sf::Music()
{
    openFromFile(SystemUtilities::GetResourcePath() + filename);
}

CMusic::~CMusic()
{
    
}