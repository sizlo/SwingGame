//
//  CText.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CText__
#define __SwingGame__CText__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "CFont.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CText : public sf::Text
{
public:
    CText(std::string theString, CFont &theFont, unsigned int fontSize = 12);
    ~CText();
};

#endif /* defined(__SwingGame__CText__) */
