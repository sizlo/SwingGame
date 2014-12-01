//
//  CLine.hpp
//  SwingGame
//
//  Created by Tim Brier on 10/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CLine__
#define __SwingGame__CLine__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
// Only include the vector header to get around circular include issue
#include "SFMLIntegration/CVector2.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CLine
{
public:
    CLine(CVector2f start, CVector2f end);
    ~CLine();
    
    // Getters
    CVector2f GetStart();
    CVector2f GetEnd();
    CVector2f GetMidpoint();
    CVector2f GetDirection();
    CVector2f GetNormal();
    float     GetLength();
    
    bool Intersects(CLine other, CVector2f *intersectinoPoint);
    
private:
    CVector2f mStart;
    CVector2f mEnd;
    CVector2f mDirection;
    CVector2f mNormal;
};

// =============================================================================
// Operators
// -----------------------------------------------------------------------------
bool operator == (CLine lhs, CLine rhs);

#endif /* defined(__SwingGame__CLine__) */
