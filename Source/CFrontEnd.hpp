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
    
    void Draw(CWindow *theWindow);
    
    void ExecuteMenuItem(int choice);
    
private:
    static std::string smTitle;
    static CFloatRect smShape;
    static int smStartingChoice;
    
    std::vector<std::string>    mFilenames;
};

#endif /* defined(__SwingGame__CFrontEnd__) */
