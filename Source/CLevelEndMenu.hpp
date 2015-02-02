//
//  CLevelEndMenu.hpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CLevelEndMenu__
#define __SwingGame__CLevelEndMenu__

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
enum ELEMItems
{
    kLEMRestart = 0,
    kLEMFrontEnd = 1,
    kLEMExitGame = 2
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLevelEndMenu : public CTextMenu
{
public:
    CLevelEndMenu(CLevel *theParent);
    ~CLevelEndMenu();
    
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

#endif /* defined(__SwingGame__CLevelEndMenu__) */
