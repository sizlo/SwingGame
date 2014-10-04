//
//  CTextureBank.cpp
//  SwingGame
//
//  Created by Tim Brier on 04/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CTextureBank.hpp"
#include "CSystemUtilities.hpp"

// =============================================================================
// Static members
// -----------------------------------------------------------------------------
std::map<std::string, CTexture *> CTextureBank::smTextures;

// =============================================================================
// CTextureBank::GetTexture
// If a texture is not yet loaded then load it, otherwise return the already
// loaded one
// -----------------------------------------------------------------------------
CTexture * CTextureBank::GetTexture(std::string filename)
{
    // Load a texture if we don't have it
    if (smTextures[filename] == NULL)
    {
        CTexture *theTexture = new CTexture();
        theTexture->loadFromFile(CSystemUtilities::GetResourcePath() + filename);
        smTextures[filename] = theTexture;
    }
    
    return smTextures[filename];
}

// =============================================================================
// CTextureBank::Cleanup
// Delete all loaded textures
// -----------------------------------------------------------------------------
void CTextureBank::Cleanup()
{
    for (std::map<std::string, CTexture *>::iterator it = smTextures.begin();
         it != smTextures.end();
         ++it)
    {
        SAFE_DELETE(it->second);
    }
}