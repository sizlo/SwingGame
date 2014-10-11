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
#include "CLine.hpp"

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
CWindow::CWindow(   unsigned int width,
                    unsigned int height,
                    std::string title)
: sf::RenderWindow( sf::VideoMode(width, height),
                    title,
                    sf::Style::Close,
                    sf::ContextSettings(0, 0, 8)) // 8XAA
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
// CWindow::DrawDebugPoint
// Draw a cross at a position
// -----------------------------------------------------------------------------
void CWindow::DrawDebugPoint(const CVector2f thePoint,
                             CColour theColour /* = CColour::Red */)
{
    sf::Vertex lines[] =
    {
        sf::Vertex(CVector2f(thePoint.x-5,  thePoint.y),    theColour),
        sf::Vertex(CVector2f(thePoint.x+5,  thePoint.y),    theColour),
        sf::Vertex(CVector2f(thePoint.x,    thePoint.y-5),  theColour),
        sf::Vertex(CVector2f(thePoint.x,    thePoint.y+5),  theColour)
    };
    draw(lines, 2, sf::Lines);
    draw(&lines[2], 2, sf::Lines);
}

// =============================================================================
// CWindow::DrawSprite
// Draw a sprite with any requested debug info
// -----------------------------------------------------------------------------
void CWindow::DrawSprite(CSprite theSprite)
{
    draw(theSprite);
    
    // Draw debug info
    DRAW_BOUNDS(theSprite);
    DRAW_ORIGIN(theSprite);
}

// =============================================================================
// CWindow::DrawShape
// Draw a shape with any requested debug info
// -----------------------------------------------------------------------------
void CWindow::DrawShape(CConvexShape theShape)
{
    draw(theShape);
    
    // Draw debug info
    DRAW_BOUNDS(theShape);
    DRAW_ORIGIN(theShape);
    
#if SG_DEBUG
    // Draw each point of the shape
    if (DebugOptions::drawShapePoints)
    {
        for (int i = 0; i < theShape.getPointCount(); i++)
        {
            DrawDebugPoint(theShape.getPosition() + theShape.getPoint(i));
        }
    }
    
    // Draw the normal to all lines
    if (DebugOptions::drawShapeNormals)
    {
        std::list<CLine> theLines = theShape.GetGlobalLines();
        for (std::list<CLine>::iterator it = theLines.begin();
             it != theLines.end();
             ++it)
        {
            CVector2f normal = (*it).GetNormal();
            CVector2f start = (*it).GetMidpoint();
            CVector2f end = start + 5.0f * normal;
            
            sf::Vertex line[] =
            {
                sf::Vertex(start,   CColour::Red),
                sf::Vertex(end,     CColour::Red)
            };
            draw(line, 2, sf::Lines);
        }
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
// CConvexShape::GetLines
// Build and return a list of lines within the shape using global coords
// -----------------------------------------------------------------------------
std::list<CLine> CConvexShape::GetGlobalLines()
{
    std::list<CLine> theResult;
    
    int numPoints = getPointCount();
    CVector2f pos = getPosition();
    
    for (int i = 0; i < numPoints; i++)
    {
        CVector2f start = pos + getPoint(i);
        CVector2f end = pos + getPoint((i+1) % numPoints);
        
        theResult.push_back(CLine(start, end));
    }
    
    return theResult;
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


