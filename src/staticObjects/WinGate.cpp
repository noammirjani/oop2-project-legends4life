#include "StaticObjects/WinGate.h"
#include <iostream>

//-----------------------------------------------------------------------------
bool WinGate::m_registerit = Factory<StaticObject>::registerit("WinGate",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<WinGate>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
WinGate::WinGate(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: StaticObject(world, typeOfObjectInWorld, resourseIndex, position, rect, bodySize, bodyOffset), m_gateAnimation(sf::Vector2f(rect.width, rect.height), frameLimit, m_sprite)
{
	createBodyFixture(bodySize, 1.f, 1.f, WaterBits, playerBits);
	m_objectBody->SetUserData(this);
}
//-----------------------------------------------------------------------------
void WinGate::draw(sf::RenderWindow& window)
{
	if (m_gateAnimation.getFrameByClock()) {
		m_gateAnimation.update(toVector());
	}
	else {
		m_gateAnimation.setCurrentFrame(0);
		m_gateAnimation.setRect();
	}
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void WinGate::handleCollide()
{
	m_gateAnimation.setFrameByClock(true);
	m_gateAnimation.setRenderTimeByClock(0.2f);
}
//-----------------------------------------------------------------------------

