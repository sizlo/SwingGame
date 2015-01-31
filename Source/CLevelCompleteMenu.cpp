//
//  CLevelCompleteMenu.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/01/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CLevelCompleteMenu.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
std::string CLevelCompleteMenu::smTitle = "Level completed";
float CLevelCompleteMenu::smHalfWidth = 250;
float CLevelCompleteMenu::smHalfHeight = 125;
CVector2f CLevelCompleteMenu::smCenter = CVector2f(
                                            GameOptions::windowWidth / 2.0f,
                                            GameOptions::windowHeight / 2.0f
                                         );
CFloatRect CLevelCompleteMenu::smShape = CFloatRect(smCenter.y - smHalfHeight,
                                                    smCenter.x - smHalfWidth,
                                                    smHalfWidth * 2.0f,
                                                    smHalfHeight * 2.0f);

// =============================================================================
// CLevelCompleteMenu constructor/destructor
// -----------------------------------------------------------------------------
CLevelCompleteMenu::CLevelCompleteMenu(CLevel *theParent)
:   CTextMenu(smTitle, smShape),
    mParentLevel(theParent)
{
    AddMenuItem("Restart level");
    AddMenuItem("Exit to main menu");
    AddMenuItem("Exit game");
}

CLevelCompleteMenu::~CLevelCompleteMenu()
{
    
}

// =============================================================================
// CLevelCompleteMenu::Enter/Exit
// -----------------------------------------------------------------------------
void CLevelCompleteMenu::Enter()
{
    // Call parent
    CTextMenu::Enter();
    
    // Stop updating the parent level
    CSwingGame::UnregisterUpdateable(mParentLevel);
}

void CLevelCompleteMenu::Exit()
{
    // Call parent
    CTextMenu::Exit();
    
    // Update the parent again
    CSwingGame::RegisterUpdateable(mParentLevel);
}

// =============================================================================
// CLevelCompleteMenu::ExecuteMenuChoice
// -----------------------------------------------------------------------------
void CLevelCompleteMenu::ExecuteMenuItem(int choice)
{
    switch (choice)
    {
        case kLCMRestart:
            Exit();
            mParentLevel->StartLevel();
            break;
            
        case kLCMFrontEnd:
            Exit();
            CSwingGame::GoToLocation(kGameLocationFrontEnd);
            break;
            
        case kLCMExitGame:
            Exit();
            CSwingGame::ExitGame();
            break;
    }
}