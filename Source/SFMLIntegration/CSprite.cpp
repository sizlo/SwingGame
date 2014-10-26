//
//  CSprite.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CSprite.hpp"
#include "CTexture.hpp"
#include "../CTextureBank.hpp"

// =============================================================================
// CSprite constructor/destructor
// -----------------------------------------------------------------------------
CSprite::CSprite() : sf::Sprite()
{
    
}

CSprite::CSprite(std::string filename) : sf::Sprite()
{
    CTexture *theTexture = CTextureBank::GetTexture(filename);
    setTexture(*theTexture);
}

CSprite::CSprite(std::string filename, bool flipX, bool flipY) : sf::Sprite()
{
    CTexture *theTexture = CTextureBank::GetTexture(filename, flipX, flipY);
    setTexture(*theTexture);
}


CSprite::~CSprite()
{
    
}