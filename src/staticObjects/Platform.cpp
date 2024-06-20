#include "StaticObjects/Platform.h"


//-----------------------------------------------------------------------------
bool Platform::m_registerit = Factory<StaticObject>::registerit("Platform",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<Platform>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody);});


//-----------------------------------------------------------------------------
Platform::Platform(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex, const sf::Vector2f& position,
					const sf::IntRect& rect, const sf::Vector2f& spriteRow, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: StaticObject(world, typeOfObjectInWorld,resourseIndex, position, rect, bodySize, offsetBody)
{
	createBodyFixture(bodySize, 1.f, 1.f, PaltformBits, playerBits | MagicEffectBits | TrapsBits | BoxBits | EnemyBits);
	m_objectBody->SetUserData(this);
}