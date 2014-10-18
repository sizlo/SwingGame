//
//  CMusic.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CMusic__
#define __SwingGame__CMusic__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Audio.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CMusic : public sf::Music
{
public:
    CMusic(std::string filename);
    ~CMusic();
};

#endif /* defined(__SwingGame__CMusic__) */
