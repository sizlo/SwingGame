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
#include <list>

// =============================================================================
// Data structures
// -----------------------------------------------------------------------------
struct SStartPosition
{
    float mX;
    float mY;
    float mSwingTargetX;
    float mSwingTargetY;
};

struct SLevelItem
{
    bool                mRigid;
    float               mY;
    float               mX;
    ELevelItemShapes    mShape;
    float               mSizeX;
    float               mSizeY;
    CSprite             mSprite;
};

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLevel : public CGameLocation
{
public:
    CLevel(std::string filename);
    ~CLevel();
    
    void Enter();
    void Exit();
    
    // Read a level from an xml file
    void InitFromFile(std::string filename);
    
private:
    int                     mID;
    std::string             mName;
    
    // Start and goal
    SStartPosition          mStartPosition;
    SLevelItem              mEndPosition;
    
    // Background sprite
    CSprite                 mBackground;
    
    // Obstacles
    std::list<SLevelItem>   mLevelItems;
};

#endif /* defined(__SwingGame__CLevel__) */
