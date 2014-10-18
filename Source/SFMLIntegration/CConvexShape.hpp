//
//  CConvexShape.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CConvexShape__
#define __SwingGame__CConvexShape__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <list>
#include "CVector2.hpp"
#include "CLine.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CConvexShape : public sf::ConvexShape
{
public:
    CConvexShape(unsigned int pointCount = 0);
    CConvexShape(std::list<CVector2f> &thePoints);
    ~CConvexShape();
    // Build and return a list of lines within the shape
    std::list<CLine> GetGlobalLines();
};

#endif /* defined(__SwingGame__CConvexShape__) */
