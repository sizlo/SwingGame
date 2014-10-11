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
#include "SFMLIntegration.hpp"

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
    CVector2f GetNormal();
    
    bool Intersects(CLine other);
    
private:
    CVector2f mStart;
    CVector2f mEnd;
    CVector2f mNormal;
};

#endif /* defined(__SwingGame__CLine__) */
