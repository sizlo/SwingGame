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

namespace CollisionHandler
{
    
// =============================================================================
// CollisionHandler::AreColliding
// Check for collisions between 2 convex shapes
// -----------------------------------------------------------------------------
bool AreColliding(CConvexShape &lhs, CConvexShape &rhs)
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
    // The axis we need to try project onto are the ones each side of each shape
    // lies on
    
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
        CVector2f axis = (*it).GetDirection();
        
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
            if (!AreOverlapping(lhs, rhs, axis))
            {
                // There is no collision
                return false;
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
bool AreOverlapping(CConvexShape &lhs, CConvexShape &rhs, CVector2f axis)
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
    
} // namespace CollsionHandler