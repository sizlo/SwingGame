//
//  CText.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CText.hpp"

// =============================================================================
// CText constructor/destructor
// -----------------------------------------------------------------------------
CText::CText(std::string theString, CFont &theFont, unsigned int theFontSize /* = 12 */)
: sf::Text(theString, theFont, theFontSize)
{
    
}

CText::~CText()
{
    
}