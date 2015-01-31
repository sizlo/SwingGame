//
//  CTextMenu.hpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __SwingGame__CTextMenu__
#define __SwingGame__CTextMenu__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CMenu.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CTextMenu : public CMenu
{
public:    
    virtual void Enter();
    virtual void Exit();
    
    virtual void Update(CTime elapsedTime);
    virtual void Draw(CWindow *theWindow);
    
    virtual void ExecuteMenuItem(int choice) = 0;
    virtual void AddMenuItem(std::string theItem);

private:
    std::list<std::string> mMenuItems;
    int mCurrentSelection;
};

#endif /* defined(__SwingGame__CTextMenu__) */
