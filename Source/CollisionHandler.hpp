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
#include "CPhysicsBody.hpp"

// =============================================================================
// Enums
// -----------------------------------------------------------------------------
enum ECollisionResolveOptions
{
    // Which object(s) to move when seperating the colliding objects
    kCRMoveLeft         = 1 << 0,
    kCRMoveRight        = 1 << 1,
    kCRMoveBoth         = 1 << 2
};

// =============================================================================
// Namespace definition
// -----------------------------------------------------------------------------
namespace CollisionHandler
{
    // Check for collisions between 2 convex shapes
    bool AreColliding(CConvexShape &lhs,
                      CConvexShape &rhs,
                      CVector2f *correctionVector);
    // Check if 2 shapes overlap in an axis
    bool AreOverlapping(CConvexShape &lhs,
                        CConvexShape &rhs,
                        CVector2f axis,
                        CVector2f *correctionVector);
    // Project a point onto an axis
    float Project(CVector2f point, CVector2f axis);
    
    // Resolve a collision
    void Resolve(CPhysicsBody *lhs,
                 CPhysicsBody *rhs,
                 CVector2f correctionVector,
                 ECollisionResolveOptions = kCRMoveLeft);
}


#endif /* defined(__SwingGame__CollisionHandler__) */
