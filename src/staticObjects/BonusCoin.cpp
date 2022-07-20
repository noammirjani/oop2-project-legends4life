#include "StaticObjects/BonusCoin.h"

//-----------------------------------------------------------------------------
bool BonusCoin::m_registerit = Factory<StaticObject>::registerit("BonusCoin",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<BonusCoin>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
BonusCoin::BonusCoin(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: Bonus(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, offsetBody)
{
	m_objectBody->SetUserData(this);
}