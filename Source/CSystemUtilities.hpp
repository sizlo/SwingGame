//
//  CSystemUtilities.hpp
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CSystemUtilities__
#define __SwingGame__CSystemUtilities__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include <string>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSystemUtilities
{
public:
    // Return the platform specific path to the resource location
    static std::string GetResourcePath();
};

#endif /* defined(__SwingGame__CSystemUtilities__) */
