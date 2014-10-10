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
#include "TextUtilties.hpp"
#include "SystemUtilities.hpp"
#include "CTextureBank.hpp"
#include "DebugOptions.hpp"

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
: sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close)
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
    theFont = TextUtilities::GetFont(fontType);
    
    CText theText(theString, *theFont, fontSize);
    theText.setColor(theColour);
    theText.setPosition((float) x, (float) y);
    
    draw(theText);
}

// =============================================================================
// CWindow::DrawSprite
// Draw a sprite with any requested debug info
// -----------------------------------------------------------------------------
void CWindow::DrawSprite(CSprite theSprite)
{
    draw(theSprite);
    
    // Draw debug info
    DRAW_ORIGIN(theSprite);
    DRAW_BOUNDS(theSprite);
}

// =============================================================================
// CWindow::DrawShape
// Draw a shape with any requested debug info
// -----------------------------------------------------------------------------
void CWindow::DrawShape(CConvexShape theShape)
{
    draw(theShape);
    
    // Draw debug info
    DRAW_ORIGIN(theShape);
    DRAW_BOUNDS(theShape);
}

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

// =============================================================================
// CClock constructor/destructor
// -----------------------------------------------------------------------------
CClock::CClock() : sf::Clock()
{
    
}

CClock::~CClock()
{
    
}

// =============================================================================
// CSprite constructor/destructor
// -----------------------------------------------------------------------------
CSprite::CSprite() : sf::Sprite()
{
    
}

CSprite::CSprite(std::string filename) : sf::Sprite()
{
    CTexture *theTexture = CTextureBank::GetTexture(filename);
    setTexture(*theTexture);
}

CSprite::CSprite(std::string filename, bool flipX, bool flipY) : sf::Sprite()
{
    CTexture *theTexture = CTextureBank::GetTexture(filename, flipX, flipY);
    setTexture(*theTexture);
}


CSprite::~CSprite()
{

}

// =============================================================================
// CConvexShape constructor/destructor
// -----------------------------------------------------------------------------
CConvexShape::CConvexShape(unsigned int pointCount /* = 0 */)
: sf::ConvexShape(pointCount)
{
    
}

CConvexShape::CConvexShape(std::list<CVector2f> &thePoints)
: sf::ConvexShape(thePoints.size())
{
    int theIndex = 0;
    
    for (std::list<CVector2f>::iterator it = thePoints.begin();
         it != thePoints.end();
         ++it)
    {
        setPoint(theIndex, (*it));
        theIndex++;
    }
}

CConvexShape::~CConvexShape()
{
    
}

// =============================================================================
// CImage constructor/destructor
// -----------------------------------------------------------------------------
CImage::CImage() : sf::Image()
{
    
}

CImage::~CImage()
{
    
}

// =============================================================================
// CTexture constructor/destructor
// -----------------------------------------------------------------------------
CTexture::CTexture() : sf::Texture()
{
    
}

CTexture::~CTexture()
{
    
}


