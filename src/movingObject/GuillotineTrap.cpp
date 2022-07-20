#include "MovingObject/GuillotineTrap.h" 
#include <iostream>

//-----------------------------------------------------------------------------
bool GuillotineTrap::m_registerit = Factory<MovingObject>::registerit("GuillotineTrap",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<MovingObject> { return std::make_unique<GuillotineTrap>(world, b2_dynamicBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
GuillotineTrap::GuillotineTrap(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: Trap(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, bodyOffset)
{
	b2MassData  * newMass = new b2MassData();

	newMass->mass = 15000;
	m_objectBody->SetMassData(newMass);
	resetToFirstPosition();
}
//-----------------------------------------------------------------------------
void GuillotineTrap::draw(sf::RenderWindow& window)
{
	if (m_animation.getFrameByClock() && m_time.getElapsedTime().asSeconds() >= 4.f) {
		m_animation.update();
	}
	
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void GuillotineTrap::move()
{

	 if (getIfCollide() && m_time.getElapsedTime().asSeconds() >= 4.f) {
	m_objectBody->SetTransform(b2Vec2(m_startPosition.x, m_startPosition.y), 0);
	m_objectBody->SetAwake(false);
	m_animation.setFrameByClock(true);
	m_animation.setRenderTimeByClock(0.12f);
	setCollide(false);
	}

	else if (m_time.getElapsedTime().asSeconds() >= 4.f) {
	updatePhysically();
    }

}
//-----------------------------------------------------------------------------
void GuillotineTrap::updatePhysically()
{
	m_objectBody->SetLinearVelocity(b2Vec2(0, 28));
}
//-----------------------------------------------------------------------------
void GuillotineTrap::resetToFirstPosition()
{
    m_animation.setFrameByClock(false);
	m_animation.setCurrentFrame(0);
	m_animation.setRect();
	setCollide(true);
	m_time.restart();
}
