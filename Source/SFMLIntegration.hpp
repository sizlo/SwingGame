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


#endif /* defined(__SwingGame__SFMLIntegration__) */
