//
//  CVertex.hpp
//  SwingGame
//
//  Created by Tim Brier on 31/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CVertex__
#define __SwingGame__CVertex__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "CVector2.hpp"
#include "CColour.hpp"

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
class CVertex : public sf::Vertex
{
public:
    CVertex();
    CVertex(CVector2f thePosition, CColour theColour);
    ~CVertex();
};


#endif /* defined(__SwingGame__CVertex__) */
