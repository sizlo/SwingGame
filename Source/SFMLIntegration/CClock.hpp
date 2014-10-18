//
//  CClock.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CClock__
#define __SwingGame__CClock__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CClock : public sf::Clock
{
public:
    CClock();
    ~CClock();
};

#endif /* defined(__SwingGame__CClock__) */
