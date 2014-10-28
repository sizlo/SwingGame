//
//  CConvexShape.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CConvexShape.hpp"

// =============================================================================
// CConvexShape constructor/destructor
// -----------------------------------------------------------------------------
CConvexShape::CConvexShape(unsigned int pointCount /* = 0 */)
: sf::ConvexShape(pointCount)
{
    
}

CConvexShape::CConvexShape(std::list<CVector2f> &thePoints)
: sf::ConvexShape(thePoints.size())
{
    int theIndex = 0;
    
    for (std::list<CVector2f>::iterator it = thePoints.begin();
         it != thePoints.end();
         ++it)
    {
        setPoint(theIndex, (*it));
        theIndex++;
    }
}

CConvexShape::~CConvexShape()
{
    
}

// =============================================================================
// CConvexShape::GetLines
// Build and return a list of lines within the shape using global coords
// -----------------------------------------------------------------------------
std::list<CLine> CConvexShape::GetGlobalLines()
{
    std::list<CLine> theResult;
    
    int numPoints = getPointCount();
    CVector2f pos = getPosition();
    
    for (int i = 0; i < numPoints; i++)
    {
        CVector2f start = pos + getPoint(i);
        CVector2f end = pos + getPoint((i+1) % numPoints);
        
        theResult.push_back(CLine(start, end));
    }
    
    return theResult;
}

// =============================================================================
// CConvexShape::GetGlobalPoint
// Get the indexth point in the shape in global coords
// -----------------------------------------------------------------------------
CVector2f CConvexShape::GetGlobalPoint(unsigned int index)
{
    return getPosition() + getPoint(index);
}