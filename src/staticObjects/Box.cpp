#include "StaticObjects/Box.h"
//-----------------------------------------------------------------------------
bool Box::m_registerit = Factory<StaticObject>::registerit("Box",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<StaticObject> { return std::make_unique<Box>(world, b2_dynamicBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });

//-----------------------------------------------------------------------------
Box::Box(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: StaticObject(world, typeOfObjectInWorld, resourseIndex, position, rect, bodySize, offsetBody)
{
	
	createBodyFixture(bodySize, 1.f, 1.f, BoxBits, BoxBits| PaltformBits| playerBits | MagicEffectBits | EnemyBits);
	m_objectBody->SetUserData     (this);
	m_objectBody->SetFixedRotation(false);
	m_sprite.setScale(1.4f, 1.4f);
	
}
//-----------------------------------------------------------------------------
void Box::draw(sf::RenderWindow& window)
{
	auto rotation = (m_objectBody->GetAngle() * 180) / b2_pi; 
	m_sprite.setRotation(rotation );
	convertPositionFromBox2dToSprite();
	window.draw         (m_sprite );
}