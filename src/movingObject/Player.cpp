#include "MovingObject/Player.h"
#include <iostream>

//------------------------- CONSTRUCTOR ------------------------------------
Player::Player(std::unique_ptr<b2World>& world, CheckPoint&& checkPointPosition,  enum b2BodyType typeOfObjectInWorldconst, int resourseIndex, const sf::Vector2f& position,
			   const sf::IntRect& rect, const sf::Vector2f& frameLimit, const sf::Vector2f& bodySize, const sf::Vector2f& offsetBody)
	: MovingObject(world, typeOfObjectInWorldconst,resourseIndex, position, rect, frameLimit, bodySize, offsetBody), m_lifeBar({ 809,1,2,10 }, m_injury, bodySize.y),
	m_checkPointPosition(std::move(checkPointPosition)), m_ground(world), m_magicEffect({-15,-10})
{
	  
	m_animation.setRenderTimeByClock(0.08f);
	createBodyFixture(bodySize, 1.f, 1.f, playerBits, playerBits | PaltformBits | TrapsBits  | BonusBits | WaterBits | BoxBits | GroundBits | EnemyBits);
	m_sprite.setScale(1.2f, 1.2f);

	m_objectBody->SetUserData(this);
	setAvatarSprite(10); 
}

//----------------------------------------------------------------
void Player::initAttackWithNewEnemy(Enemy* newEnemy)
{
	m_enemy = newEnemy;
	setCollideWithEnemy(true);
}


//----------------------------------------------------------------
void Player::setAvatarSprite(const int indexIcon)
{
	m_avatarSprite.setTexture(Resources::getInstance().getIcon(10));
	m_avatarSprite.setTextureRect({ ((indexIcon - 1) * 66) + 1, 1, 64,64 });
	m_avatarSprite.setScale(1.8f, 1.5f);
}


//---------------------------------------------------------------
void Player::update(std::unique_ptr<b2World>& world)
{
	if(m_newMagicEffect){
		m_magicEffect.initNewMagicEffect(world, { m_objectBody->GetPosition().x,m_objectBody->GetPosition().y }, m_animation.getIfImageFlip());
		m_newMagicEffect = false;
	}
	m_magicEffect.update(world);

	if (m_energy < 100) updateEnergy();
	m_avatarSprite.setPosition(m_sprite.getPosition() + sf::Vector2f(0, -50));

	checkAttackEnemy();
}


//-----------------------------------------------------------------------------
void Player::checkAttackEnemy()
{
	if (!m_collideEnemy) return;
	if (m_attack) 
	{
		m_enemy->manageDisqualified();
		m_attack = false;
	}
}


//---------------------------------------------------------------
void Player::drawAvatar(sf::RenderWindow& window)
{
	window.draw(m_avatarSprite);
}



//-----------------------------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
	if (getPlyaerAttack() && !m_animation.getFrameByClock() ) {
		m_attack = false;
	}

    if (getIfCollide()) {
		if (!m_animation.getFrameByClock()) {
			auto checkPosition = m_checkPointPosition.currCheckPointPosition(m_sprite.getPosition());
			m_objectBody->SetTransform( b2Vec2(checkPosition.x - m_bodyOffset.x, checkPosition.y - m_bodyOffset.y), 0);
			setCollide(false);
			m_injury = 3;
		}
	}
	 if (m_animation.getFrameByClock()) m_animation.update();

	convertPositionFromBox2dToSprite();
	
	m_magicEffect.draw(window);
	m_lifeBar.draw(window, m_sprite.getPosition(), m_injury);
	window.draw(m_sprite);
}


//-----------------------------------------------------------------------------
void Player::move()
{
	m_magicEffect.move();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		manageAttack();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		magicEffectAttack();
		return;
	}

	if (toVector().first == Direction::None) return;

	float velX = 0.f;
	auto shift = toVector().second;
	m_animation.update(toVector());
	auto pos = m_objectBody->GetLinearVelocity();

	if (shift.x > 0) {
		velX = b2Max(pos.x - 0.1f, shift.x + (m_bonusSpeed)) - pos.x;
		m_animation.setImageFlip(false, 1.2f);
	}
	else if (shift.x < 0) {
		velX = b2Min(pos.x + 0.1f, shift.x + (m_bonusSpeed)) - pos.x;
		m_animation.setImageFlip(true, 1.2f);
	}
	if (shift.y != 0) {
		jump(shift.y);
	}

	float impulse = (m_objectBody->GetMass() * (velX));
	m_objectBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_objectBody->GetWorldCenter(), true);

}


//-----------------------------------------------------------------------------
void Player::manageAttack() 
{
	if (!m_animation.getFrameByClock()) 
	{
		m_animation.setRenderTimeByClock(0.06f);
		specialAnimation(1);
	    m_attack = true;
		Audio::getInstance().playSoundEffect(ATTACK);
	}
}


//-----------------------------------------------------------------------------
void Player::magicEffectAttack()
{
	if (m_energy < 100) return; 

	m_newMagicEffect = true;
	m_energy = -1; 
}


//-----------------------------------------------------------------------------
void Player::manageDisqualified()
{
	Audio::getInstance().playSoundEffect(PLAYERDIE);
	m_animation.setRenderTimeByClock(0.12f);
	specialAnimation(2);
	setCollide(true);
	--m_lifes;
}


//-----------------------------------------------------------------------------
void Player::jump(const float y)
{
	if (getPlyaerJump()) return;

	m_animation.setRenderTimeByClock(0.08f);
	
	specialAnimation(4);

	setPlayerJump(true);

	float impulse = 0;
	auto pos = m_objectBody->GetLinearVelocity();
	if (y > 0)
		impulse = -m_objectBody->GetMass() * y;
	else
		impulse = (m_objectBody->GetMass() * 7.f) ;
	m_objectBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_objectBody->GetWorldCenter(), true);
	Audio::getInstance().playSoundEffect(JUMPSOUND);
}


//-----------------------------------------------------------------------------
void Player::updateEnergy()
{
	static sf::Clock clock; 

	if (m_energy == -1)
	{	//first entery after each attack
		clock.restart();
		m_energy = 0; 
	}
	
	if (clock.getElapsedTime() > sf::seconds(0.5))
	{
		m_energy += 10; 
		clock.restart(); 
	}

	if (m_energy > 100) m_energy = 100; 
}


//-----------------------------------------------------------------------------
void Player::updateMagicEffect()
{
	m_magicEffect.updateRowAnimationEffect();
}
