//
//  CSystemUtilities.mm
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSystemUtilities.hpp"

#if SG_MAC
#import <Foundation/Foundation.h>
#elif SG_WINDOWS
#include <windows.h>
#include <Shlwapi.h>
#endif

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
std::list<CEvent>   CSystemUtilities::smTheInputEvents;
CWindow             *CSystemUtilities::smGameWindow = NULL;

// =============================================================================
// CSystemUtilities::Init
// Initialise at program launch
// -----------------------------------------------------------------------------
void CSystemUtilities::Init(CWindow *theWindow)
{
    smGameWindow = theWindow;
}

// =============================================================================
// CSystemUtilities::GetResourcePath
// Return the platform specific path to the resource location
// -----------------------------------------------------------------------------
std::string CSystemUtilities::GetResourcePath()
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
// CSystemUtilities::AddInputEvent
// Add an input event to this of them recieved this cycle
// -----------------------------------------------------------------------------
void CSystemUtilities::AddInputEvent(CEvent theEvent)
{
    smTheInputEvents.push_back(theEvent);
}

// =============================================================================
// CSystemUtilities::ClearInputEvents
// Clear the list of input events
// -----------------------------------------------------------------------------
void CSystemUtilities::ClearInputEvents()
{
    smTheInputEvents.clear();
}

// =============================================================================
// CSystemUtilities::WasKeyPressedThisCycle
// Was a keypress event recieved for the given key this cycle
// -----------------------------------------------------------------------------
bool CSystemUtilities::WasKeyPressedThisCycle(CKeyboard::Key theKey)
{
    bool theResult = false;
    
    for (std::list<CEvent>::iterator it = smTheInputEvents.begin();
         it != smTheInputEvents.end();
         ++it)
    {
        if ((*it).type == CEvent::KeyPressed && (*it).key.code == theKey)
        {
            theResult = true;
        }
    }
    
    return theResult;
}

// =============================================================================
// CSystemUtilities::GetMousePosition
// Get the mouse position relative to the window
// -----------------------------------------------------------------------------
CVector2i CSystemUtilities::GetMousePosition()
{
    return CMouse::getPosition(*smGameWindow);
}

