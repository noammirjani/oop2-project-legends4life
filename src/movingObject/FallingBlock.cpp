#include "MovingObject/FallingBlock.h"
#include <iostream>

//-----------------------------------------------------------------------------
bool FallingBlock::m_registerit = Factory<MovingObject>::registerit("FallingBlock",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<MovingObject> { return std::make_unique<FallingBlock>(world, b2_dynamicBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
FallingBlock::FallingBlock(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	: Trap(world, typeOfObjectInWorld, resourseIndex, position, rect, frameLimit, bodySize, bodyOffset)
{

}
//-----------------------------------------------------------------------------
void FallingBlock::draw(sf::RenderWindow& window)
{
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void FallingBlock::move()
{
	if (m_animation.getFrameByClock()) {
		m_animation.update();
	}
	else if (getIfCollide() && m_time.getElapsedTime().asSeconds() >= 0.3f) {
		m_objectBody->SetTransform(b2Vec2(m_startPosition.x, m_startPosition.y), 0);
		m_objectBody->SetAwake(false);
		setCollide(false);
		m_animation.setCurrentFrame(0);
		m_animation.setRect();
	}
	else if (m_time.getElapsedTime().asSeconds() >= 3.5f)
	{
		m_animation.setCurrentFrame(1);
		updatePhysically();
		m_animation.setRect();
	}
}
//-----------------------------------------------------------------------------
void FallingBlock::updatePhysically()
{ 
	m_objectBody->SetLinearVelocity(b2Vec2(0, 15));
}
//-----------------------------------------------------------------------------
void FallingBlock::resetToFirstPosition()
{ 
	m_animation.setFrameByClock (true);
	m_animation.setRenderTimeByClock(0.12f);
	setCollide(true);
	m_time     .restart();
}
