//
//  SystemUtilities.mm
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SystemUtilities.hpp"

#if SG_MAC
#import <Foundation/Foundation.h>
#elif SG_WINDOWS
#include <windows.h>
#include <Shlwapi.h>
#endif

namespace SystemUtilities
{
    
// =============================================================================
// Namespace globals
// -----------------------------------------------------------------------------
std::list<CEvent>   theInputEvents;
CWindow             *theGameWindow;
    
// =============================================================================
// SystemUtilities::Init
// Initialise at program launch
// -----------------------------------------------------------------------------
void Init(CWindow *theWindow)
{
    theGameWindow = theWindow;
}

// =============================================================================
// SystemUtilities::GetResourcePath
// Return the platform specific path to the resource location
// -----------------------------------------------------------------------------
std::string GetResourcePath()
{
    std::string theReturnPath;

#if SG_MAC
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    NSBundle* bundle = [NSBundle mainBundle];

    if (bundle == nil)
    {
        DEBUG_LOG("Resource location can't be found: bundle is nil");
    }
    else
    {
        NSString* path = [bundle resourcePath];
        theReturnPath = [path UTF8String] + std::string("/");
    }

    [pool drain];
#elif SG_WINDOWS
	char buffer[MAX_PATH];
	DWORD result = GetModuleFileName(NULL, buffer, MAX_PATH);
	if (result == 0)
	{
		DEBUG_LOG("Failed to get module filename, error code %d", GetLastError());
	}
	else
	{
		PathRemoveFileSpec(buffer);
		theReturnPath = std::string(buffer) + std::string("\\");
	}
#endif

    return theReturnPath;
}

// =============================================================================
// SystemUtilities::AddInputEvent
// Add an input event to this of them recieved this cycle
// -----------------------------------------------------------------------------
void AddInputEvent(CEvent theEvent)
{
    theInputEvents.push_back(theEvent);
}

// =============================================================================
// SystemUtilities::ClearInputEvents
// Clear the list of input events
// -----------------------------------------------------------------------------
void ClearInputEvents()
{
    theInputEvents.clear();
}

// =============================================================================
// SystemUtilities::WasKeyPressedThisCycle
// Was a keypress event recieved for the given key this cycle
// -----------------------------------------------------------------------------
bool WasKeyPressedThisCycle(CKeyboard::Key theKey)
{
    bool theResult = false;
    
    FOR_EACH_IN_LIST(CEvent, theInputEvents)
    {
        if ((*it).type == CEvent::KeyPressed && (*it).key.code == theKey)
        {
            theResult = true;
        }
    }
    
    return theResult;
}

// =============================================================================
// SystemUtilities::GetMousePosition
// Get the mouse position relative to the window
// -----------------------------------------------------------------------------
CVector2i GetMousePosition()
{
    return CMouse::getPosition(*theGameWindow);
}
    
} // namespace SystemUtilities

