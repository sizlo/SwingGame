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

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CWindow : public sf::RenderWindow
{
public:
    CWindow(unsigned int width, 
            unsigned int height, 
            std::string title,
            bool fullscreen);
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
    void DrawLine(CLine theLine, CColour theColour);
};

#endif /* defined(__SwingGame__CWindow__) */
