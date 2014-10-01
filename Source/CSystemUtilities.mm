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
