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
    
    float           GetMass();
    CVector2f       GetVelocity();
    CVector2f       GetForce();
    CConvexShape *  GetShape();
    
    void        SetMass     (float          theMass);
    void        SetVelocity (CVector2f      theVelocity);
    void        AddVelocity (CVector2f      theVelocity);
    void        SetForce    (CVector2f      theForce);
    void        ApplyForce  (CVector2f      theForce);
    void        SetShape    (CConvexShape   theShape);

private:
    float           mMass;
    CVector2f       mVelocity;
    CVector2f       mForce;
    CConvexShape    mShape;
};

#endif /* defined(__SwingGame__CPhysicsBody__) */
