//
//  CTextureBank.hpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CTextureBank__
#define __SwingGame__CTextureBank__

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "SFMLIntegration.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CTextureBank
{
public:
    // Load or get a loaded texture
    static CTexture * GetTexture(std::string filename);
    // Delete all loaded textures
    static void Cleanup();
    
private:
    static std::map<std::string, CTexture *> smTextures;
};

#endif /* defined(__SwingGame__CTextureBank__) */
