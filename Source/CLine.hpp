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
    
    CVector2f GetMidpoint();
    CVector2f GetNormal();
    
private:
    CVector2f mStart;
    CVector2f mEnd;
    CVector2f mNormal;
};

#endif /* defined(__SwingGame__CLine__) */
