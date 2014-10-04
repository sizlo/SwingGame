//
//  CLevel.cpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CLevel.hpp"
#include "CSwingGame.hpp"
#include "Libraries/pugixml/pugixml.hpp"
#include "CSystemUtilities.hpp"

// =============================================================================
// CLevel constructor/destructor
// -----------------------------------------------------------------------------
CLevel::CLevel(std::string filename)
{
    InitFromFile(filename);
}

CLevel::~CLevel()
{
    
}

// =============================================================================
// CLevel::Enter
// -----------------------------------------------------------------------------
void CLevel::Enter()
{
    // Set the game state
    CSwingGame::SetGameState(kGameStateInGame);
}

// =============================================================================
// CLevel::Exit()
// -----------------------------------------------------------------------------
void CLevel::Exit()
{
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateInGame);
}

// =============================================================================
// CLevel::InitFromFile
// Read a level from an xml file
// -----------------------------------------------------------------------------
void CLevel::InitFromFile(std::string filename)
{
    // Read the file
    pugi::xml_document theDocument;
    std::string fullName = CSystemUtilities::GetResourcePath() + filename;
    pugi::xml_parse_result theResult = theDocument.load_file(fullName.c_str());
    
    if (theResult.status != pugi::status_ok)
    {
        DEBUG_LOG("Error parsisng level xml file: %s", filename.c_str());
        DEBUG_LOG("Status code: %d", theResult.status);
    }
    
    // TODO: Interpret the xml and populate the level
    DEBUG_LOG("InitFromFile - Not fully implemented");
}