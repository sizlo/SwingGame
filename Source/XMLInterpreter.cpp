//
//  XMLInterpreter.cpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "XMLInterpreter.hpp"
#include "SystemUtilities.hpp"
#include "GameOptions.hpp"

namespace XMLInterpreter
{

// =============================================================================
// XMLInterpreter::ReadConfig
// Set the game options from a config file
// -----------------------------------------------------------------------------
void ReadConfig(std::string filename)
{
    // Read the file
    pugi::xml_document theDocument;
    std::string fullName = SystemUtilities::GetResourcePath() + filename;
    pugi::xml_parse_result theResult = theDocument.load_file(fullName.c_str());

    if (theResult.status != pugi::status_ok)
    {
        DEBUG_LOG("Error parsisng config xml file: %s", filename.c_str());
        DEBUG_LOG("Status code: %d", theResult.status);
        
        // Bail out
        return;
    }

    // Begin processing
    pugi::xml_node theRoot = theDocument.document_element();

    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "windowHeight") == 0)
        {
            GameOptions::windowHeight = GetInt(theNode);
        }
        else if (strcmp(theNode.name(), "windowWidth") == 0)
        {
            GameOptions::windowWidth = GetInt(theNode);
        }
        else if (strcmp(theNode.name(), "useVsync") == 0)
        {
            GameOptions::doVsync = GetBool(theNode);
        }
        else if (strcmp(theNode.name(), "fullscreen") == 0)
        {
            GameOptions::fullscreen = GetBool(theNode);
        }
        else if (strcmp(theNode.name(), "preserveAspect") == 0)
        {
            GameOptions::preserveAspect = GetBool(theNode);
        }
        else
        {
             DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
}
    
// =============================================================================
// XMLInterpreter::ReadBestTimes
// -----------------------------------------------------------------------------
std::map<std::string, CTime> ReadBestTimes(std::string filename)
{
    std::map<std::string, CTime> theTimes;
    
    // Read the file
    pugi::xml_document theDocument;
    std::string fullName = SystemUtilities::GetResourcePath() + filename;
    pugi::xml_parse_result theResult = theDocument.load_file(fullName.c_str());
    
    if (theResult.status != pugi::status_ok)
    {
        DEBUG_LOG("Error parsisng times xml file: %s", filename.c_str());
        DEBUG_LOG("Status code: %d", theResult.status);
    }
    
    // Begin processing
    pugi::xml_node theRoot = theDocument.document_element();
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        theTimes[theNode.name()] = GetTime(theNode);
    }
    
    return theTimes;
}
    
// =============================================================================
// XMLInterpreter::WriteBestTimes
// -----------------------------------------------------------------------------
void WriteBestTimes(std::string filename,
                    std::map<std::string, CTime> theTimes)
{
    pugi::xml_document doc;
    doc.load("<times></times>");
    
    pugi::xml_node theRoot = doc.document_element();

    for (std::map<std::string, CTime>::iterator it = theTimes.begin();
         it != theTimes.end();
         ++it)
    {
        std::string key = it->first;
        CTime value = it->second;
        
        pugi::xml_node theChild = theRoot.append_child(key.c_str());
        char valueString[32];
        sprintf(valueString, "%f", value.asSeconds());
        theChild.text().set(valueString);
    }
    
    std::string fullName = SystemUtilities::GetResourcePath() + filename;
    doc.save_file(fullName.c_str());
}
    
// =============================================================================
// XMLInterpreter::ProcessLevel
// Populate the given level using the given xml file
// -----------------------------------------------------------------------------
void ProcessLevel(std::string filename, CLevel *theLevel)
{
    DEBUG_LOG("Loading level from %s", filename.c_str());
    
    // Read the file
    pugi::xml_document theDocument;
    std::string fullName = SystemUtilities::GetResourcePath() + filename;
    pugi::xml_parse_result theResult = theDocument.load_file(fullName.c_str());
    
    if (theResult.status != pugi::status_ok)
    {
        DEBUG_LOG("Error parsisng level xml file: %s", filename.c_str());
        DEBUG_LOG("Status code: %d", theResult.status);
    }
    
    // Begin processing the level(root) node
    DEBUG_LOG("Processing level node");
    
    // Get the name and ID from the root element
    pugi::xml_node theRoot = theDocument.document_element();
    CHECK_ATTRIBUTE(theRoot, "name");
    theLevel->SetName(theRoot.attribute("name").value());
    
    // Report missing required nodes
    CHECK_CHILD(theRoot, "start");
    CHECK_CHILD(theRoot, "goal");
    CHECK_CHILD(theRoot, "background");
    // Don't check for obstacles, strictly speaking they are not required
    // Don't check tutorial text, it's not needed
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "start") == 0)
        {
            theLevel->SetStartPosition(GetStartPosition(theNode));
        }
        else if (strcmp(theNode.name(), "goal") == 0)
        {
            theLevel->SetGoal(GetGoal(theNode));
        }
        else if (strcmp(theNode.name(), "background") == 0)
        {
            DEBUG_LOG("Processing background node");
            theLevel->SetBackground(CSprite(theNode.text().as_string()));
        }
        else if (strcmp(theNode.name(), "obstacle") == 0)
        {
            theLevel->AddObstacle(GetObstacle(theNode));
        }
        else if (strcmp(theNode.name(), "tutorialText") == 0)
        {
            theLevel->SetTutorialText(GetLevelText(theNode));
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
}
    
// =============================================================================
// XMLInterpreter::GetLevelName
// -----------------------------------------------------------------------------
std::string GetLevelName(std::string filename)
{
    // Read the file
    pugi::xml_document theDocument;
    std::string fullName = SystemUtilities::GetResourcePath() + filename;
    pugi::xml_parse_result theResult = theDocument.load_file(fullName.c_str());
    
    if (theResult.status != pugi::status_ok)
    {
        DEBUG_LOG("Error parsisng level xml file: %s", filename.c_str());
        DEBUG_LOG("Status code: %d", theResult.status);
    }
    
    // Get the name and ID from the root element
    pugi::xml_node theRoot = theDocument.document_element();
    CHECK_ATTRIBUTE(theRoot, "name");
    std::string theName = theRoot.attribute("name").as_string();
    
    return theName;
}

// =============================================================================
// XMLInterpreter::GetInt
// -----------------------------------------------------------------------------
int GetInt(pugi::xml_node theRoot)
{
    int theResult = 0;
    theResult = theRoot.text().as_int();
    return theResult;
}

// =============================================================================
// XMLInterpreter::GetBool
// -----------------------------------------------------------------------------
bool GetBool(pugi::xml_node theRoot)
{
    int theResult = 0;
    theResult = theRoot.text().as_bool();
    return theResult;
}

// =============================================================================
// XMLInterpreter::GetVector2f
// -----------------------------------------------------------------------------
CVector2f GetVector2f(pugi::xml_node theRoot)
{
    CHECK_CHILD(theRoot, "x");
    CHECK_CHILD(theRoot, "y");
    
    CVector2f theResult;
    theResult.x = theRoot.child("x").text().as_float();
    theResult.y = theRoot.child("y").text().as_float();
    
    return theResult;
}
    
// =============================================================================
// XMLInterpreter::GetTime
// -----------------------------------------------------------------------------
CTime GetTime(pugi::xml_node theRoot)
{
    float seconds = theRoot.text().as_float();
    CTime theResult = CTime::Seconds(seconds);
    
    return theResult;
}

// =============================================================================
// XMLInterpreter::GetLevelItem
// -----------------------------------------------------------------------------
CPhysicsBody GetLevelItem(pugi::xml_node theRoot)
{
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "texture");
    
    CPhysicsBody theResult;
    std::list<CVector2f> thePoints;
    CVector2f thePosition = CVector2f(0.0f, 0.0f);
    
    // Process each child
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            thePosition = GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "texture") == 0)
        {
            bool flipX = false;
            bool flipY = false;
            
            if (theNode.attribute("flipX") != NULL)
            {
                flipX = theNode.attribute("flipX").as_bool();
            }
            if (theNode.attribute("flipY") != NULL)
            {
                flipY = theNode.attribute("flipY").as_bool();
            }
            
            std::string filename = theNode.text().as_string();
            // TODO: Texture item shapes
            DEBUG_LOG("Texturing level items not implemented");
        }
        else if (strcmp(theNode.name(), "point") == 0)
        {
            CVector2f thePoint = GetVector2f(theNode);
            thePoints.push_back(thePoint);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
    
    // Create and initialise the shape
    theResult.SetShape(CConvexShape(thePoints));
    theResult.GetShape()->setPosition(thePosition);
    
    return theResult;
}
    
// =============================================================================
// XMLInterpreter::GetStartPosition
// -----------------------------------------------------------------------------
SStartPosition GetStartPosition(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing start node");
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "swingTarget");
    CHECK_CHILD(theRoot, "velocity")
    CHECK_CHILD(theRoot, "swingType")
    
    SStartPosition theResult;
    
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            theResult.mPosition = XMLInterpreter::GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "swingTarget") == 0)
        {
            theResult.mSwingTarget = XMLInterpreter::GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "velocity") == 0)
        {
            theResult.mVelocity = XMLInterpreter::GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "swingType") == 0)
        {
            theResult.mSwingType = XMLInterpreter::GetSwingType(theNode);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
    
    return theResult;
}
    
// =============================================================================
// XMLInterpreter::GetGoal
// -----------------------------------------------------------------------------
CPhysicsBody GetGoal(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing goal node");
    
    CPhysicsBody theResult = XMLInterpreter::GetLevelItem(theRoot);
    
    // Default goal to green
    theResult.GetShape()->setFillColor(CColour::Green);
    
    return theResult;
}

// =============================================================================
// XMLInterpreter::GetObstacle
// -----------------------------------------------------------------------------
CPhysicsBody GetObstacle(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing goal node");
    
    CPhysicsBody theResult = XMLInterpreter::GetLevelItem(theRoot);
    
    // Default obstacle to black
    theResult.GetShape()->setFillColor(CColour::Black);
    
    return theResult;
}
    
// =============================================================================
// XMLInterpreter::GetSwingType
// -----------------------------------------------------------------------------
ESwingTypes GetSwingType(pugi::xml_node theRoot)
{
    ESwingTypes theResult = kSwingTypeRigid;
    
    if (strcmp(theRoot.text().as_string(), "rigid") == 0)
    {
        theResult = kSwingTypeRigid;
    }
    else if (strcmp(theRoot.text().as_string(), "flexible") == 0)
    {
        theResult = kSwingTypeFlexible;
    }
    else if (strcmp(theRoot.text().as_string(), "pulling") == 0)
    {
        theResult = kSwingTypePulling;
    }
    else if (strcmp(theRoot.text().as_string(), "spring") == 0)
    {
        theResult = kSwingTypeSpring;
    }
    
    return theResult;
}
    
// =============================================================================
// XMLInterpreter::GetLevelText
// -----------------------------------------------------------------------------
CText GetLevelText(pugi::xml_node theRoot)
{
    CHECK_CHILD(theRoot, "text");
    
    std::string theString = theRoot.child("text").text().as_string();
    CVector2f thePos = GetVector2f(theRoot);
    
    CText theResult = CText(theString, thePos);
    return theResult;
}
    
} // namespace XMLInterpreter