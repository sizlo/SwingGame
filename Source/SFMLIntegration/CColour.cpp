//
//  CColour.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CColour.hpp"

// =============================================================================
// CColour constructors/destructors
// -----------------------------------------------------------------------------
CColour::CColour(sf::Uint8 red,
                 sf::Uint8 green,
                 sf::Uint8 blue,
                 sf::Uint8 alpha /* = 255 */)
: sf::Color(red, green, blue, alpha)
{
    
}

CColour::CColour(sf::Color theColour)
: sf::Color(theColour.r, theColour.g, theColour.b, theColour.a)
{
    
}

CColour::~CColour()
{
    
}