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
#include "SystemUtilities.hpp"
#include <sstream>

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
        theTexture->loadFromFile(SystemUtilities::GetResourcePath() + filename);
        smTextures[filename] = theTexture;
    }
    
    return smTextures[filename];
}

// =============================================================================
// CTextureBank::GetTexture
// Get or load a texture which has a flip applied to the image file
// -----------------------------------------------------------------------------
CTexture * CTextureBank::GetTexture(std::string filename, bool flipX, bool flipY)
{
    std::string theIdentifier = filename;
    if (flipX)
        theIdentifier += "flipx";
    if (flipY)
        theIdentifier += "flipy";
    
    // Load a texture if we don't have it
    if (smTextures[theIdentifier] == NULL)
    {
        // Load and flip the image
        CImage theImage;
        theImage.loadFromFile(SystemUtilities::GetResourcePath() + filename);
        if (flipX)
            theImage.flipHorizontally();
        if (flipY)
            theImage.flipVertically();
        
        CTexture *theTexture = new CTexture();
        theTexture->loadFromImage(theImage);
        smTextures[theIdentifier] = theTexture;
    }
    
    return smTextures[theIdentifier];
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