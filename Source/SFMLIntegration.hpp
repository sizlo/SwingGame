//
//  SFMLIntegration.hpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__SFMLIntegration__
#define __SwingGame__SFMLIntegration__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "Enums.hpp"
#include <list>

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
// Typedefs
// -----------------------------------------------------------------------------
// The SFML Time interface doesn't provide anyway of constructing a Time object
// with an initial value or setting the value so I can't create a conversion
// from sf::Time to a derived class. I don't imagine I'll need to add any
// extensions to this so a typedef should do
typedef sf::Time CTime;

// I won't need to extend vectors in any way
typedef sf::Vector2f CVector2f;
typedef sf::Vector2i CVector2i;

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CSprite;
class CConvexShape;
class CLine;

// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
static void InitSFML(sf::RenderWindow *theWindow)
{
    // When we're not in debug mode redirect SFML errors to nowhere
#if !SG_DEBUG
    sf::err().rdbuf(NULL);
#endif
    
    // Don't repeat keypress events
    theWindow->setKeyRepeatEnabled(false);
}

class CColour : public sf::Color
{
public:
    CColour(sf::Uint8 red,
            sf::Uint8 green,
            sf::Uint8 blue,
            sf::Uint8 alpha = 255);
    CColour(sf::Color theColour);
    ~CColour();
};

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
};

class CFont : public sf::Font
{
public:
    CFont(std::string filename);
    ~CFont();
};

class CText : public sf::Text
{
public:
    CText(std::string theString, CFont &theFont, unsigned int fontSize = 12);
    ~CText();
};

class CEvent : public sf::Event
{
    
};

class CClock : public sf::Clock
{
public:
    CClock();
    ~CClock();
};

class CSprite : public sf::Sprite
{
public:
    CSprite();
    CSprite(std::string filename);
    CSprite(std::string filename, bool flipX, bool flipY);
    ~CSprite();
};

class CConvexShape : public sf::ConvexShape
{
public:
    CConvexShape(unsigned int pointCount = 0);
    CConvexShape(std::list<CVector2f> &thePoints);
    ~CConvexShape();
    // Build and return a list of lines within the shape
    std::list<CLine> GetGlobalLines();
};

class CTexture : public sf::Texture
{
public:
    CTexture();
    ~CTexture();
};

class CImage : public sf::Image
{
public:
    CImage();
    ~CImage();
};

class CKeyboard : public sf::Keyboard
{
    // Static class, no constructors
};

class CMouse : public sf::Mouse
{
    // Static class, no constructors
};

#endif /* defined(__SwingGame__SFMLIntegration__) */
