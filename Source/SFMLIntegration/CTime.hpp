//
//  CTime.hpp
//  ParticleSystem
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __ParticleSystem__CTime__
#define __ParticleSystem__CTime__

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
    
    std::string AsString();
    
    // Create a CTime with the given seconds
    static CTime Seconds(float amount);
};

#endif /* defined(__ParticleSystem__CTime__) */
