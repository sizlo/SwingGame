//
//  CVector2.hpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

#ifndef __SwingGame__CVector2__
#define __SwingGame__CVector2__

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

// =============================================================================
// Class definition
// -----------------------------------------------------------------------------
template <typename T> class CVector2 : public sf::Vector2<T>
{
public:
    CVector2();
    CVector2(T X, T Y);
    CVector2(sf::Vector2<T> other);
    ~CVector2();
    
    // Conversion from another vector type
    template <typename U> CVector2(CVector2<U> other);
    
    // Normalise a vector to unit length 1
    void Normalise();
    
    // Get the dot product of this and another vector
    T DotProduct(CVector2<T> rhs);
};

// =============================================================================
// Include the method definitions since they are required prior to instantiating
// a template class
// -----------------------------------------------------------------------------
#include "CVector2.cpp"

// =============================================================================
// Common typedefs
// -----------------------------------------------------------------------------
typedef CVector2<float> CVector2f;
typedef CVector2<int>   CVector2i;

#endif /* defined(__SwingGame__CVector2__) */
