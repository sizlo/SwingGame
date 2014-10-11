//
//  DebugOptions.cpp
//  SwingGame
//
//  Created by Tim Brier on 05/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "DebugOptions.hpp"
#include "SystemUtilities.hpp"

namespace DebugOptions
{

// =============================================================================
// Namespace globals
// -----------------------------------------------------------------------------
bool showFramerate      = true;
bool drawBounds         = false;
bool drawOrigins        = false;
bool drawShapePoints    = false;
bool drawShapeNormals   = false;

} // namespace DebugOptions

// =============================================================================
// CDebugHelper constructor/destructor
// -----------------------------------------------------------------------------
CDebugHelper::CDebugHelper()
{
    
}

CDebugHelper::~CDebugHelper()
{
    
}

// =============================================================================
// CDebugHelper::Update
// -----------------------------------------------------------------------------
void CDebugHelper::Update(CTime elapsedTime)
{
    // Toggle debug options on key presses, only when alt is held
    if (CKeyboard::isKeyPressed(CKeyboard::LAlt))
    {
        TOGGLE_DEBUG_OPTION(F, DebugOptions::showFramerate);
        TOGGLE_DEBUG_OPTION(B, DebugOptions::drawBounds);
        TOGGLE_DEBUG_OPTION(O, DebugOptions::drawOrigins);
        TOGGLE_DEBUG_OPTION(P, DebugOptions::drawShapePoints);
        TOGGLE_DEBUG_OPTION(N, DebugOptions::drawShapeNormals);
    }
}