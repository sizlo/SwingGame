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
#include "FontEnums.hpp"

// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
static void InitSFML()
{
    // When we're not in debug mode redirect SFML errors to nowhere
#if !SG_DEBUG
    sf::err().rdbuf(NULL);
#endif
}

// =============================================================================
// Class Definitions
// -----------------------------------------------------------------------------
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

// The SFML Time interface doesn't provide anyway of constructing a Time object
// with an initial value or setting the value so I can't create a conversion
// from sf::Time to a derived class. I don't imagine I'll need to add any
// extensions to this so a typedef should do
typedef sf::Time CTime;

class CClock : public sf::Clock
{
public:
    CClock();
    ~CClock();
};

class CSprite : public sf::Sprite
{
public:
    CSprite(std::string filename);
    ~CSprite();
    
private:
    sf::Texture *mTexture;
};


#endif /* defined(__SwingGame__SFMLIntegration__) */
