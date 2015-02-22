//
//  CLevelEndMenu.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CLevelEndMenu.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "SystemUtilities.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
float CLevelEndMenu::smHalfWidth = 250;
float CLevelEndMenu::smHalfHeight = 125;
CVector2f CLevelEndMenu::smCenter = CVector2f(GameOptions::viewWidth / 2.0f,
                                              GameOptions::viewHeight / 2.0f);
CFloatRect CLevelEndMenu::smShape = CFloatRect(smCenter.y - smHalfHeight,
                                               smCenter.x - smHalfWidth,
                                               smHalfWidth * 2.0f,
                                               smHalfHeight * 2.0f);

// =============================================================================
// CLevelEndMenu constructor/destructor
// -----------------------------------------------------------------------------
CLevelEndMenu::CLevelEndMenu(std::string theTitle, CLevel *theParent)
:   CTextMenu(theTitle, smShape),
    mParentLevel(theParent)
{
    AddMenuItem("Restart level");
    AddMenuItem("Exit to main menu");
    AddMenuItem("Exit game");
}

CLevelEndMenu::~CLevelEndMenu()
{
    
}

// =============================================================================
// CLevelEndMenu::Enter/Exit
// -----------------------------------------------------------------------------
void CLevelEndMenu::Enter()
{
    // Call parent
    CTextMenu::Enter();
    
    // Stop updating the parent level
    CSwingGame::UnregisterUpdateable(mParentLevel);
}

void CLevelEndMenu::Exit()
{
    // Call parent
    CTextMenu::Exit();
    
    // Update the parent again
    CSwingGame::RegisterUpdateable(mParentLevel);
}

// =============================================================================
// CLevelEndMenu::Update
// -----------------------------------------------------------------------------
void CLevelEndMenu::Update(CTime elapsedTime)
{
    // Execute the parent
    CTextMenu::Update(elapsedTime);
    
    // Restart on R
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::R))
    {
        ExecuteMenuItem(kLEMRestart);
    }
}

// =============================================================================
// CLevelEndMenu::Draw
// -----------------------------------------------------------------------------
void CLevelEndMenu::Draw(CWindow *theWindow)
{
    // Call the parent method
    CTextMenu::Draw(theWindow);
    
    // Draw the extra text
    theWindow->DrawTextAt(mExtraText, 500, 360, CColour::White);
}

// =============================================================================
// CLevelEndMenu::ExecuteMenuChoice
// -----------------------------------------------------------------------------
void CLevelEndMenu::ExecuteMenuItem(int choice)
{
    switch (choice)
    {
        case kLEMRestart:
            Exit();
            mParentLevel->StartLevel();
            break;
            
        case kLEMFrontEnd:
            Exit();
            CSwingGame::GoToLocation(kGameLocationFrontEnd);
            break;
            
        case kLEMExitGame:
            Exit();
            CSwingGame::ExitGame();
            break;
    }
}

// =============================================================================
// CLevelEndMenu::SetExtraText
// -----------------------------------------------------------------------------
void CLevelEndMenu::SetExtraText(std::string theText)
{
    mExtraText = theText;
}