#include "StaticObjects/StaticObjectAnimation.h"


//-----------------------------------------------------------------------------
StaticObjectAnimation::StaticObjectAnimation(std::unique_ptr<b2World>& world,enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
											 const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: StaticObject(world, typeOfObjectInWorld, resourseIndex, position, rect, bodySize, offsetBody), m_animation(sf::Vector2f(rect.width, rect.height), frameLimit, m_sprite)
{}
//-----------------------------------------------------------------------------
void StaticObjectAnimation::draw(sf::RenderWindow& window)
{
	if (m_disposeAnimation)
	{
		updateDisposeAnimation(window);
		return;
	}
	m_animation.update(toVector());
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//---------------------------------------------------------------
void StaticObjectAnimation::updateDisposeAnimation(sf::RenderWindow& window)
{
	m_sprite.setColor({ 245,237,87,170 });
	auto pervPos = m_sprite.getPosition();
	pervPos.x -= 0.2f;
	pervPos.y -= 0.2f;
	m_animation.update(toVector());
	m_sprite.setPosition(pervPos.x, pervPos.y );
	window.draw(m_sprite);
}
//---------------------------------------------------------------------
void StaticObjectAnimation::destroyBody(std::unique_ptr<b2World>& world)
{
	if (m_isDisposed && !m_disposeAnimation)
	{
		world->DestroyBody(m_objectBody);
		setDisposeAnimation();

	}

}
