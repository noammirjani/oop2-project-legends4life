#include "StaticObjects/StaticObject.h"


//-----------------------------------------------------------------------------
StaticObject::StaticObject(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld,const int resourseIndex,
							const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: GameObject(world, typeOfObjectInWorld, resourseIndex, position, rect, bodySize, offsetBody)
{
	
}