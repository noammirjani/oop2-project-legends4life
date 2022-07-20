#include "gameManage/Animation.h"
#include <iostream>


//-----------------------------------------------------------------------------
Animation::Animation(const sf::Vector2f& sizeFrame, const sf::Vector2f& frameLimit, sf::Sprite& sprite)
	: m_sprite(sprite), m_sizeFrame(sizeFrame), m_frameLimit(frameLimit), m_currentFrame({0, 0})
{}

//-----------------------------------------------------------------------------
void Animation::update(const directionData& dirData)
{
	if (m_frameByClock)
		setFrameDataByClock();
	else 
	{
		if (dirData.first == Direction::None) return;

		setFrameDataByKeyboard(int(dirData.first));
	}
	setRect();			
}


//-----------------------------------------------------------------------------
void Animation::setFrameDataByClock()
{
	if (m_currentFrame.x == m_frameLimit.y)
	{
		setFrameByClock(false);
		return;
	}
	if (m_timer.getElapsedTime().asSeconds() >= m_renderByClock)
	{
		++m_currentFrame.x;
		m_timer.restart();
	}
}


//-----------------------------------------------------------------------------
void Animation::setRect()
{
	m_sprite.setTextureRect({m_currentFrame.x * m_sizeFrame.x, m_currentFrame.y * m_sizeFrame.y, m_sizeFrame.x, m_sizeFrame.y});
}

//-----------------------------------------------------------------------------
void Animation::setImageFlip(const bool cond , const float scale)
{
	if (getIfImageFlip() == cond) return;
	
	if (cond) {
		m_sprite.setScale(sf::Vector2f(-scale, scale));
	}
	else
		m_sprite.setScale(sf::Vector2f(scale, scale));

	m_imageFlip = cond;
}


//-----------------------------------------------------------------------------
void Animation::setFrameDataByKeyboard(const int direction)
{
	if (m_frameLimit.y == 0) { throw std::invalid_argument("divide in zero! check the animation trct function!"); }
	
	
	if (m_timer.getElapsedTime().asSeconds() >= 0.08f)
	{
		++m_currentFrame.x;
		m_currentFrame  .x %= m_frameLimit.y;
		m_timer.restart();
	}
	m_currentFrame.y = direction;
}

void Animation::setSprite(sf::Sprite& sprite)
{
	m_sprite = sprite; 
}
