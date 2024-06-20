#include "MovingObject/Trap.h"

//----------------------------- CONSTRUCTOR -----------------------------------
Trap::Trap(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	:MovingObject(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, offsetBody),
	 m_startPosition(sf::Vector2f(position.x - offsetBody.x, position.y - offsetBody.y))
{
	createBodyFixture(bodySize, 1.f, 1.f, TrapsBits, playerBits | MagicEffectBits |PaltformBits);
	m_animation.setRect();
	m_time.restart();
	m_objectBody->SetUserData(this);
	m_objectBody->SetAwake(false);
	m_objectBody->SetGravityScale(0);
}
