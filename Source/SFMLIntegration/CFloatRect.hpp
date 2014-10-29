//
//  CFloatRect.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CFloatRect__
#define __SwingGame__CFloatRect__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CFloatRect : public sf::FloatRect
{
public:
    CFloatRect();
    CFloatRect(sf::FloatRect other);
    CFloatRect(float left, float top, float width, float height);
    ~CFloatRect();
};

#endif /* defined(__SwingGame__CFloatRect__) */
