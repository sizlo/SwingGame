//
//  CUpdateable.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CUpdateable_hpp
#define SwingGame_CUpdateable_hpp

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"
#include "Enums.hpp"

// =============================================================================
// Abstract class definition
// -----------------------------------------------------------------------------
class CUpdateable
{
public:
    virtual void Update(CTime elapsedTime) = 0;
    virtual bool ShouldUpdateForState(EGameState theState){return true;};
};

#endif
