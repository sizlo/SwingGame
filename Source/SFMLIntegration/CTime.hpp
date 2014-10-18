//
//  CTime.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CTime__
#define __SwingGame__CTime__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/System.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CTime : public sf::Time
{
public:
    CTime();
    CTime(sf::Time other);
    ~CTime();
};

#endif /* defined(__SwingGame__CTime__) */
