//
//  CRenderable.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CRenderable_hpp
#define SwingGame_CRenderable_hpp

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"

// =============================================================================
// Abstract class definition
// -----------------------------------------------------------------------------
class CRenderable
{
public:
    virtual void Draw(CWindow *theWindow) = 0;
};

#endif
