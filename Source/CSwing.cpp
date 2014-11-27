//
//  CSwing.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSwing.hpp"
#include "CSwingGame.hpp"
#include "CLevel.hpp"
#include "CollisionHandler.hpp"

// =============================================================================
// Static variables
// -----------------------------------------------------------------------------
static float sMaxLength = 500.0f;
static float sClimbSpeed = 100.0f;
static float sCollisionIgnoreDistance = 0.0f;
static float sAnchorGap = 5.0f;
static float sReflectionScaleFactor = -1.0f;

// =============================================================================
// CSwing constructor/destructor
// -----------------------------------------------------------------------------
CSwing::CSwing(CPlayer *theBob, CLevel *theParentLevel)
:   mBob(theBob),
    mParentLevel(theParentLevel),
    mAttached(false)
{
    
}

CSwing::~CSwing()
{
    // Unregister this x-able
    if (mAttached)
    {
        CSwingGame::UnregisterRenderable(this);
        CSwingGame::UnregisterUpdateable(this);
    }
}

// =============================================================================
// CSwing::AttemptToAttach
// Find the first point between the bob and the aim point to attach to
// -----------------------------------------------------------------------------
void CSwing::AttemptToAttach(CVector2f theAimPoint)
{
    // Attach the swing if we can find a valid anchor point
    CVector2f anchorPoint;
    if (IsThereAValidAnchor(theAimPoint, &anchorPoint))
    {
        // Make sure we detach from any existing swing
        Detach();
        
        // Now attach
        mAttached = true;
        
        mOrigin = anchorPoint;
        mLength = GetDistanceToBob();
        
        // Find where we should draw the origin
        CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
        bobToOrigin.Normalise();
        mOriginDrawPoint = mOrigin + (bobToOrigin * sAnchorGap);
        
        // Throw away any velocity that isn't perpendicular to the swing
        CVector2f v = mBob->GetVelocity();
        CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
        mBob->SetVelocity(newV);
        
        // Register ourselves now we're active
        CSwingGame::RegisterRenderable(this);
        CSwingGame::RegisterUpdateable(this);
    }
}

// =============================================================================
// CSwing::Detach
// -----------------------------------------------------------------------------
void CSwing::Detach()
{
    if (mAttached)
    {
        mAttached = false;
        CSwingGame::UnregisterUpdateable(this);
        CSwingGame::UnregisterRenderable(this);
    }
}

// =============================================================================
// CSwing::AttenuateGravity
// Alter the affect of gravity based on the swings angle
// -----------------------------------------------------------------------------
CVector2f CSwing::AttenuateGravity(CVector2f gravity)
{
    // If we're not attached then don't affect gravity
    if (!mAttached)
    {
        return gravity;
    }
    
    // Throw away any component of the gravity that isn't perpendicular to the
    // swing
    return gravity.GetComponentInDirection(GetPerpendicularDirection());
}

// =============================================================================
// CSwing::Draw
// -----------------------------------------------------------------------------
void CSwing::Draw(CWindow *theWindow)
{
    // The line
    theWindow->DrawLine(CLine(mOrigin, mBob->GetPosition()), CColour::Black);
    
    // The anchor
    sf::CircleShape theOrigin(sAnchorGap);
    theOrigin.setOrigin(CVector2f(sAnchorGap, sAnchorGap));
    theOrigin.setPosition(mOrigin);
    theOrigin.setOutlineColor(CColour::Black);
    theOrigin.setOutlineThickness(1.0f);
    theOrigin.setFillColor(CColour::Transparent);
    theWindow->draw(theOrigin);
}

// =============================================================================
// CSwing::Update
// -----------------------------------------------------------------------------
void CSwing::Update(CTime elapsedTime)
{
    if (mAttached)
    {
        HandleInput(elapsedTime);
        
        // Adjust the velocity so it is perpendicular to the swing
        CVector2f v = mBob->GetVelocity();
        CVector2f newV = v.GetComponentInDirection(GetPerpendicularDirection());
        newV.Normalise();
        newV *= v.GetMagnitude();
        mBob->SetVelocity(newV);
        
        // Make sure the bob isn't further away from the origin than the length
        // of the swing
        CVector2f bobToOrigin = mOrigin - mBob->GetPosition();
        float distance = bobToOrigin.GetMagnitude();
        if (distance > mLength)
        {
            // Move by the difference between the distance and length
            float moveDistance = distance - mLength;
            bobToOrigin.Normalise();
            bobToOrigin *= moveDistance;
            mBob->GetShape()->move(bobToOrigin);
        }
        
        HandleCollisions();
    }
}

// =============================================================================
// CSwing::IsAttached
// -----------------------------------------------------------------------------
bool CSwing::IsAttached()
{
    return mAttached;
}

// =============================================================================
// CSwing::GetDistanceToBob
// -----------------------------------------------------------------------------
float CSwing::GetDistanceToBob()
{
    CVector2f bobPosition = mBob->GetPosition();
    CVector2f bobToOrigin = mOrigin - bobPosition;
    return bobToOrigin.GetMagnitude();
}

// =============================================================================
// CSwing::IsThereAValidAnchor
// -----------------------------------------------------------------------------
bool CSwing::IsThereAValidAnchor(CVector2f theAimPoint, CVector2f *anchor)
{
    bool theResult = false;
    
    // Find the direction from the bob to the aim point
    CVector2f bobPosition = mBob->GetPosition();
    CVector2f aimDirection = theAimPoint - bobPosition;
    aimDirection.Normalise();
    
    // Create a line from the bob to the max distance away that a swing could
    // reach in the aim direction
    CLine longestPossile = CLine(bobPosition,
                                 bobPosition + (aimDirection * sMaxLength));
    
    // Find the closest intersection of this line and any obstacle lines to the
    // bob
    *anchor = longestPossile.GetEnd();
    float currentDistanceToAnchor = sMaxLength;
    
    std::list<CPhysicsBody *> theObstacles = mParentLevel->GetObstacles();
    FOR_EACH_IN_LIST(CPhysicsBody*, theObstacles)
    {
        std::list<CVector2f> theIntersections;
        if (CollisionHandler::AreIntersecting(longestPossile,
                                              *((*it)->GetShape()),
                                              &theIntersections))
        {
            theResult = true;
            FOR_EACH_IN_LIST(CVector2f, theIntersections)
            {
                CVector2f thisIntersection = (*it);
                CVector2f bobToThis = thisIntersection - bobPosition;
                float distanceToThis = bobToThis.GetMagnitude();
                if (distanceToThis < currentDistanceToAnchor
                    && distanceToThis > sAnchorGap)
                {
                    float distanceToUse = distanceToThis - sAnchorGap;
                    bobToThis.Normalise();
                    *anchor = bobPosition + (bobToThis * distanceToUse);
                    currentDistanceToAnchor = distanceToUse;
                }
            }
        }
    }
    
    return theResult;
}

// =============================================================================
// CSwing::GetPerpendicularDirection
// -----------------------------------------------------------------------------
CVector2f CSwing::GetPerpendicularDirection()
{
    CVector2f originToBob = mBob->GetPosition() - mOrigin;
    originToBob.Normalise();
    
    CVector2f perpendicularDirection;
    perpendicularDirection.x = originToBob.y;
    perpendicularDirection.y = -originToBob.x;
    
    return perpendicularDirection;
}

// =============================================================================
// CSwing::HandleInput
// -----------------------------------------------------------------------------
void CSwing::HandleInput(CTime elapsedTime)
{
    CVector2f climbOffset = CVector2f(0.0f, 0.0f);
    CVector2f climbDirection = mOrigin - mBob->GetPosition();
    climbDirection.Normalise();
    
    // Climb while w is pressed
    if (CKeyboard::isKeyPressed(CKeyboard::W))
    {
        climbOffset += climbDirection * sClimbSpeed * elapsedTime.asSeconds();
    }
    
    // Descend while s is presses
    if (CKeyboard::isKeyPressed(CKeyboard::S))
    {
        climbOffset -= climbDirection * sClimbSpeed * elapsedTime.asSeconds();
    }
    
    if (climbOffset .GetMagnitude() > 0)
    {
        mBob->MoveFixedDistanceUntilCollision(climbOffset);
        mLength = GetDistanceToBob();
        mLength = std::min(mLength, sMaxLength);
    }
}

// =============================================================================
// CSwing::HandleCollisions
// -----------------------------------------------------------------------------
void CSwing::HandleCollisions()
{
    // Keep track of the closest intersection to the origin we care about
    bool validIntersectionFound = false;
    float distanceToIntersection = sMaxLength;
    
    // Check for collisions with all obstacles in the level
    CLine theLine = CLine(mOrigin, mBob->GetPosition());
    std::list<CPhysicsBody *> theObstacles = mParentLevel->GetObstacles();
    FOR_EACH_IN_LIST(CPhysicsBody*, theObstacles)
    {
        CPhysicsBody *theObs = (*it);
        CConvexShape theShape = *(theObs->GetShape());
        
        std::list<CVector2f> theIntPoints;
        if (CollisionHandler::AreIntersecting(theLine, theShape, &theIntPoints))
        {
            FOR_EACH_IN_LIST(CVector2f, theIntPoints)
            {
                CVector2f thisIntersection = (*it);
                CVector2f originToInt = thisIntersection - mOrigin;
                float distanceToThisIntersection = originToInt.GetMagnitude();
                
                if (distanceToThisIntersection > sCollisionIgnoreDistance)
                {
                    validIntersectionFound = true;
                    
                    // Only record this if its closer to the origin
                    if (distanceToThisIntersection < distanceToIntersection)
                    {
                        distanceToIntersection = distanceToThisIntersection;
                    }
                }
            }
        }
    }
    
    // If we found a collision we care about then handle it
    if (validIntersectionFound)
    {
        RespondToCollisionAt(distanceToIntersection);
    }
}

// =============================================================================
// CSwing::RespondToCollisionAt
// -----------------------------------------------------------------------------
void CSwing::RespondToCollisionAt(float distanceFromOrigin)
{
    // For this rigid swing we'll just reflect the players velocity
    // Apply a scaling factor as well so we can dampen it
    mBob->SetVelocity(mBob->GetVelocity() * sReflectionScaleFactor);
}