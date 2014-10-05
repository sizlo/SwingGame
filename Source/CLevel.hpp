//
//  CLevel.hpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CLevel__
#define __SwingGame__CLevel__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CGameLocation.hpp"
#include "SFMLIntegration.hpp"
#include "Libraries/pugixml/pugixml.hpp"
#include "CDrawable.hpp"
#include "CUpdateable.hpp"
#include <list>

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
// Data structures
// -----------------------------------------------------------------------------
struct SStartPosition
{
    CVector2f mPosition;
    CVector2f mSwingTarget;
};

struct SLevelItem
{
    CVector2f           mPosition;
    ELevelItemShapes    mShape;
    CVector2f           mSize;
    CSprite             mSprite;
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLevel : public CGameLocation, public CDrawable, public CUpdateable
{
public:
    CLevel(std::string filename);
    ~CLevel();
    
    void Enter();
    void Exit();
    
    // Read a level from an xml file
    void InitFromFile       (std::string filename);
    void ProcessStartXML    (pugi::xml_node theRoot);
    void ProcessGoalXML     (pugi::xml_node theRoot);
    void ProcessObstacleXML (pugi::xml_node theRoot);
    
    // Update the level
    void Update(CTime elapsedTime);
    // Draw the level
    void Draw(CWindow *theWindow);
    
private:
    std::string             mName;
    
    // Start and goal
    SStartPosition          mStartPosition;
    SLevelItem              mGoal;
    
    // Background sprite
    CSprite                 mBackground;
    
    // Obstacles
    std::list<SLevelItem>   mLevelItems;
};

#endif /* defined(__SwingGame__CLevel__) */
