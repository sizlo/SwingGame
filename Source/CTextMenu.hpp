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
    CTextMenu(std::string theTitle, CFloatRect theShape);
    
    virtual void Enter();
    virtual void Exit();
    
    virtual void Update(CTime elapsedTime);
    virtual void Draw(CWindow *theWindow);
    
    virtual void ExecuteMenuItem(int choice) = 0;
    virtual void AddMenuItem(std::string theItem);

    int GetCurrentSelectionIndex();
    void SetCurrentSelectionIndex(int theIndex);

private:
    std::string mTitle;
    std::list<std::string> mMenuItems;
    int mCurrentSelection;
    CFloatRect mShape;
};

#endif /* defined(__SwingGame__CTextMenu__) */
