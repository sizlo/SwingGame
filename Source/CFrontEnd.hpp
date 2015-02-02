//
//  CFrontEnd.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CFrontEnd__
#define __SwingGame__CFrontEnd__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CTextMenu.hpp"

// =============================================================================
// Enums
// -----------------------------------------------------------------------------
enum EFrontEndItems
{
#if SG_DEBUG
    kFEItemTestLevel,
#endif
    kFEItemLevel1,
    kFEItemExit
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CFrontEnd : public CTextMenu
{
public:
    CFrontEnd();
    ~CFrontEnd();
    
    // Enter the menu
    void Enter();
    // Exit the menu
    void Exit();
    
    void ExecuteMenuItem(int choice);
    
private:
    static std::string smTitle;
    static CFloatRect smShape;
};

#endif /* defined(__SwingGame__CFrontEnd__) */
