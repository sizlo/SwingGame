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
// CTime::Seconds
// -----------------------------------------------------------------------------
CTime CTime::Seconds(float amount)
{
    return sf::seconds(amount);
}