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
#include "CDebugOptions.hpp"

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
// Draw a sprite
// Can also draw debug info like bounds and origin
// -----------------------------------------------------------------------------
void CWindow::DrawSprite(CSprite theSprite)
{
    draw(theSprite);
    
#if SG_DEBUG // Draw debug information
    // Draw the origin
    if (CDebugOptions::smDrawSpriteOrigins)
    {
        CVector2f theOrigin = theSprite.getPosition();
        sf::Vertex lines[] =
        {
            sf::Vertex(CVector2f(theOrigin.x-5, theOrigin.y), CColour::Red),
            sf::Vertex(CVector2f(theOrigin.x+5, theOrigin.y), CColour::Red),
            sf::Vertex(CVector2f(theOrigin.x, theOrigin.y-5), CColour::Red),
            sf::Vertex(CVector2f(theOrigin.x, theOrigin.y+5), CColour::Red)
        };
        draw(lines, 2, sf::Lines);
        draw(&lines[2], 2, sf::Lines);
    }
    
    // Draw the global bounds
    if (CDebugOptions::smDrawSpriteBounds)
    {
        sf::FloatRect theGlobalBounds = theSprite.getGlobalBounds();
        sf::RectangleShape theGlobalBoundsShape(
                    CVector2f(theGlobalBounds.width,theGlobalBounds.height));
        theGlobalBoundsShape.setPosition(theGlobalBounds.left,
                                         theGlobalBounds.top);
        theGlobalBoundsShape.setOutlineColor(CColour::Red);
        theGlobalBoundsShape.setOutlineThickness(1.0f);
        theGlobalBoundsShape.setFillColor(CColour::Transparent);
        draw(theGlobalBoundsShape);
    }
#endif
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


