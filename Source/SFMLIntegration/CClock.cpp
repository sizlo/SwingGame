//
//  CClock.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CClock.hpp"

// =============================================================================
// CClock constructor/destructor
// -----------------------------------------------------------------------------
CClock::CClock() : sf::Clock()
{
    
}

CClock::~CClock()
{
    
}

// =============================================================================
// CPauseableClock constructor/destructor
// -----------------------------------------------------------------------------
CPauseableClock::CPauseableClock() : CClock()
{
    mAccumulatedTime = CTime::Zero;
    mPaused = false;
}

CPauseableClock::~CPauseableClock()
{
    
}

// =============================================================================
// CPauseableClock::Restart
// -----------------------------------------------------------------------------
CTime CPauseableClock::Restart()
{
    CTime elapsedTime = GetElapsedTime();
    mPaused = false;
    mAccumulatedTime = CTime::Zero;
    restart();
    return elapsedTime;
}

// =============================================================================
// CPauseableClock::Pause
// -----------------------------------------------------------------------------
CTime CPauseableClock::Pause()
{
    if (!mPaused)
    {
        mPaused = true;
        mAccumulatedTime += getElapsedTime();
    }
    
    return mAccumulatedTime;
}

// =============================================================================
// CPauseableClock::Resume
// -----------------------------------------------------------------------------
CTime CPauseableClock::Resume()
{
    CTime elapsedTime = GetElapsedTime();
    
    if (mPaused)
    {
        mPaused = false;
        restart();
    }
    
    return elapsedTime;
}

// =============================================================================
// CPauseableClock::GetElapsedTime
// -----------------------------------------------------------------------------
CTime CPauseableClock::GetElapsedTime()
{
    CTime elapsedTime = mAccumulatedTime;
    if (!mPaused)
    {
        elapsedTime += getElapsedTime();
    }
    return elapsedTime;
}