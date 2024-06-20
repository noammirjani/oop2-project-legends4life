#include "StaticObjects/MineTrap.h"
#include <iostream>

//-----------------------------------------------------------------------------
bool MineTrap::m_registerit = Factory<StaticObject>::registerit("MineTrap",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<MineTrap>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
MineTrap::MineTrap(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: StaticObject(world, typeOfObjectInWorld, resourseIndex, position, rect, bodySize, bodyOffset),m_mineAnimation(sf::Vector2f(rect.width, rect.height), frameLimit, m_sprite)
{
	createBodyFixture(bodySize, 1.f, 1.f, WaterBits, playerBits);
	m_objectBody->SetUserData(this);
}
//-----------------------------------------------------------------------------
void MineTrap::draw(sf::RenderWindow& window)
{
	if (m_mineAnimation.getFrameByClock()) {
		m_mineAnimation.update(toVector());
	}
	else {
		m_mineAnimation.setCurrentFrame(0);
		m_mineAnimation.setRect();
	}
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void MineTrap::handleCollide()
{
	m_mineAnimation.setFrameByClock(true);
	m_mineAnimation.setRenderTimeByClock(0.12f);
}
//-----------------------------------------------------------------------------

