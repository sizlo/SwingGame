//
//  CLine.cpp
//  SwingGame
//
//  Created by Tim Brier on 10/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CLine.hpp"
#include <math.h>

// =============================================================================
// CLine constructor/destructor
// -----------------------------------------------------------------------------
CLine::CLine(CVector2f start, CVector2f end) :  mStart(start),
                                                mEnd(end)
{
    // Find the direction of the normal vector
    CVector2f startToEnd = mEnd - mStart;
    mNormal.x = startToEnd.y;
    mNormal.y = -startToEnd.x;
    
    // Normalise the normal vector
    float normalLength = sqrt(mNormal.x * mNormal.x
                              + mNormal.y * mNormal.y);
    mNormal.x /= normalLength;
    mNormal.y /= normalLength;
}

CLine::~CLine()
{
    
}

// =============================================================================
// CLine::GetMidpoint
// -----------------------------------------------------------------------------
CVector2f CLine::GetMidpoint()
{
    CVector2f theResult;
    
    CVector2f startToEnd;
    startToEnd.x = mEnd.x - mStart.x;
    startToEnd.y = mEnd.y - mStart.y;
    
    theResult.x = mStart.x + (startToEnd.x / 2.0f);
    theResult.y = mStart.y + (startToEnd.y / 2.0f);
    
    return theResult;
}

// =============================================================================
// CLine::GetNormal
// -----------------------------------------------------------------------------
CVector2f CLine::GetNormal()
{
    return mNormal;
}