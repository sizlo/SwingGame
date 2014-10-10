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
#include "SystemUtilities.hpp"

// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
CVector2f GetVector2f(pugi::xml_node theNode)
{
    CHECK_CHILD(theNode, "x");
    CHECK_CHILD(theNode, "y");
    
    CVector2f theResult;
    theResult.x = theNode.child("x").text().as_float();
    theResult.y = theNode.child("y").text().as_float();
    
    return theResult;
}

SLevelItem GetLevelItem(pugi::xml_node theRoot)
{
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "texture");
    
    SLevelItem theResult;
    std::list<CVector2f> thePoints;
    
    // Process each child
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            theResult.mPosition = GetVector2f(theNode);
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
    
    // Set the position of the sprite
    theResult.mShape = CConvexShape(thePoints);
    theResult.mShape.setPosition(theResult.mPosition);
    
    return theResult;
}

// =============================================================================
// CLevel constructor/destructor
// -----------------------------------------------------------------------------
CLevel::CLevel(std::string filename)    :   mPlayer("player.png")
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
    
    // Register any renderables and updateables
    CSwingGame::RegisterRenderable(this);
    CSwingGame::RegisterUpdateable(this);
}

// =============================================================================
// CLevel::Exit()
// -----------------------------------------------------------------------------
void CLevel::Exit()
{
    // Unset the game state
    CSwingGame::UnsetGameState(kGameStateInGame);
    
    // Unregister all renderables and updateables
    CSwingGame::UnregisterRenderable(this);
    CSwingGame::UnregisterUpdateable(this);
}

// =============================================================================
// CLevel::InitFromFile
// Read a level from an xml file
// -----------------------------------------------------------------------------
void CLevel::InitFromFile(std::string filename)
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
    mName = theRoot.attribute("name").value();
    
    // Report missing required nodes
    CHECK_CHILD(theRoot, "start");
    CHECK_CHILD(theRoot, "goal");
    CHECK_CHILD(theRoot, "background");
    // Don't check for obstacles, stricly speaking they are not required
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "start") == 0)
        {
            ProcessStartXML(theNode);
        }
        else if (strcmp(theNode.name(), "goal") == 0)
        {
            ProcessGoalXML(theNode);
        }
        else if (strcmp(theNode.name(), "background") == 0)
        {
            DEBUG_LOG("Processing background node");
            mBackground = CSprite(theNode.text().as_string());
        }
        else if (strcmp(theNode.name(), "obstacle") == 0)
        {
            ProcessObstacleXML(theNode);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
}

// =============================================================================
// CLevel::ProcessStartXML
// Build the start position from the xml
// -----------------------------------------------------------------------------
void CLevel::ProcessStartXML(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing start node");
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "swingTarget");

    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            mStartPosition.mPosition = GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "swingTarget") == 0)
        {
            mStartPosition.mSwingTarget = GetVector2f(theNode);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
}

// =============================================================================
// CLevel::ProcessGoalXML
// Build the goal from the xml
// -----------------------------------------------------------------------------
void CLevel::ProcessGoalXML(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing goal node");

    mGoal = GetLevelItem(theRoot);
    
    // Default goal to green
    mGoal.mShape.setFillColor(CColour::Green);
}

// =============================================================================
// CLevel::ProcessObstacleXML
// Build an obstacle from the xml
// -----------------------------------------------------------------------------
void CLevel::ProcessObstacleXML(pugi::xml_node theRoot)
{
    DEBUG_LOG("Processing obstacle node");

    SLevelItem theObstacle = GetLevelItem(theRoot);
    
    // Default obstacles to black
    theObstacle.mShape.setFillColor(CColour::Black);
    
    mLevelItems.push_back(theObstacle);
}

// =============================================================================
// CLevel::Update
// Update the level
// -----------------------------------------------------------------------------
void CLevel::Update(CTime elapsedTime)
{
    // Temporary
    CVector2i playerPos = SystemUtilities::GetMousePosition();
    playerPos.x = std::max(0, playerPos.x);
    playerPos.x = std::min(1024-20, playerPos.x);
    playerPos.y = std::max(0, playerPos.y);
    playerPos.y = std::min(768-40, playerPos.y);
    mPlayer.setPosition(playerPos.x, playerPos.y);
    
    if (CKeyboard::isKeyPressed(CKeyboard::R))
    {
        mPlayer.rotate(360 * elapsedTime.asSeconds());
    }
}

// =============================================================================
// CLevel::Draw
// Draw the level
// -----------------------------------------------------------------------------
void CLevel::Draw(CWindow *theWindow)
{
    // Draw the background
    theWindow->draw(mBackground);
    
    // Draw the goal
    theWindow->DrawShape(mGoal.mShape);
    
    // Draw all level items
    for (std::list<SLevelItem>::iterator it = mLevelItems.begin();
         it != mLevelItems.end();
         ++it)
    {
        theWindow->DrawShape((*it).mShape);
    }
    
    // Temporary
    theWindow->DrawSprite(mPlayer);
}





