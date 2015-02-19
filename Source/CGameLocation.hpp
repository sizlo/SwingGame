//
//  CGameLocation.hpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CGameLocation_hpp
#define SwingGame_CGameLocation_hpp

// =============================================================================
// Game location enum
// -----------------------------------------------------------------------------
enum EGameLocation
{
    kGameLocationFrontEnd,
    kGameLocationLevel
};

// =============================================================================
// Abstract class definition
// -----------------------------------------------------------------------------
class CGameLocation
{
public:
    virtual ~CGameLocation(){};
    
    virtual void Enter() = 0;
    virtual void Exit() = 0;
};

#endif
