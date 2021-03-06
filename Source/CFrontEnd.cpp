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
#include "XMLInterpreter.hpp"
#if SG_WINDOWS
#include "Libraries/dirent.h"
#else
#include <dirent.h>
#endif

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
std::string CFrontEnd::smTitle = "SwingGame";
CFloatRect CFrontEnd::smShape = CFloatRect(0.0f, 0.0f,
                                GameOptions::viewWidth,
                                GameOptions::viewHeight);
int CFrontEnd::smStartingChoice = 0;

// =============================================================================
// CFrontEnd constructor/destructor
// -----------------------------------------------------------------------------
CFrontEnd::CFrontEnd() : CTextMenu(smTitle, smShape)
{
    // Build the list of level files
    std::string thePath = SystemUtilities::GetResourcePath() + "Levels/";
    std::string fileExtension = ".xml";
    DIR *simDir;
    struct dirent *currentEntry;
    
    simDir = opendir(thePath.c_str());
    if (simDir != NULL)
    {
        // Loop through all entries in this directory
        while ((currentEntry = readdir(simDir)) != NULL)
        {
            // If this entries name ends in .xml add it to the list
            std::string filename = currentEntry->d_name;
            if (filename.length() >= fileExtension.length()
                && filename.compare(filename.length() - fileExtension.length(),
                                   fileExtension.length(),
                                   fileExtension) == 0)
            {
                // Only include the test level in debug
                if (filename.compare("testLevel.xml") != 0 || SG_DEBUG)
                {
                    // Get the level name from the xml and add that to the menu list
                    filename = "Levels/" + filename;
                    std::string levelName = XMLInterpreter::GetLevelName(filename);
                    AddMenuItem(levelName);
                    // Add the filename to our list
                    mFilenames.push_back(filename);
                }
            }
        }
        closedir(simDir);
    }
    else
    {
        DEBUG_LOG("Problem opening directory %s", thePath.c_str());
    }
    
    // Add an exit option
    AddMenuItem("Exit Game");
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

    // Start the selection at where we last left it
    SetCurrentSelectionIndex(smStartingChoice);
    
    // Set the game state
    CSwingGame::SetGameState(kGameStateFrontEnd);
}

void CFrontEnd::Exit()
{
    // Call the parent
    CTextMenu::Exit();

    // Remember which choice index we're at
    smStartingChoice = GetCurrentSelectionIndex();
    
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateFrontEnd);
}

// =============================================================================
// CFrontEnd::Draw
// -----------------------------------------------------------------------------
void CFrontEnd::Draw(CWindow *theWindow)
{
    // Call the parent
    CTextMenu::Draw(theWindow);
    
    // Draw the best times for each level
    int xPos = 150;
    int yPos = 90;
    int yOffset = 20;
    
    std::map<std::string, CTime> bestTimes = XMLInterpreter::ReadBestTimes("times.xml");
    
    for (int i = 0; i < mFilenames.size(); i++)
    {
        std::string levelName = XMLInterpreter::GetLevelName(mFilenames.at(i));
        std::string key = levelName;
        std::replace(key.begin(), key.end(), ' ', '_');
        
        if (bestTimes.count(key) > 0)
        {
            CTime thisBestTime = bestTimes[key];
            theWindow->DrawTextAt(thisBestTime.AsString(), xPos, yPos, CColour::White);
        }
        
        yPos += yOffset;
    }
}

// =============================================================================
// CFrontEnd::ExecuteMenuItem
// -----------------------------------------------------------------------------
void CFrontEnd::ExecuteMenuItem(int choice)
{
    // Exit if we don't have a filename for that choice
    if (choice >= mFilenames.size())
    {
        CSwingGame::ExitGame();
    }
    // Otherwise get the filename for this choice and go to it
    else
    {
        CSwingGame::GoToLocation(kGameLocationLevel, mFilenames.at(choice));
    }
}
