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
    mSmallestRadius = 10.0f;
    
    std::list<CVector2f> thePoints;
    thePoints.push_back(CVector2f(0.0f,                 0.0f));
    thePoints.push_back(CVector2f(2 * mSmallestRadius,  0.0f));
    thePoints.push_back(CVector2f(2 * mSmallestRadius,  2 * mSmallestRadius));
    thePoints.push_back(CVector2f(0.0f,                 2 * mSmallestRadius));
    
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
    HandleInput(elapsedTime);
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
void CPlayer::Init(SStartPosition theStartPos)
{
    // Register any update/renderables
    CSwingGame::RegisterUpdateable(this);
    CSwingGame::RegisterRenderable(this);
    
    mShape.setPosition(theStartPos.mPosition);
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
// CPlayer::Move
// -----------------------------------------------------------------------------
void CPlayer::Move(float offsetX, float offsetY)
{
    Move(CVector2f(offsetX, offsetY));
}

void CPlayer::Move(CVector2f offset)
{
    // Find a smaller offset which is less than the shapes smallest "radius"
    CVector2f unitOffsetVector = offset;
    unitOffsetVector.Normalise();
    CVector2f smallOffset = unitOffsetVector * (mSmallestRadius - 1.0f);
    
    // Move by that offset until another move would go too far
    float totalDistanceToMove = offset.GetMagnitude();
    CVector2f movedSoFar(0.0f, 0.0f);
    
    do
    {
        mShape.move(smallOffset);
        movedSoFar += smallOffset;
        
        // After each move handle collisions
        HandleCollisions();
    } while (movedSoFar.GetMagnitude() < totalDistanceToMove);
    
    // Move by remaining offset
    mShape.move(offset - movedSoFar);
    HandleCollisions();
}

// =============================================================================
// CPlayer::HandleInput
// -----------------------------------------------------------------------------
void CPlayer::HandleInput(CTime elapsedTime)
{
    // Temporarily:
    // Move to the cursor if mouse is clicked
    // Move downwards if space is down
    if (CMouse::isButtonPressed(CMouse::Left))
    {
        CVector2f thePosition = SystemUtilities::GetMousePosition();
        
        // Constrain to window
        thePosition.x = std::min(1024.0f - 20.0f,   thePosition.x);
        thePosition.x = std::max(0.0f,              thePosition.x);
        thePosition.y = std::min(768.0f - 40.0f,    thePosition.y);
        thePosition.y = std::max(0.0f,              thePosition.y);
        
        mShape.setPosition(thePosition);
    }
    
    if (CKeyboard::isKeyPressed(CKeyboard::Space))
    {
        Move(0.0f, 1000.0f * elapsedTime.asSeconds());
    }
}

// =============================================================================
// CPlayer::HandleCollisions
// -----------------------------------------------------------------------------
void CPlayer::HandleCollisions()
{
    // Check for collisions against all level obstacles
    std::list<SLevelItem *> theObstacles = mParentLevel->GetObstacles();
    
    CVector2f correctionVector;
    FOR_EACH_IN_LIST(SLevelItem *, theObstacles)
    {
        if (CollisionHandler::AreColliding(mShape,
                                           (*it)->mShape,
                                           &correctionVector))
        {
            // If we're colliding move by the smallest correction vector
            // found during collision detection
            mShape.move(correctionVector);
        }
    }
}