#include "StaticObjects/WaterTrap.h"

//-----------------------------------------------------------------------------
bool WaterTrap::m_registerit = Factory<StaticObject>::registerit("WaterTrap",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<WaterTrap>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
WaterTrap::WaterTrap(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: StaticObjectAnimation(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, offsetBody)
{
	createBodyFixture(bodySize, 1.f, 1.f, WaterBits, playerBits);
	m_objectBody->SetUserData(this);
}