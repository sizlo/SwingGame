//
//  CPlayer.hpp
//  SwingGame
//
//  Created by Tim Brier on 11/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CPlayer__
#define __SwingGame__CPlayer__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CUpdateable.hpp"
#include "CRenderable.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CPlayer : public CUpdateable, public CRenderable
{
public:
    CPlayer();
    ~CPlayer();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Init();
    void Cleanup();
    
private:
    CConvexShape    mShape;
};

#endif /* defined(__SwingGame__CPlayer__) */
