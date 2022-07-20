#include "MovingObject/Enemy.h"
#include <iostream>

//-----------------------------------------------------------------------------
bool Enemy::m_registerit = Factory<MovingObject>::registerit("Enemy",
	[](std::unique_ptr<b2World>& world, const int resourseIndex, const sf::Vector2f& position, const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody) ->
	std::unique_ptr<MovingObject> { return std::make_unique<Enemy>(world, b2_dynamicBody, resourseIndex, position, rect, frameLimit, bodySize, offsetBody); });


//-----------------------------------------------------------------------------
Enemy::Enemy(std::unique_ptr<b2World>& world, enum b2BodyType typeOfObjectInWorldconst, int resourseIndex, const sf::Vector2f& position,
	const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: MovingObject(world, typeOfObjectInWorldconst, resourseIndex, position, rect, frameLimit, bodySize, offsetBody), m_lifeBar({ 508,1,1,10 }, m_life, bodySize.y),
	m_startPosition(sf::Vector2f(position.x - offsetBody.x, position.y - offsetBody.y)),m_life(3), m_offset(frameLimit.x)
{
	m_animation.setRenderTimeByClock(0.09f);
	createBodyFixture(bodySize, 1.f, 1.f, EnemyBits,  PaltformBits | playerBits| BoxBits |MagicEffectBits);
	m_objectBody->SetUserData(this);
}


//-----------------------------------------------------------------------------
void Enemy::update(std::unique_ptr<b2World>& world)
{
	if (!getIsBodyDisposed() || m_animation.getFrameByClock()) return;

	destroyBody(world);

}


//-----------------------------------------------------------------------------
void Enemy::draw(sf::RenderWindow& window)
{
	if (!m_animation.getFrameByClock() && !m_isDisposed) {
		specialAnimation(0);
	} 

	if (m_animation.getCurrentFrame().y != ATTACK_FRAME ) { 
		m_attack = false;
	}

	m_animation.update();
	convertPositionFromBox2dToSprite();
	m_lifeBar.draw(window, m_sprite.getPosition(), m_life);
	window.draw(m_sprite);
}


//-----------------------------------------------------------------------------
void Enemy::move()
{
	auto pos = m_objectBody->GetLinearVelocity();
	auto offset = updatePhysically();
	if (offset > 0) 
	{
		m_objectBody->SetLinearVelocity({ offset, pos.y });
	}
	else if (offset < 0) 
	{
		m_objectBody->SetLinearVelocity({ offset,  pos.y });
	}

}


//-----------------------------------------------------------------------------
void Enemy::manageAttack()
{
	m_attack = true;
	m_animation.setRenderTimeByClock(0.10f);
	specialAnimation(1);
}


//-----------------------------------------------------------------------------
void Enemy::manageDisqualified()
{
	--m_life;
	if (m_life == 0) 
	{
		Audio::getInstance().playSoundEffect(ENEMYDIE);
		m_animation.setRenderTimeByClock(0.15f);
		specialAnimation(2);
		setIsDisposed(true);
		m_animation.setRect();
	}
}


//-----------------------------------------------------------------------------
float Enemy::updatePhysically()
{
	auto currPos = m_sprite.getPosition().x;

	if (currPos > m_startPosition.x + m_offset) {// go Left
		m_changeDirection = true;
		m_animation.setImageFlip(true,1.f);
	} 

	else if (currPos < m_startPosition.x - m_offset) { // go Right
		m_changeDirection = false;
		m_animation.setImageFlip(false, 1.f);
	}

	if (m_changeDirection)
		return -10.f;

	return  10.f;
}