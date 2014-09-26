//
//  Main.cpp
//  SwingGame
//
//  Created by Tim Brier on 26/09/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSwingGame.hpp"


// =============================================================================
// Program entry point
// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    CSwingGame theGame;
    theGame.Init();
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
