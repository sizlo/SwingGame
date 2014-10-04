//
//  CTextFrontEnd.cpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CTextFrontEnd.hpp"
#include "CSwingGame.hpp"

// =============================================================================
// CTextFrontEnd constructor/destructor
// -----------------------------------------------------------------------------
CTextFrontEnd::CTextFrontEnd()
{
    
}

CTextFrontEnd::~CTextFrontEnd()
{
    
}

// =============================================================================
// CTextFrontEnd::Enter
// Enter the menu
// -----------------------------------------------------------------------------
void CTextFrontEnd::Enter()
{
    // Register any updateables and drawables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterDrawable(this);
    
    // Set the game state
    CSwingGame::SetGameState(kGameStateFrontEnd);
}

// =============================================================================
// CTextFrontEnd::Draw
// Draw the menu
// -----------------------------------------------------------------------------
void CTextFrontEnd::Draw(CWindow *theWindow)
{
    int xPosLeft    = 50;
    int xPosRight   = 200;
    int yPos        = 50;
    int yOffset     = 20;
    
    theWindow->DrawTextAt("Level 1:", xPosLeft, yPos, CColour::White);
    theWindow->DrawTextAt("1", xPosRight, yPos, CColour::White);
    
    yPos += yOffset;
    
    theWindow->DrawTextAt("Exit Game:", xPosLeft, yPos, CColour::White);
    theWindow->DrawTextAt("Esc", xPosRight, yPos, CColour::White);
}

// =============================================================================
// CTextFrontEnd::Update
// Update the menu
// -----------------------------------------------------------------------------
void CTextFrontEnd::Update(CTime elapsedTime)
{
    if (CSwingGame::WasKeyPressedThisCycle(CKeyboard::Num1))
    {
        CSwingGame::GoToLocation(kGameLocationLevel1);
    }
    
    if (CSwingGame::WasKeyPressedThisCycle(CKeyboard::Escape))
    {
        CSwingGame::ExitGame();
    }
}

void CTextFrontEnd::Exit()
{
    // Unregister all updateables and drawables
    CSwingGame::UnregisterUpdateable(this);
    CSwingGame::UnregisterDrawable(this);
    
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateFrontEnd);
}

