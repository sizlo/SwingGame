//
//  CTextFrontEnd.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CTextFrontEnd__
#define __SwingGame__CTextFrontEnd__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CMenu.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CTextFrontEnd : public CMenu
{
public:
    CTextFrontEnd();
    ~CTextFrontEnd();
    
    // Enter the menu
    void Enter();
    // Draw the menu
    void Draw(CWindow *theWindow);
    // Update the menu
    void Update(CTime elapsedTime);

private:
    // Exit the menu
    void Exit();
};

#endif /* defined(__SwingGame__CTextFrontEnd__) */
