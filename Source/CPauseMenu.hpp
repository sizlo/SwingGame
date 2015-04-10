//
//  CPauseMenu.h
//  SwingGame
//
//  Created by Tim Brier on 19/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CPauseMenu__
#define __SwingGame__CPauseMenu__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CTextMenu.hpp"

// =============================================================================
// Forward declarations
// -----------------------------------------------------------------------------
class CLevel;

// =============================================================================
// Enums
// -----------------------------------------------------------------------------
enum EPauseMenuItems
{
    kPauseMenuResume,
    kPauseMenuRestart,
    kPauseMenuFrontEnd,
    kPauseMenuExitGame
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPauseMenu : public CTextMenu
{
public:
    CPauseMenu(CLevel *theParent);
    ~CPauseMenu();
    
    void Enter();
    void Exit();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void ExecuteMenuItem(int choice);
    
private:
    CLevel *mParentLevel;
    
    static float smHalfWidth;
    static float smHalfHeight;
    static CVector2f smCenter;
    static CFloatRect smShape;
};

#endif /* defined(__SwingGame__CPauseMenu__) */
