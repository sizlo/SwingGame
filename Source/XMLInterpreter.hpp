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
    // Populate the given level using the given xml file
    void ProcessLevel(std::string filename, CLevel *theLevel);
    
    // Get a given data type from an xml node
    CVector2f       GetVector2f     (pugi::xml_node theRoot);
    SLevelItem      GetLevelItem    (pugi::xml_node theRoot);
    SStartPosition  GetStartPosition(pugi::xml_node theRoot);
    SLevelItem      GetGoal         (pugi::xml_node theRoot);
    SLevelItem      GetObstacle     (pugi::xml_node theRoot);
}

#endif /* defined(__SwingGame__XMLInterpreter__) */