//
//  CPauseMenu.cpp
//  SwingGame
//
//  Created by Tim Brier on 19/02/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CPauseMenu.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "SystemUtilities.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
float CPauseMenu::smHalfWidth = 250;
float CPauseMenu::smHalfHeight = 125;
CVector2f CPauseMenu::smCenter = CVector2f(GameOptions::viewWidth / 2.0f,
                                           GameOptions::viewHeight / 2.0f);
CFloatRect CPauseMenu::smShape = CFloatRect(smCenter.y - smHalfHeight,
                                            smCenter.x - smHalfWidth,
                                            smHalfWidth * 2.0f,
                                            smHalfHeight * 2.0f);

// =============================================================================
// CPauseMenu constructor/destructor
// -----------------------------------------------------------------------------
CPauseMenu::CPauseMenu(CLevel *theParent)
:   CTextMenu("Paused", smShape),
mParentLevel(theParent)
{
    AddMenuItem("Resume game");
    AddMenuItem("Restart level");
    AddMenuItem("Exit to main menu");
    AddMenuItem("Exit game");
}

CPauseMenu::~CPauseMenu()
{
    
}

// =============================================================================
// CPauseMenu::Enter/Exit
// -----------------------------------------------------------------------------
void CPauseMenu::Enter()
{
    // Call parent
    CTextMenu::Enter();
    
    // Stop updating the parent level and pause the game
    CSwingGame::UnregisterUpdateable(mParentLevel);
    CSwingGame::SetGameState(kGameStatePaused);
}

void CPauseMenu::Exit()
{
    // Call parent
    CTextMenu::Exit();
    
    // Update the parent again and unpause the game
    CSwingGame::RegisterUpdateable(mParentLevel);
    CSwingGame::UnsetGameState(kGameStatePaused);
    mParentLevel->ResumeLevel();
}

// =============================================================================
// CPauseMenu::Update
// -----------------------------------------------------------------------------
void CPauseMenu::Update(CTime elapsedTime)
{
    // Execute the parent
    CTextMenu::Update(elapsedTime);
    
    // Unpause on esc
    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Escape))
    {
        ExecuteMenuItem(kPauseMenuResume);
    }
}

// =============================================================================
// CPauseMenu::ExecuteMenuChoice
// -----------------------------------------------------------------------------
void CPauseMenu::ExecuteMenuItem(int choice)
{
    switch (choice)
    {
        case kPauseMenuResume:
            Exit();
            break;
            
        case kPauseMenuRestart:
            Exit();
            mParentLevel->StartLevel();
            break;
            
        case kPauseMenuFrontEnd:
            Exit();
            CSwingGame::GoToLocation(kGameLocationFrontEnd);
            break;
            
        case kPauseMenuExitGame:
            Exit();
            CSwingGame::ExitGame();
            break;
    }
}
