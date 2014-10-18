//
//  CFont.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CFont__
#define __SwingGame__CFont__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

// =============================================================================
// Font type enum
// -----------------------------------------------------------------------------
enum EFontType
{
    kFontTypeSansation,
    kFontTypeDefault,
    kFontTypeMax
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CFont : public sf::Font
{
public:
    CFont(std::string filename);
    ~CFont();
};

#endif /* defined(__SwingGame__CFont__) */
