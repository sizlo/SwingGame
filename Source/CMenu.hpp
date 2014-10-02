//
//  CMenu.hpp
//  SwingGame
//
//  Created by Tim Brier on 02/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CMenu_hpp
#define SwingGame_CMenu_hpp

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CDrawable.hpp"
#include "CUpdateable.hpp"

// =============================================================================
// Abstract class definition
// -----------------------------------------------------------------------------
class CMenu : public CDrawable, public CUpdateable
{
public:
    virtual ~CMenu(){};
    
    virtual void Enter() = 0;
    virtual void Draw(CWindow *theWindow) = 0;
    virtual void Update(CTime elapsedTime) = 0;
private:
    virtual void Exit() = 0;
};

#endif
