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
#include "../TextUtilties.hpp"

// =============================================================================
// CText constructor/destructor
// -----------------------------------------------------------------------------
CText::CText() : sf::Text()
{
    
}

CText::CText(std::string theString, CFont &theFont, unsigned int theFontSize /* = 12 */)
: sf::Text(theString, theFont, theFontSize)
{
    
}

CText::CText(std::string theString, CVector2f thePos, unsigned int theFontSize /* = 12 */)
: sf::Text(theString, *TextUtilities::GetFont(kFontTypeDefault), theFontSize)
{
    setPosition(thePos);
}

CText::~CText()
{
    
}