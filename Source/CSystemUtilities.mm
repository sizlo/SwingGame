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
#endif

    return theReturnPath;
}
