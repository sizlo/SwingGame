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
#include "SFMLIntegration/SFMLIntegration.hpp"
#include "CPlayer.hpp"
#include "SystemUtilities.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "CLine.hpp"
#include "CollisionHandler.hpp"

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
    HandleInput();
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
// CPlayer::HandleInput
// -----------------------------------------------------------------------------
void CPlayer::HandleInput()
{
    // Temporarily follow the mouse cursor
    CVector2f thePosition = SystemUtilities::GetMousePosition();
    
    // Constrain to window
    thePosition.x = std::min(1024.0f - 20.0f,   thePosition.x);
    thePosition.x = std::max(0.0f,              thePosition.x);
    thePosition.y = std::min(768.0f - 40.0f,    thePosition.y);
    thePosition.y = std::max(0.0f,              thePosition.y);
    
    mShape.setPosition(thePosition);
}

// =============================================================================
// CPlayer::HandleCollisions
// -----------------------------------------------------------------------------
void CPlayer::HandleCollisions()
{
    // Reset player colour
    mShape.setFillColor(CColour::Yellow);
    
    std::list<SLevelItem *> theObstacles = mParentLevel->GetObstacles();
    
    FOR_EACH_IN_LIST(SLevelItem *, theObstacles)
    {
        // Reset each obstacle colour
        (*it)->mShape.setFillColor(CColour::Black);
        
        if (CollisionHandler::AreColliding(mShape, (*it)->mShape))
        {
            // For now just highlight the colliding objects
            mShape.setFillColor(CColour::Red);
            (*it)->mShape.setFillColor(CColour::Red);
        }
    }
}