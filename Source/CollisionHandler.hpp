//
//  CollisionHandler.hpp
//  SwingGame
//
//  Created by Tim Brier on 28/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CollisionHandler__
#define __SwingGame__CollisionHandler__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"

// =============================================================================
// Namespace definition
// -----------------------------------------------------------------------------
namespace CollisionHandler
{
    // Check for collisions between 2 convex shapes
    bool AreColliding(CConvexShape &lhs, CConvexShape &rhs);
    // Check if 2 shapes overlap in an axis
    bool AreOverlapping(CConvexShape &lhs, CConvexShape &rhs, CVector2f axis);
    // Project a point onto an axis
    float Project(CVector2f point, CVector2f axis);
}


#endif /* defined(__SwingGame__CollisionHandler__) */
