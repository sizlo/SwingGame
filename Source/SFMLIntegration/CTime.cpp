//
//  CTime.cpp
//  ParticleSystem
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CTime.hpp"
#include <math.h>

// =============================================================================
// CTime constructor/destructor
// -----------------------------------------------------------------------------
CTime::CTime() : sf::Time()
{
    
}

CTime::CTime(sf::Time other) : sf::Time(other)
{
    
}

CTime::~CTime()
{
    
}

// =============================================================================
// CTime::AsString
// Return a string in the format ss:mmm
// -----------------------------------------------------------------------------
std::string CTime::AsString()
{
    char str[16];
    int seconds = floor(asSeconds());
    int millis = asMilliseconds() - (seconds * 1000);
    sprintf(str, "%02d:%03d", seconds, millis);
    
    std::string theResult = str;
    return theResult;
}

// =============================================================================
// CTime::Seconds
// -----------------------------------------------------------------------------
CTime CTime::Seconds(float amount)
{
    return sf::seconds(amount);
}