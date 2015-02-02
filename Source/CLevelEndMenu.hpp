//
//  CLevelCompleteMenu.hpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CLevelCompleteMenu__
#define __SwingGame__CLevelCompleteMenu__

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
enum ELCMItems
{
    kLCMRestart = 0,
    kLCMFrontEnd = 1,
    kLCMExitGame = 2
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLevelCompleteMenu : public CTextMenu
{
public:
    CLevelCompleteMenu(CLevel *theParent);
    ~CLevelCompleteMenu();
    
    void Enter();
    void Exit();
    
    void ExecuteMenuItem(int choice);
    
private:
    CLevel *mParentLevel;
    
    static std::string smTitle;
    static float smHalfWidth;
    static float smHalfHeight;
    static CVector2f smCenter;
    static CFloatRect smShape;
};

#endif /* defined(__SwingGame__CLevelCompleteMenu__) */
