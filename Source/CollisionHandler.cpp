//
//  CollisionHandler.cpp
//  SwingGame
//
//  Created by Tim Brier on 28/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CollisionHandler.hpp"

// =============================================================================
// Helper methods
// -----------------------------------------------------------------------------
bool CROptionHasAllFlags(ECollisionResolveOptions theOptions,
                         ECollisionResolveOptions theFlags)
{
    ECollisionResolveOptions theResult =
                static_cast<ECollisionResolveOptions>(theOptions & theFlags);
    return theResult == theFlags;
}

namespace CollisionHandler
{
    
// =============================================================================
// CollisionHandler::AreColliding
// Check for collisions between 2 convex shapes
// -----------------------------------------------------------------------------
bool AreColliding(CConvexShape &lhs,
                  CConvexShape &rhs,
                  CVector2f *correctionVector)
{
    // First check the bounding box as an early out
    if (!lhs.getGlobalBounds().intersects(rhs.getGlobalBounds()))
    {
        // Bounding boxes don't intersect, there is no collision
        return false;
    }
    
    // Now use separating axis theorem
    //
    // Try to find an axis we can project all points on where no points of
    // either shape overlaps the other
    // If we can't then we have a collision
    //
    // The axis we need to try project onto are the normals to each side of each
    // shape
    
    // Keep track of whether we've overlapped on an axis already
    bool haveOverlapped = false;
    
    // Keep a list of the axes we've already checked so we don't check dupes
    std::list<CVector2f> projectionAxesChecked;
    
    // Check all shape lines
    std::list<CLine> lhsLines = lhs.GetGlobalLines();
    std::list<CLine> rhsLines = rhs.GetGlobalLines();
    std::list<CLine> theLines;
    theLines.insert(theLines.end(), lhsLines.begin(), lhsLines.end());
    theLines.insert(theLines.end(), rhsLines.begin(), rhsLines.end());
    
    FOR_EACH_IN_LIST(CLine, theLines)
    {
        // Get the vector for this axis
        CVector2f axis = (*it).GetNormal();
        
        // Make sure we've not already checked this axis, or it's inverse
        CVector2f inverseAxis = -axis;
        bool alreadyChecked = false;
        FOR_EACH_IN_LIST(CVector2f, projectionAxesChecked)
        {
            if ((*it) == axis || (*it) == inverseAxis)
            {
                alreadyChecked = true;
            }
        }
        
        if (!alreadyChecked)
        {
            // We haven't checked this axis yet
            // See if we're overlapping in it, if we're not then the shapes
            // can't be colliding
            CVector2f thisCV;
            if (!AreOverlapping(lhs, rhs, axis, &thisCV))
            {
                // There is no collision
                return false;
            }
            else
            {
                // If the correction vector for this overlap is the smallest yet
                // then remember it
                if (thisCV.GetMagnitude() < correctionVector->GetMagnitude()
                    || !haveOverlapped)
                {
                    *correctionVector = thisCV;
                }
                
                // We've now had an overlap
                haveOverlapped = true;
            }
            
            // Add this axis to the list of checked ones and move on to the next
            projectionAxesChecked.push_back(axis);
        }
    }
    
    // If we've reached here then we must be colliding
    return true;
}
    
// =============================================================================
// CollisionHandler::AreOverlapping
// -----------------------------------------------------------------------------
bool AreOverlapping(CConvexShape &lhs,
                    CConvexShape &rhs,
                    CVector2f axis,
                    CVector2f *correctionVector)
{
    bool theResult = false;
    
    // Project all points of either shape onto the axis, keep track of the min
    // and max of each shape
    float lhsMin, rhsMin, lhsMax, rhsMax;
    
    // Initialise min and max to the projection value of the first point
    // of each shape
    lhsMin = Project(lhs.GetGlobalPoint(0), axis);
    lhsMax = lhsMin;
    rhsMin = Project(rhs.GetGlobalPoint(0), axis);
    rhsMax = rhsMin;
    
    int lhsPointCount = lhs.getPointCount();
    for (int i = 1; i < lhsPointCount; i++)
    {
        float projectionValue = Project(lhs.GetGlobalPoint(i), axis);
        lhsMin = std::min(lhsMin, projectionValue);
        lhsMax = std::max(lhsMax, projectionValue);
    }
    
    int rhsPointCount = rhs.getPointCount();
    for (int i = 1; i < rhsPointCount; i++)
    {
        float projectionValue = Project(rhs.GetGlobalPoint(i), axis);
        rhsMin = std::min(rhsMin, projectionValue);
        rhsMax = std::max(rhsMax, projectionValue);
    }
    
    // We're overlapping if the max projection point of either shape is in
    // between the max or min of the other
    if ((lhsMax >= rhsMin && lhsMax <= rhsMax)
        || (rhsMax >= lhsMin && rhsMax <= lhsMax))
    {
        theResult = true;
        
        // Find the smallest distance we have to move on this axis to escape
        // the collision
        // We assume that the lhs object is the one to move
        float leftEscapeDistance = lhsMax - rhsMin;
        float rightEscapeDistance = rhsMax - lhsMin;
        
        // The vector will be a scaled value of the current axis
        correctionVector->x = axis.x;
        correctionVector->y = axis.y;
        
        // If we're moving left the vector will be negatively scaled, if right
        // it will be positively scaled
        if (leftEscapeDistance < rightEscapeDistance)
        {
            *correctionVector *= -leftEscapeDistance;
        }
        else
        {
            *correctionVector *= rightEscapeDistance;
        }
    }
    
    return theResult;
}
    
// =============================================================================
// CollisionHandler::Project
// -----------------------------------------------------------------------------
bool AreIntersecting(CLine &theLine,
                     CConvexShape &theShape,
                     std::list<CVector2f> *intersectionPoints,
                     bool returnCorners /* = true */)
{
    bool theResult = false;
    
    // Create a bounding box for the line
    float minX = std::min(theLine.GetStart().x, theLine.GetEnd().x);
    float minY = std::min(theLine.GetStart().y, theLine.GetEnd().y);
    float maxX = std::max(theLine.GetStart().x, theLine.GetEnd().x);
    float maxY = std::max(theLine.GetStart().y, theLine.GetEnd().y);
    CFloatRect lineBounds = CFloatRect(minX, minY, maxX - minX, maxY - minY);
    
    // Check the bounding box first
    if (!theShape.getGlobalBounds().intersects(lineBounds))
    {
        return false;
    }
    
    // Now check each line in the shape
    std::list<CLine> shapeLines = theShape.GetGlobalLines();
    FOR_EACH_IN_LIST(CLine, shapeLines)
    {
        CLine thisShapeLine = (*it);
        CVector2f thisIntersectionPoint;
        if (theLine.Intersects(thisShapeLine, &thisIntersectionPoint))
        {
            if (returnCorners)
            {
                // Find the closest corner of the shape to this point, as a line
                // will only ever collide at corners in the real world
                CVector2f closestPoint = theShape.GetGlobalPoint(0);
                CVector2f intToClosest = closestPoint - thisIntersectionPoint;
                float distanceToClosest = intToClosest.GetMagnitude();
                
                int numPoints = theShape.getPointCount();
                for (int i = 1; i < numPoints; i++)
                {
                    CVector2f thisPoint = theShape.GetGlobalPoint(i);
                    CVector2f intToThis = thisPoint - thisIntersectionPoint;
                    float distanceToThis = intToThis.GetMagnitude();
                    if (distanceToThis < distanceToClosest)
                    {
                        closestPoint = thisPoint;
                        intToClosest = intToThis;
                        distanceToClosest = distanceToThis;
                    }
                }
                
                thisIntersectionPoint = closestPoint;
            }
            
            intersectionPoints->push_back(thisIntersectionPoint);
            theResult = true;
        }
    }
    
    // Remove duplicates from the intersection points list
    intersectionPoints->unique();
    
    // If we're returning corners then move the intersection points out of the
    // shape
    if (returnCorners)
    {
        std::list<CVector2f> unalteredIntersectionPoints = *intersectionPoints;
        intersectionPoints->clear();
        
        FOR_EACH_IN_LIST(CVector2f, unalteredIntersectionPoints)
        {
            CVector2f thisIntersection = (*it);
            
            std::list<CLine> linesWithThisPoint;
            FOR_EACH_IN_LIST(CLine, shapeLines)
            {
                CLine thisLine = (*it);
                if (thisLine.GetEnd() == thisIntersection
                    || thisLine.GetStart() == thisIntersection)
                {
                    linesWithThisPoint.push_back(thisLine);
                }
            }
            
            // Average the normals of all points on this line
            CVector2f normalAverage = CVector2f(0.0f, 0.0f);
            FOR_EACH_IN_LIST(CLine, linesWithThisPoint)
            {
                normalAverage += (*it).GetNormal();
            }
            normalAverage /= (float)linesWithThisPoint.size();
            normalAverage.Normalise();
            
            // Move the intersection point by 1 unit in the average normal
            // direction
            thisIntersection += normalAverage * 1.0f;
            
            intersectionPoints->push_back(thisIntersection);
        }
    }
    
    return theResult;
}
    
// =============================================================================
// CollisionHandler::Project
// -----------------------------------------------------------------------------
float Project(CVector2f point, CVector2f axis)
{
    // Project a point onto an axis by performing the dot product between them
    return point.DotProduct(axis);
}

// =============================================================================
// CollisionHandler::Resolve
// -----------------------------------------------------------------------------
void Resolve(CPhysicsBody *lhs,
             CPhysicsBody *rhs,
             CVector2f correctionVector,
             float friction /* = 0.0f */,
             float elasticity /* = 1.0f */,
             ECollisionResolveOptions theOptions /* = kCRMoveLeft */)
{
    Seperate(lhs, rhs, correctionVector, friction, elasticity, theOptions);
    
    // Normalise the correction vector before responding
    correctionVector.Normalise();
    Respond(lhs, rhs, correctionVector, friction, elasticity, theOptions);
}

// =============================================================================
// CollisionHandler::Seperate
// -----------------------------------------------------------------------------
void Seperate(CPhysicsBody *lhs,
              CPhysicsBody *rhs,
              CVector2f correctionVector,
              float friction,
              float elasticity,
              ECollisionResolveOptions theOptions)
{
    // Move either one or both of the shapes by the correction vector so they
    // aren't penetrating anymore
    // The vector will be assuming the lhs body is moving so it will need
    // adjusting if this is not the case
    ECollisionResolveOptions bothSides = static_cast<ECollisionResolveOptions>
    (kCRMoveLeft | kCRMoveRight);
    if (CROptionHasAllFlags(theOptions, kCRMoveBoth)
        || CROptionHasAllFlags(theOptions, bothSides))
    {
        lhs->GetShape()->move(0.5f * correctionVector);
        rhs->GetShape()->move(-0.5f * correctionVector);
    }
    else if (CROptionHasAllFlags(theOptions, kCRMoveLeft))
    {
        lhs->GetShape()->move(correctionVector);
    }
    else if (CROptionHasAllFlags(theOptions, kCRMoveRight))
    {
        rhs->GetShape()->move(-correctionVector);
    }
    else
    {
        DEBUG_LOG("No valid collision resolve option");
    }
}
    
// =============================================================================
// CollisionHandler::Respond
// -----------------------------------------------------------------------------
void Respond(CPhysicsBody *lhs,
             CPhysicsBody *rhs,
             CVector2f normal,
             float friction,
             float elasticity,
             ECollisionResolveOptions theOptions)
{
    // Compute the collision response using the relative velocity of both
    // bodies and the normal to the collision
    CVector2f relativeVelocity = lhs->GetVelocity() - rhs->GetVelocity();
    
    // Work out the components of this relative velocity which are
    // perpendicular to the normal and paralel to the normal
    CVector2f perpComp = relativeVelocity.GetComponentInDirection(normal);
    CVector2f parComp = relativeVelocity - perpComp;
    
    // Reflect these components and scale based on friction and elasticity
    perpComp *= -(1.0f + elasticity);
    parComp *= -friction;
    
    // Combine them into the response
    CVector2f response = perpComp + parComp;
    
    // Scale this response based on each bodies relative mass and apply it
    float bothInvMasses = lhs->GetInverseMass() + rhs->GetInverseMass();
    lhs->AddVelocity(response * (lhs->GetInverseMass() / bothInvMasses));
    rhs->AddVelocity(-response * (rhs->GetInverseMass() / bothInvMasses));
}
    
} // namespace CollsionHandler