//
//  SystemUtilities.hpp
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__SystemUtilities__
#define __SwingGame__SystemUtilities__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration/SFMLIntegration.hpp"
#include <string>
#include <list>

// =============================================================================
// Namespace definition
// -----------------------------------------------------------------------------
namespace SystemUtilities
{
    // Initialise at program launch
    void Init(CWindow *theWindow);
    // Return the platform specific path to the resource location
    std::string GetResourcePath();
    // Add an input event to the list
    void AddInputEvent(CEvent theEvent);
    // Clear the input event list
    void ClearInputEvents();
    // Was a given key pressed this cycle
    bool WasKeyPressedThisCycle(CKeyboard::Key theKey);
    // Was a given button pressed this cycle
    bool WasButtonPressedThisCycle(CMouse::Button theButton,
                                   CVector2f *thePosition);
    // Get the mouse position relative to the window
    CVector2f GetMousePosition();
};

#endif /* defined(__SwingGame__SystemUtilities__) */
