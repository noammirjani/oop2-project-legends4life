#include "StaticObjects/GoneTile.h"
#include <iostream>

//-----------------------------------------------------------------------------
bool GoneTile::m_registerit = Factory<StaticObject>::registerit("GoneTile",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<GoneTile>(world, b2_staticBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
GoneTile::GoneTile(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: Platform(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, bodyOffset), m_animation(sf::Vector2f(rect.width, rect.height), frameLimit, m_sprite)
{
	m_animation.setCurrentFrame(0);
	m_animation.setRect();
}
//-----------------------------------------------------------------------------
void GoneTile::draw(sf::RenderWindow& window)
{	
	updatePhysically();
	if (m_animation.getFrameByClock()) {
		m_animation.update(toVector());
	}
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void GoneTile::handleCollide()
{
	
	m_animation.setFrameByClock     (true);
	m_animation.setRenderTimeByClock(0.4f);
}
//-----------------------------------------------------------------------------
void GoneTile::updatePhysically()
{

	if (m_animation.getCurrentFrame().x == 3 && m_animation.getFrameByClock()) {
		m_animation.setFrameByClock(false);
		m_animation.setCurrentFrame(3);
		m_animation.setRect();
		m_goneTimer.restart();
		m_sensor = false;
		m_objectBody->SetEnabled(m_sensor);
		return;
	}
	else if (!m_sensor && m_goneTimer.getElapsedTime().asSeconds() > 2.5f) {
		m_animation.setCurrentFrame(0);
		m_animation.setRect();
		m_sensor = true;
		m_objectBody->SetEnabled(m_sensor);
	}
}
//-----------------------------------------------------------------------------

