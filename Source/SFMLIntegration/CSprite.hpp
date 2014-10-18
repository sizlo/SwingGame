//
//  CSprite.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CSprite__
#define __SwingGame__CSprite__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSprite : public sf::Sprite
{
public:
    CSprite();
    CSprite(std::string filename);
    CSprite(std::string filename, bool flipX, bool flipY);
    ~CSprite();
};

#endif /* defined(__SwingGame__CSprite__) */
