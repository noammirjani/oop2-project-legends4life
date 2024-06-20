#include "gameManage/GameObject.h"


//-----------------------------------------------------------------------------
GameObject::GameObject(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld, const int resourseIndex,
	const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& bodySize, const sf::Vector2f& bodyOffset)
	:m_sprite(Resources::getInstance().getIcon(resourseIndex),rect), m_bodyOffset(bodyOffset)
{
	setSprite(position);
	
	createBodyDefinition(world, typeOfObjectInWorld);
	
	m_objectBody->SetFixedRotation(true);
}

//-----------------------------------------------------------------------------
GameObject::GameObject(const int resourseIndex,const sf::IntRect& rect,const sf::Vector2f& bodyOffset)
	:m_sprite(Resources::getInstance().getIcon(resourseIndex), rect), m_bodyOffset(bodyOffset)
{}

//-----------------------------------------------------------------------------
void GameObject::setSprite(const sf::Vector2f& location)
{
	m_sprite.setPosition(location);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f , m_sprite.getGlobalBounds().height / 2.f);
}

//-----------------------------------------------------------------------------
void GameObject::setSprite(const int resourseIndex)
{
	m_sprite.setTexture(Resources::getInstance().getIcon(resourseIndex));
}

//-----------------------------------------------------------------------------
void GameObject::createBodyDefinition(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorld,const bool condbullet)
{
	b2BodyDef bodyDef;

	bodyDef.type = typeOfObjectInWorld;// static or dinamic
	bodyDef.position.Set(m_sprite.getPosition().x - m_bodyOffset.x, m_sprite.getPosition().y - m_bodyOffset.y);
    bodyDef.allowSleep = true;//When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep state which has very
	bodyDef.awake = true;     //little CPU overhead. If a body is awake and collides with a sleeping body, then the sleeping body wakes up.
	                          //Bodies will also wake up if a joint or contact attached to them is destroyed. You can also wake a body manually.
	bodyDef.bullet = condbullet;
	m_objectBody = world->CreateBody(&bodyDef);
}


//-----------------------------------------------------------------------------
void GameObject::createBodyFixture(const sf::Vector2f& bodySize,float density, float friction,uint16 categoryBits, uint16 maskBits)
{
	b2PolygonShape boxShape;
	b2FixtureDef boxFixtureDef;
	
	boxShape.SetAsBox(bodySize.x, bodySize.y);

	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = density;   // density - how heavy it is in relation to its area
	boxFixtureDef.friction = friction; //friction - how slippery it is
	boxFixtureDef.filter.categoryBits = categoryBits;
	boxFixtureDef.filter.maskBits = maskBits;
	m_objectBody->CreateFixture(&boxFixtureDef);
}
//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window) 
{
	convertPositionFromBox2dToSprite();
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
sf::Vector2f GameObject::getPos() const
{
	return m_sprite.getPosition();
}
//-----------------------------------------------------------------------------
void GameObject::convertPositionFromBox2dToSprite()
{
	m_sprite.setPosition(m_objectBody->GetPosition().x + m_bodyOffset.x, m_objectBody->GetPosition().y + m_bodyOffset.y);
}
