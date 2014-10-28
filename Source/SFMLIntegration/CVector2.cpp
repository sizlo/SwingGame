//
//  CVector2.cpp
//  SwingGame
//
//  Created by Tim Brier on 18/10/2014.
//  Copyright (c) 2014 tbrier. All rights reserved.
//

// =============================================================================
// Include files
// -----------------------------------------------------------------------------
#include <math.h>

// =============================================================================
// CVector2 constructor/destructor
// -----------------------------------------------------------------------------
template <typename T>
CVector2<T>::CVector2() : sf::Vector2<T>()
{
    
}

template <typename T>
CVector2<T>::CVector2(T X, T Y) : sf::Vector2<T>(X, Y)
{
    
}

template <typename T>
CVector2<T>::CVector2(sf::Vector2<T> other)
: sf::Vector2<T>(other)
{
    
}

template <typename T>
CVector2<T>::~CVector2()
{
    
}

template <typename T> template <typename U>
CVector2<T>::CVector2(CVector2<U> other) : sf::Vector2<T>(other)
{
    
}

// =============================================================================
// CVector2::GetMagnitude
// -----------------------------------------------------------------------------
template <typename T>
T CVector2<T>::GetMagnitude()
{
    return sqrt(this->x * this->x + this->y * this->y);
}

// =============================================================================
// CVector2::Normalise
// -----------------------------------------------------------------------------
template <typename T>
void CVector2<T>::Normalise()
{
    T length = GetMagnitude();
    this->x /= length;
    this->y /= length;
}

// =============================================================================
// CVector2::DotProduct
// -----------------------------------------------------------------------------
template <typename T>
T CVector2<T>::DotProduct(CVector2<T> rhs)
{
    return (this->x * rhs.x) + (this->y * rhs.y);
}