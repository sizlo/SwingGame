//
//  CView.hpp
//  SwingGame
//
//  Created by Tim Brier on 29/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CView__
#define __SwingGame__CView__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CFloatRect.hpp"

// =============================================================================
// Class Definition
// -----------------------------------------------------------------------------
class CView : public sf::View
{
public:
    CView();
    CView(CFloatRect theRect);
    ~CView();
};

#endif /* defined(__SwingGame__CView__) */
