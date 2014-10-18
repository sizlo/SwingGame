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
    
    // Normalise the normal vactor
    mNormal.Normalise();
}

CLine::~CLine()
{
    
}

// =============================================================================
// CLine::GetStart
// -----------------------------------------------------------------------------
CVector2f CLine::GetStart()
{
    return mStart;
}

// =============================================================================
// CLine::GetEnd
// -----------------------------------------------------------------------------
CVector2f CLine::GetEnd()
{
    return mEnd;
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

// =============================================================================
// CLine::Intersects
// Does the given line intersect this line
// -----------------------------------------------------------------------------
bool CLine::Intersects(CLine other)
{
    bool theResult = false;
    
    // First check that the lines would intersect if they were infinitely long
    // Use the equation from
    // http://devmag.org.za/2009/04/13/basic-collision-detection-in-2d-part-1/
    float otherDY = other.GetEnd().y - other.GetStart().y;
    float otherDX = other.GetEnd().x - other.GetStart().x;
    float thisDY = mEnd.y - mStart.y;
    float thisDX = mEnd.x - mStart.x;
    
    float denominator = (otherDY * thisDX) - (otherDX * thisDY);
    
    // If this denominator is 0 then the lines are parallel, any other value
    // and the lines would intersect at some point if they were of infinite
    // length
    if (denominator != 0.0f)
    {
        // Find the intersection point and make sure it lies between the start
        // and end of each respective line
        float otherToThisStartY = mStart.y - other.GetStart().y;
        float otherToThisStartX = mStart.x - other.GetStart().x;
        
        float percentageAlongThisLine =     ((otherDX * otherToThisStartY)
                                             - (otherDY * otherToThisStartX))
                                            / denominator;
        float percentageAlongOtherLine =    ((thisDX * otherToThisStartY)
                                             - (thisDY * otherToThisStartX))
                                            / denominator;
        
        if (percentageAlongThisLine >= 0.0f
            && percentageAlongThisLine <= 1.0f
            && percentageAlongOtherLine >= 0.0f
            && percentageAlongOtherLine <= 1.0f)
        {
            // This point lies on both lines so we have an intersection
            theResult = true;
        }
    }
    
    return theResult;
}