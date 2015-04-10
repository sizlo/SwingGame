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
bool showFramerate          = true;
bool drawBounds             = false;
bool drawOrigins            = false;
bool drawShapePoints        = false;
bool drawShapeNormals       = false;
bool useSlowMotion          = false;
bool showMouseCoords        = false;
bool showPlayerAcceleration = false;
bool showPlayerVelocity     = false;
bool drawUnwrapTriangle     = false;
bool hidePauseMenu          = false;

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
        TOGGLE_DEBUG_OPTION(S, DebugOptions::useSlowMotion);
        TOGGLE_DEBUG_OPTION(M, DebugOptions::showMouseCoords);
        TOGGLE_DEBUG_OPTION(A, DebugOptions::showPlayerAcceleration);
        TOGGLE_DEBUG_OPTION(V, DebugOptions::showPlayerVelocity);
        TOGGLE_DEBUG_OPTION(U, DebugOptions::drawUnwrapTriangle);
        TOGGLE_DEBUG_OPTION(H, DebugOptions::hidePauseMenu);
    }
}

// =============================================================================
// CDebugHelper::Draw
// -----------------------------------------------------------------------------
void CDebugHelper::Draw(CWindow *theWindow)
{
    FOR_EACH_IN_LIST(CConvexShape*, mShapes)
    {
        theWindow->draw(*(*it));
    }
    
    FOR_EACH_IN_LIST(CLine, mLines)
    {
        theWindow->DrawLine((*it), CColour::Red);
    }
    
    if (DebugOptions::showMouseCoords)
    {
        CVector2f coords = SystemUtilities::GetMousePosition();
        char txt[32];
        sprintf(txt, "(%f, %f)", coords.x, coords.y);
        theWindow->DrawTextAt(txt, coords.x, coords.y - 15, CColour::Red);
    }
}

// =============================================================================
// CDebugHelper::AddShape
// -----------------------------------------------------------------------------
void CDebugHelper::AddShape(CConvexShape *theShape)
{
    mShapes.push_back(theShape);
}

// =============================================================================
// CDebugHelper::RemoveShape
// -----------------------------------------------------------------------------
void CDebugHelper::RemoveShape(CConvexShape *theShape)
{
    mShapes.remove(theShape);
}

// =============================================================================
// CDebugHelper::AddLine
// -----------------------------------------------------------------------------
void CDebugHelper::AddLine(CLine theLine)
{
    mLines.push_back(theLine);
}

// =============================================================================
// CDebugHelper::RemoveLine
// -----------------------------------------------------------------------------
void CDebugHelper::RemoveLine(CLine theLine)
{
    mLines.remove(theLine);
}