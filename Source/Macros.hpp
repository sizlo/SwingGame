//
//  Macros.hpp
//  SwingGame
//
//  Created by Tim Brier on 25/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_Macros_hpp
#define SwingGame_Macros_hpp

// =============================================================================
// Allocation
// -----------------------------------------------------------------------------
#define SAFE_DELETE(ptr)    \
    if (ptr != NULL)        \
    {                       \
        delete ptr;         \
        ptr = NULL;         \
    }

// =============================================================================
// Logging
// -----------------------------------------------------------------------------
#if SG_DEBUG
#define DEBUG_LOG(fmt, ...)         \
    printf("%s:%d " fmt, __FILE__, __LINE__, __VA_ARGS__);
#else
#define DEBUG_LOG(fmt, ...)
#endif

#endif
