#include "movingObject/MagicEffect.h"
#include <iostream>

//---------------------------------------------------------------
MagicEffect::MagicEffect(const sf::Vector2f& bodyOffset)
	:GameObject(8,{ 0,14,128,128 }, bodyOffset), m_animation({ 128, 133 }, { 0,6 }, m_sprite)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
	m_animation.setFrameByClock(0.10f);
}
//---------------------------------------------------------------
void MagicEffect::initNewMagicEffect(std::unique_ptr<b2World>& world, const sf::Vector2f& pos,const bool flipImage)
{
	if (m_shotMagicEffect) return;

	m_shotTime.restart();
	Audio::getInstance().playSoundEffect(MAGICATTAK);
	if (flipImage && m_animation.getIfImageFlip() != flipImage) {
		m_bodyOffset.x += 30;
	}
	if (!flipImage && m_animation.getIfImageFlip() != flipImage) {
		m_bodyOffset.x += -30;
	}

	m_animation.setImageFlip(flipImage, 1.f);
	m_animation.setRowAnimation(m_rowAnimationEffect);
	m_animation.setFrameByClock(true);
	m_animation.setRect();

	m_sprite.setPosition(pos.x + m_bodyOffset.x, pos.y + m_bodyOffset.y);
	m_shotMagicEffect = true;

	createBodyDefinition(world, b2_dynamicBody, true);
	createBodyFixture({ 2.f,10.f }, 1.f, 1.f, MagicEffectBits, (EnemyBits | PaltformBits | BoxBits |TrapsBits));

	m_objectBody->SetUserData (this);
	m_objectBody->SetGravityScale(0);

}
//-----------------------------------------------------------------------------
void MagicEffect::collisionMagicEffect()
{
	m_animation.setFrameByClock(true);
	
	m_animation.setRowAnimation(m_rowAnimationEffect + 1);
	
	setIsDisposed(true);

	m_animation.setRect();
}
//-----------------------------------------------------------------------------
void MagicEffect::updatePhysically()
{
	if (m_animation.getIfImageFlip()) 
		m_objectBody->SetLinearVelocity(b2Vec2(-27, 0));
	else 
		m_objectBody->SetLinearVelocity(b2Vec2(27, 0));
		
	convertPositionFromBox2dToSprite();
}
//-----------------------------------------------------------------------------
void MagicEffect::updateRowAnimationEffect()
{
	m_rowAnimationEffect += 2;
	m_rowAnimationEffect %= 6;
}
//-----------------------------------------------------------------------------
void MagicEffect::move()
{
	if (!m_shotMagicEffect) return;


	if (m_shotTime.getElapsedTime().asSeconds() >= 4.5f) {
		collisionMagicEffect();
		m_shotTime.restart();
	}

	updatePhysically();

	if (m_animation.getFrameByClock())
		m_animation.update();
	else {
		m_animation.setCurrentFrame(6);
		m_animation.setRect();
	}
}
//-----------------------------------------------------------------------------
void MagicEffect::draw(sf::RenderWindow& window)
{

	if (!m_shotMagicEffect) return;

	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void MagicEffect::update(std::unique_ptr<b2World>& world)
{

	if (!getIsBodyDisposed() || m_animation.getFrameByClock()) return;

	destroyBody  (world);

	setIsDisposed(false);
}
//-----------------------------------------------------------------------------
void MagicEffect::destroyBody(std::unique_ptr<b2World>& world)
{
	m_shotMagicEffect = false;
	world->DestroyBody(m_objectBody);
}