//
//  CFrontEnd.cpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CFrontEnd.hpp"
#include "CSwingGame.hpp"
#include "SystemUtilities.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
std::string CFrontEnd::smTitle = "SwingGame";
CFloatRect CFrontEnd::smShape = CFloatRect(0.0f, 0.0f,
                                GameOptions::windowWidth,
                                GameOptions::windowHeight);

// =============================================================================
// CFrontEnd constructor/destructor
// -----------------------------------------------------------------------------
CFrontEnd::CFrontEnd() : CTextMenu(smTitle, smShape)
{
    // Add all the menu items
    AddMenuItem("Level 1");
    AddMenuItem("Exit");
}

CFrontEnd::~CFrontEnd()
{
    
}

// =============================================================================
// CFrontEnd::Enter
// Enter the menu
// -----------------------------------------------------------------------------
void CFrontEnd::Enter()
{
    // Call the parent
    CTextMenu::Enter();
    
    // Set the game state
    CSwingGame::SetGameState(kGameStateFrontEnd);
}

void CFrontEnd::Exit()
{
    // Call the parent
    CTextMenu::Exit();
    
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateFrontEnd);
}

// =============================================================================
// CFrontEnd::ExecuteMenuItem
// -----------------------------------------------------------------------------
void CFrontEnd::ExecuteMenuItem(int choice)
{
    switch (choice)
    {
        case kFEItemLevel1:
            CSwingGame::GoToLocation(kGameLocationLevel1);
            break;
        case kFEItemExit: // Fall through
        default:
            CSwingGame::ExitGame();
    }
}
