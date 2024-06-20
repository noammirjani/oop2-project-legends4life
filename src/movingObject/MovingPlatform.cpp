#include "MovingObject/MovingPlatform.h"

//-----------------------------------------------------------------------------
bool MovingPlatform::m_registerit = Factory<MovingObject>::registerit("MovingPlatform",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<MovingObject> { return std::make_unique<MovingPlatform>(world, b2_kinematicBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//----------------------------------------------------------------------------
MovingPlatform::MovingPlatform(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorldconst, int resourseIndex, const sf::Vector2f& position,
	const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	:MovingObject(world, typeOfObjectInWorldconst, resourseIndex, position, rect, frameLimit, bodySize, offsetBody), m_startPosition(sf::Vector2f(position.x - offsetBody.x, position.y - offsetBody.y)), m_offset(frameLimit.x), m_speed(frameLimit.y)
{
	createBodyFixture(bodySize, 1.f, 1.f, PaltformBits, playerBits | MagicEffectBits | TrapsBits | EnemyBits);
	m_time.restart();
	m_objectBody->SetUserData(this);
	m_objectBody->SetAwake(false);

}

//----------------------------------------------------------------------------
void MovingPlatform::move()
{
	auto pos = m_objectBody->GetLinearVelocity();
	auto offset = updatePhysically();
	if (offset > 0) {
		m_objectBody->SetLinearVelocity({ 0 , offset });
	}
	else if (offset < 0) {
		m_objectBody->SetLinearVelocity({ 0, offset });
	}
}


//-----------------------------------------------------------------------------
float MovingPlatform::updatePhysically()
{
	auto currPos = m_sprite.getPosition().y;
	if (currPos > m_startPosition.y + m_offset) {// go Up
		m_changeDirection = true;

	}
	else if (currPos < m_startPosition.y - m_offset) { // go Down
		m_changeDirection = false;
	}

	if (m_changeDirection)
		return -m_speed;

	return m_speed;
}
