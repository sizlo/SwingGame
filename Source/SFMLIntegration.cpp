//
//  SFMLIntegration.cpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"
#include "CTextUtilties.hpp"
#include "ResourcePath.hpp"

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

// =============================================================================
// CWindow constructor/destructor
// -----------------------------------------------------------------------------
CWindow::CWindow(unsigned int width, unsigned int height, std::string title)
: sf::RenderWindow(sf::VideoMode(width, height), title)
{
    
}

CWindow::~CWindow()
{
    
}

// =============================================================================
// CWindow::DrawTextAt
// Draws text at a given location in the window
// -----------------------------------------------------------------------------
void CWindow::DrawTextAt(std::string theString,
                         int x,
                         int y,
                         CColour theColour /* = CColour::Black */,
                         unsigned int fontSize /* = 12 */,
                         EFontType fontType /* = kFontTypeDefault */)
{
    CFont *theFont = NULL;
    theFont = CTextUtilities::GetFont(fontType);
    
    CText theText(theString, *theFont, fontSize);
    theText.setColor(theColour);
    theText.setPosition((float) x, (float) y);
    
    draw(theText);
}

// =============================================================================
// CFont constructor/destructor
// -----------------------------------------------------------------------------
// Loads the font from the given filename
CFont::CFont(std::string filename)
{
    if (!loadFromFile(resourcePath() + filename))
        DEBUG_LOG("Error loading font file: %s", filename.c_str());
}

CFont::~CFont()
{
    
}

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


