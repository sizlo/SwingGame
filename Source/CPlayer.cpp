//
//  CPlayer.cpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CPlayer.hpp"
#include "SystemUtilities.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "CLine.hpp"

// =============================================================================
// CPlayer constructor/destrctor
// -----------------------------------------------------------------------------
CPlayer::CPlayer(CLevel *theParentLevel) : mParentLevel(theParentLevel)
{
    // Create the shape
    std::list<CVector2f> thePoints;
    thePoints.push_back(CVector2f(0.0f,     0.0f));
    thePoints.push_back(CVector2f(20.0f,    0.0f));
    thePoints.push_back(CVector2f(20.0f,    40.0f));
    thePoints.push_back(CVector2f(0.0f,     40.0f));
    
    mShape = CConvexShape(thePoints);
    mShape.setFillColor(CColour::Yellow);
}

CPlayer::~CPlayer()
{
    
}

// =============================================================================
// CPlayer::Update
// -----------------------------------------------------------------------------
void CPlayer::Update(CTime elapsedTime)
{
    // Temporarily follow the mouse cursor
    CVector2f thePosition = (CVector2f) SystemUtilities::GetMousePosition();

    // Constrain to window
    thePosition.x = std::min(1024.0f - 20.0f,   thePosition.x);
    thePosition.x = std::max(0.0f,              thePosition.x);
    thePosition.y = std::min(768.0f - 40.0f,    thePosition.y);
    thePosition.y = std::max(0.0f,              thePosition.y);
    
    mShape.setPosition(thePosition);
    
    HandleCollisions();
}

// =============================================================================
// CPlayer::Draw
// -----------------------------------------------------------------------------
void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}

// =============================================================================
// CPlayer::Init
// -----------------------------------------------------------------------------
void CPlayer::Init()
{
    // Register any update/renderables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterRenderable(this);
}

// =============================================================================
// CPlayer::Cleanup
// -----------------------------------------------------------------------------
void CPlayer::Cleanup()
{
    // Unregister update/renderables
    CSwingGame::UnregisterUpdateable(this);
    CSwingGame::UnregisterRenderable(this);
}

// =============================================================================
// CPlayer::HandleCollisions
// -----------------------------------------------------------------------------
void CPlayer::HandleCollisions()
{
    // Reset player colour
    mShape.setFillColor(CColour::Yellow);
    
    std::list<SLevelItem *> theObstacles = mParentLevel->GetObstacles();
    
    for (std::list<SLevelItem *>::iterator it = theObstacles.begin();
         it != theObstacles.end();
         ++it)
    {
        // Reset each obstacle colour
        (*it)->mShape.setFillColor(CColour::Black);
        
        if (IsCollidingWith(*(*it)))
        {
            // For now just change highlight the colliding objects
            mShape.setFillColor(CColour::Red);
            (*it)->mShape.setFillColor(CColour::Red);
        }
    }
}

// =============================================================================
// CPlayer::IsCollidingWith
// -----------------------------------------------------------------------------
bool CPlayer::IsCollidingWith(SLevelItem theObstacle)
{
    bool theResult = false;
    
    // Check global bounding rects initially
    CFloatRect ourBounds = mShape.getGlobalBounds();
    CFloatRect theirBounds = theObstacle.mShape.getGlobalBounds();
    
    if (ourBounds.intersects(theirBounds))
    {
        // Now check each line of the player against each line of the obstacle
        // If there's an intersection we have a collision
        std::list<CLine> ourLines = mShape.GetGlobalLines();
        std::list<CLine> theirLines = theObstacle.mShape.GetGlobalLines();
        
        for (std::list<CLine>::iterator ourLine = ourLines.begin();
             ourLine != ourLines.end();
             ++ourLine)
        {
            for (std::list<CLine>::iterator theirLine = theirLines.begin();
                 theirLine != theirLines.end();
                 ++theirLine)
            {
                if ((*ourLine).Intersects((*theirLine)))
                {
                    // We have an intersection, therefore we are colliding
                    theResult = true;
                }
            }
        }
    }
    
    return theResult;
}