//
//  CPhysicsBody.hpp
//  SwingGame
//
//  Created by Tim Brier on 30/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CPhysicsBody__
#define __SwingGame__CPhysicsBody__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPhysicsBody
{
public:
    CPhysicsBody();
    
    float           GetInverseMass();
    float           GetMass();
    CVector2f       GetVelocity();
    CConvexShape *  GetShape();
    CVector2f       GetPosition();
    
    void            SetInverseMass  (float          theInverseMass);
    void            SetVelocity     (CVector2f      theVelocity);
    void            AddVelocity     (CVector2f      theVelocity);
    void            SetShape        (CConvexShape   theShape);

private:
    float           mInverseMass;
    CVector2f       mVelocity;
    CConvexShape    mShape;
};

#endif /* defined(__SwingGame__CPhysicsBody__) */
