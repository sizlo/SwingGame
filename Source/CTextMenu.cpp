//
//  CTextMenu.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CTextMenu.hpp"
#include "CSwingGame.hpp"
#include "SystemUtilities.hpp"

// =============================================================================
// CTextMenu::Enter
// -----------------------------------------------------------------------------
void CTextMenu::Enter()
{
    // Register any updateables and renderables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterRenderable(this);
    
    mCurrentSelection = 0;
}

// =============================================================================
// CTextMenu::Exit
// -----------------------------------------------------------------------------
void CTextMenu::Exit()
{
    // Unregister all updateables and renderables
    CSwingGame::UnregisterUpdateable(this);
    CSwingGame::UnregisterRenderable(this);
}

// =============================================================================
// CTextMenu::Update
// -----------------------------------------------------------------------------
void CTextMenu::Update(CTime elapsedTime)
{
    // Move the cursor when up/down are pressed
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Up))
    {
        mCurrentSelection--;
    }
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Down))
    {
        mCurrentSelection++;
    }
    
    // Clamp the current selection
    mCurrentSelection = std::max(mCurrentSelection, 0);
    mCurrentSelection = std::min(mCurrentSelection, int(mMenuItems.size()) - 1);
    
    // Execute current selection on enter
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Return))
    {
        ExecuteMenuItem(mCurrentSelection);
    }
}

// =============================================================================
// CTextMenu::Draw
// -----------------------------------------------------------------------------
void CTextMenu::Draw(CWindow *theWindow)
{
    int xPosLeft    = 40;
    int xPosRight   = 50;
    int yPos        = 50;
    int yOffset     = 20;
    
    // Draw each menu item
    int i = 0;
    FOR_EACH_IN_LIST(std::string, mMenuItems)
    {
        std::string itemText = (*it);
        theWindow->DrawTextAt(itemText, xPosRight, yPos, CColour::White);
        
        // Draw the highlight if this is the current selection
        if (i == mCurrentSelection)
        {
            theWindow->DrawTextAt(">", xPosLeft, yPos, CColour::White);
        }
        
        i++;
        yPos += yOffset;
    }
}

// =============================================================================
// CTextMenu::AddMenuItem
// -----------------------------------------------------------------------------
void CTextMenu::AddMenuItem(std::string theItem)
{
    mMenuItems.push_back(theItem);
}