//
//  CWindow.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CWindow.hpp"
#include "../TextUtilties.hpp"
#include "CText.hpp"
#include "../CLine.hpp"

// =============================================================================
// CWindow constructor/destructor
// -----------------------------------------------------------------------------
CWindow::CWindow(unsigned int width,
                 unsigned int height,
                 std::string title)
: sf::RenderWindow(sf::VideoMode(width, height),
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
            DrawDebugPoint(theShape.GetGlobalPoint(i));
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
