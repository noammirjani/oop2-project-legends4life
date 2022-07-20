#include "StaticObjects/Bonus.h"

//-----------------------------------------------------------------------------
Bonus::Bonus(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: StaticObjectAnimation(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, offsetBody)
{
	createBodyFixture(bodySize, 1.f, 1.f, BonusBits, playerBits);
	m_objectBody->GetFixtureList()->SetSensor(true);
}