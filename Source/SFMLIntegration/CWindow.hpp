//
//  CWindow.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CWindow__
#define __SwingGame__CWindow__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "CSprite.hpp"
#include "CColour.hpp"
#include "CConvexShape.hpp"
#include "CVector2.hpp"
#include "CFont.hpp"
#include "../DebugOptions.hpp"

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
#if SG_DEBUG

// Draw the origin of a transformable it is requested
#define DRAW_ORIGIN(transformable)                                          \
    if (DebugOptions::drawOrigins)                                          \
    {                                                                       \
        CVector2f theOrigin = transformable.getPosition();                  \
        DrawDebugPoint(theOrigin, CColour::Green);                          \
    }

// Draw the bounds of a transformable if it is requested
#define DRAW_BOUNDS(transformable)                                          \
    if (DebugOptions::drawBounds)                                           \
    {                                                                       \
        sf::FloatRect theGlobalBounds = transformable.getGlobalBounds();    \
        sf::RectangleShape theGlobalBoundsShape(                            \
                CVector2f(theGlobalBounds.width,theGlobalBounds.height));   \
        theGlobalBoundsShape.setPosition(theGlobalBounds.left,              \
                                         theGlobalBounds.top);              \
        theGlobalBoundsShape.setOutlineColor(CColour::Red);                 \
        theGlobalBoundsShape.setOutlineThickness(1.0f);                     \
        theGlobalBoundsShape.setFillColor(CColour::Transparent);            \
        draw(theGlobalBoundsShape);                                         \
    }                                                                       \

#else
    #define DRAW_ORIGIN(transformable)
    #define DRAW_BOUNDS(transformable)
#endif

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CWindow : public sf::RenderWindow
{
public:
    CWindow(unsigned int width, unsigned int height, std::string title);
    ~CWindow();
    // Draw text at a specific location on screen
    void DrawTextAt(std::string theString,
                    int x,
                    int y,
                    CColour theColour = CColour::Black,
                    unsigned int fontSize = 12,
                    EFontType fontType = kFontTypeDefault);
    // Draw a sprite
    void DrawSprite(CSprite theSprite);
    // Draw a shape
    void DrawShape(CConvexShape theShape);
    // Draw a point
    void DrawDebugPoint(CVector2f thePoint, CColour theColour = CColour::Red);
    // Draw a 1 pixel wide line
    void DrawLine(CVector2f start, CVector2f end, CColour theColour);
};

#endif /* defined(__SwingGame__CWindow__) */
