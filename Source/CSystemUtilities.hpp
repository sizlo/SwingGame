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
#include "SFMLIntegration.hpp"
#include <string>
#include <list>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CSystemUtilities
{
public:
    // Initialise at program launch
    static void Init(CWindow *theWindow);
    // Return the platform specific path to the resource location
    static std::string GetResourcePath();
    // Add an input event to the list
    static void AddInputEvent(CEvent theEvent);
    // Clear the input event list
    static void ClearInputEvents();
    // Was a given key pressed this cycle
    static bool WasKeyPressedThisCycle(CKeyboard::Key theKey);
    // Get the mouse position relative to the window
    static CVector2i GetMousePosition();
    
private:
    static std::list<CEvent> smTheInputEvents;
    static CWindow *smGameWindow;
};

#endif /* defined(__SwingGame__CSystemUtilities__) */
