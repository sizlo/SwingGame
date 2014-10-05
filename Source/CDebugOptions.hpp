//
//  CDebugOptions.hpp
//  SwingGame
//
//  Created by Tim Brier on 05/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef SwingGame_CDebugOptions_hpp
#define SwingGame_CDebugOptions_hpp

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CDebugOptions
{
public:
    static bool smShowFramerate;
    static bool smDrawSpriteBounds;
    static bool smDrawSpriteOrigins;
};

bool CDebugOptions::smShowFramerate     = true;
bool CDebugOptions::smDrawSpriteBounds  = true;
bool CDebugOptions::smDrawSpriteOrigins = true;

#endif
