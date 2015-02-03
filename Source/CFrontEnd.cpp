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
                                GameOptions::viewWidth,
                                GameOptions::viewHeight);

// =============================================================================
// CFrontEnd constructor/destructor
// -----------------------------------------------------------------------------
CFrontEnd::CFrontEnd() : CTextMenu(smTitle, smShape)
{
    // Add all the menu items
#if SG_DEBUG
    AddMenuItem("Test level");
#endif
    AddMenuItem("Level 1");
    AddMenuItem("Level 2");
    AddMenuItem("Level 3");
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
#if SG_DEBUG
        case kFEItemTestLevel:
            CSwingGame::GoToLocation(kGameLocationTestLevel);
            break;
#endif
            
        case kFEItemLevel1:
            CSwingGame::GoToLocation(kGameLocationLevel1);
            break;
            
        case kFEItemLevel2:
            CSwingGame::GoToLocation(kGameLocationLevel2);
            break;
            
        case kFEItemLevel3:
            CSwingGame::GoToLocation(kGameLocationLevel3);
            break;
            
        case kFEItemExit: // Fall through
        default:
            CSwingGame::ExitGame();
    }
}
