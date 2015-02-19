//
//  CCircleShape.cpp
//  SwingGame
//
//  Created by Tim Brier on 19/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CCircleShape.hpp"
#include "CVector2.hpp"

// =============================================================================
// CCircleShape construcotr/destructor
// -----------------------------------------------------------------------------
CCircleShape::CCircleShape(float radius, int pointcount /* = 30 */)
: CConvexShape(pointcount)
{
    // Create a circle with these params
    sf::CircleShape theCircle(radius, pointcount);
    // Create an offset of the radius to subtract from all points in the shape
    // so that the origin is in the centre of the shape
    CVector2f theOffset(radius, radius);
    
    // Now add all the points from this circle to our circle
    for (int i = 0; i < theCircle.getPointCount(); i++)
    {
        CVector2f thisPoint = theCircle.getPoint(i);
        thisPoint -= theOffset;
        this->setPoint(i, thisPoint);
    }
}

CCircleShape::~CCircleShape()
{
    
}
