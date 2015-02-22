//
//  XMLInterpreter.hpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__XMLInterpreter__
#define __SwingGame__XMLInterpreter__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "Libraries/pugixml/pugixml.hpp"
#include "CLevel.hpp"

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
#define CHECK_ATTRIBUTE(node, attr)                 \
    if (node.attribute(attr) == NULL)               \
    {                                               \
        DEBUG_LOG("Missing attribute: %s", attr);   \
    }

#define CHECK_CHILD(root, childName)                \
    if (root.child(childName) == NULL)              \
    {                                               \
        DEBUG_LOG("Missing child: %s", childName);  \
    }

// =============================================================================
// namespace definition
// -----------------------------------------------------------------------------
namespace XMLInterpreter
{
    // Set the game options from a config file
    void ReadConfig(std::string filename);
    
    // Read/write the players best times
    std::map<std::string, CTime> ReadBestTimes(std::string filename);
    void WriteBestTimes(std::string filename,
                        std::map<std::string, CTime> theTimes);

    // Populate the given level using the given xml file
    void ProcessLevel(std::string filename, CLevel *theLevel);
    
    // Get just a level name from a given xml file
    std::string GetLevelName(std::string filename);
    
    // Get a given data type from an xml node
    int             GetInt          (pugi::xml_node theRoot);
    bool            GetBool         (pugi::xml_node theRoot);
    CVector2f       GetVector2f     (pugi::xml_node theRoot);
    CTime           GetTime         (pugi::xml_node theRoot);
    CPhysicsBody    GetLevelItem    (pugi::xml_node theRoot);
    SStartPosition  GetStartPosition(pugi::xml_node theRoot);
    CPhysicsBody    GetGoal         (pugi::xml_node theRoot);
    CPhysicsBody    GetObstacle     (pugi::xml_node theRoot);
    ESwingTypes     GetSwingType    (pugi::xml_node theRoot);
    CText           GetLevelText    (pugi::xml_node theRoot);
}

#endif /* defined(__SwingGame__XMLInterpreter__) */
