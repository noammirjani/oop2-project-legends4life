#include "MovingObject/MovingObject.h"
#include <iostream>


//-----------------------------------------------------------------------------
MovingObject::MovingObject(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
						const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: GameObject(world, typeOfObjectInWorld,resourseIndex, position, rect, bodySize, bodyOffset), m_animation(sf::Vector2f(rect.width,rect.height), frameLimit, m_sprite)
{
}
//-----------------------------------------------------------------------------
void MovingObject::specialAnimation(const int row)
{
	m_animation.setRowAnimation(row);
	m_animation.setFrameByClock(true);
}

