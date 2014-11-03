//
//  CVertex.cpp
//  SwingGame
//
//  Created by Tim Brier on 31/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include Files
// -----------------------------------------------------------------------------
#include "CVertex.hpp"

// =============================================================================
// CVertex constructor/destructor
// -----------------------------------------------------------------------------
CVertex::CVertex() : sf::Vertex()
{
    
}

CVertex::CVertex(CVector2f thePosition, CColour theColour)
:   sf::Vertex(thePosition, theColour)
{
    
}

CVertex::~CVertex()
{
    
}