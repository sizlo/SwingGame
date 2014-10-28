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
#define DEBUG_LOG(...)                      \
    printf("%s:%d ", __FILE__, __LINE__);   \
    printf(__VA_ARGS__);                    \
    printf("\n");
#else
#define DEBUG_LOG(fmt, ...)
#endif

// =============================================================================
// Iterate over lists
// -----------------------------------------------------------------------------
#define FOR_EACH_IN_LIST(type, listName)                            \
    for (std::list<type>::iterator it = listName.begin();           \
         it != listName.end();                                      \
         ++it)

#endif
