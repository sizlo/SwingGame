//
//  CFlexibleSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 30/11/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include "CFlexibleSwing.hpp"
#include "CPlayer.hpp"
#include "CLevel.hpp"
#include "CollisionHandler.hpp"

// =============================================================================
// CFlexibleSwing constructor/destructor
// -----------------------------------------------------------------------------
CFlexibleSwing::CFlexibleSwing(CPlayer *theBob, CLevel *theParentLevel)
:   CSwing(theBob, theParentLevel)
{
    // Make it brown
    mColour = CColour(139, 119, 101);
}

CFlexibleSwing::~CFlexibleSwing()
{

}

// =============================================================================
// CFlexibleSwing::AttemptToAttach
// -----------------------------------------------------------------------------
void CFlexibleSwing::AttemptToAttach(CVector2f theAimPoint)
{
    // Make sure we clear the list of previous origins
    mPreviousOrigins.clear();
    
    // Call the parent method
    CSwing::AttemptToAttach(theAimPoint);
}

// =============================================================================
// CFlexibleSwing::Draw
// -----------------------------------------------------------------------------
void CFlexibleSwing::Draw(CWindow *theWindow)
{
    // Call the parent method
    CSwing::Draw(theWindow);
    
    // Draw the inactive sections
    CVector2f lastOrigin = mOrigin;
    FOR_EACH_IN_LIST(CVector2f, mPreviousOrigins)
    {
        CVector2f thisOrigin = (*it);
        
        // If we're not on the first origin draw the line between this one and
        // the last one
        if (it != mPreviousOrigins.begin())
        {
            DrawSwingSection(theWindow, lastOrigin, thisOrigin);
        }
        
        // Update loop values
        lastOrigin = thisOrigin;
    }
    
    // Draw the section from the last origin to the current one
    DrawSwingSection(theWindow, lastOrigin, mOrigin);
}

// =============================================================================
// CFlexibleSwing::Update
// -----------------------------------------------------------------------------
void CFlexibleSwing::Update(CTime elapsedTime)
{
    // Call the parent method
    CSwing::Update(elapsedTime);
    
    if (!mPreviousOrigins.empty())
    {
        // Construct a triangle with corners previous origin, current origin
        // and bob position
        // If this doesnt intersect any obstacles then we can unwrap
        bool shouldUnwrap = true;
        
        CVector2f previousOrigin = mPreviousOrigins.back();
        std::list<CVector2f> trianglePoints;
        trianglePoints.push_back(previousOrigin);
        trianglePoints.push_back(mOrigin);
        trianglePoints.push_back(mBob->GetPosition());
        CConvexShape unwrapTriangle = CConvexShape(trianglePoints);
        
        std::list<CPhysicsBody*> theObstacles = mParentLevel->GetObstacles();
        FOR_EACH_IN_LIST(CPhysicsBody*, theObstacles)
        {
            CConvexShape thisShape = *((*it)->GetShape());
            
            CVector2f v;
            if (CollisionHandler::AreColliding(unwrapTriangle, thisShape, &v))
            {
                shouldUnwrap = false;
            }
        }
        
        if (shouldUnwrap)
        {
            // Calculate the new active length
            CVector2f currentOriginToOld = previousOrigin - mOrigin;
            mLength += currentOriginToOld.GetMagnitude();
            
            // And use the older origin
            mPreviousOrigins.pop_back();
            mOrigin = previousOrigin;
        }
    }
}

// =============================================================================
// CFlexibleSwing::HandleInput
// -----------------------------------------------------------------------------
void CFlexibleSwing::HandleInput(CTime elapsedTime)
{
    // Call the parent method
    CSwing::HandleInput(elapsedTime);
    
    // Clamp the length to max length - inactive length
    mLength = std::min(mLength, smMaxLength - GetInactiveLength());
}

// =============================================================================
// CFlexibleSwing::RespondToCollisionAt
// -----------------------------------------------------------------------------
void CFlexibleSwing::RespondToCollisionAt(CVector2f intersectionPoint)
{
    CVector2f newOrigin = intersectionPoint;
    
    // Calculate the new active length
    CVector2f currentOriginToNew = newOrigin - mOrigin;
    float newLength = mLength - currentOriginToNew.GetMagnitude();
    
    // Only split if we're not shorter than the min length
    if (newLength >= smMinLength)
    {
        mLength = newLength;
    
        // And use the new origin
        mPreviousOrigins.push_back(mOrigin);
        mOrigin = newOrigin;
    }
    else
    {
        // Otherwise respond as if we were a rigid swing
        CSwing::RespondToCollisionAt(intersectionPoint);
    }
}

// =============================================================================
// CFlexibleSwing::GetInactiveLength
// -----------------------------------------------------------------------------
float CFlexibleSwing::GetInactiveLength()
{
    // Go through the list of previous origins keeping a running total of
    // distances between them
    float inactiveLength = 0.0f;
    CVector2f lastOrigin = mOrigin;
    
    std::list<CVector2f>::iterator it = mPreviousOrigins.begin();
    while (it != mPreviousOrigins.end())
    {
        CVector2f thisOrigin = (*it);
        
        // Only add to the running total if this isn't the first one
        if (it != mPreviousOrigins.begin())
        {
            CVector2f lastToThis = thisOrigin - lastOrigin;
            inactiveLength += lastToThis.GetMagnitude();
        }
        
        // Update loop values
        lastOrigin = thisOrigin;
        it++;
    }
    
    // Add on the distance from the last origin to the current active one
    CVector2f lastToCurrent = mOrigin - lastOrigin;
    inactiveLength += lastToCurrent.GetMagnitude();
    
    return inactiveLength;
}