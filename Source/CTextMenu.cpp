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
// CTextMenu constructor
// -----------------------------------------------------------------------------
CTextMenu::CTextMenu(std::string theTitle, CFloatRect theShape)
:   mTitle(theTitle),
    mShape(theShape)
{
    
}

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
    int xPosLeft    = mShape.left +  40;
    int xPosRight   = mShape.left + 50;
    int yPos        = mShape.top + 50;
    int yOffset     = 20;
    
    // Draw the background
    CVector2f heightOffset = CVector2f(0.0f, mShape.height);
    CVector2f widthOffset = CVector2f(mShape.width, 0.0f);
    CVector2f topLeft = CVector2f(mShape.left, mShape.top);
    CVector2f topRight = topLeft + widthOffset;
    CVector2f bottomLeft = topLeft + heightOffset;
    CVector2f bottomRight = bottomLeft + widthOffset;
    std::list<CVector2f> points;
    points.push_back(topLeft);
    points.push_back(topRight);
    points.push_back(bottomRight);
    points.push_back(bottomLeft);
    CConvexShape background = CConvexShape(points);
    background.setFillColor(CColour::Black);
    theWindow->DrawShape(background);
    
    // Draw the title
    theWindow->DrawTextAt(mTitle, xPosLeft, yPos, CColour::White);
    yPos += yOffset + yOffset;
    
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