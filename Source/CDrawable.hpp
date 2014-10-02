//
//  CDrawable.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CDrawable_hpp
#define SwingGame_CDrawable_hpp

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"

// =============================================================================
// Abstract class definition
// -----------------------------------------------------------------------------
class CDrawable
{
public:
    virtual void Draw(CWindow *theWindow) = 0;
};

#endif
