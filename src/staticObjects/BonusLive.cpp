
#include "StaticObjects/BonusLive.h"
//-----------------------------------------------------------------------------
bool BonusLive::m_registerit = Factory<StaticObject>::registerit("BonusLive",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<BonusLive>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
BonusLive::BonusLive(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: Bonus(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, offsetBody)
{
	m_objectBody->SetUserData(this);
}