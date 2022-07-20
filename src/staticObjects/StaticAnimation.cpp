#include "StaticObjects/StaticAnimation.h"
#include <iostream>

//-----------------------------------------------------------------------------
StaticAnimation::StaticAnimation(const sf::Vector2f& sizeFrame, const sf::Vector2f& frameLimit, sf::Sprite& sprite)
	: Animation(sizeFrame, frameLimit, sprite)
{
    m_timer.restart();
}


//-----------------------------------------------------------------------------
void StaticAnimation::update(const directionData&)
{
  if (m_timer.getElapsedTime().asSeconds() >= AnimationTime)
    {
        setFrameDataByClock();
        setRect();
        m_timer.restart();
   }
}
//-----------------------------------------------------------------------------
void StaticAnimation::setFrameDataByClock()
{
    ++m_currentFrame.x;
    m_currentFrame.x %= m_frameLimit.y;
    m_currentFrame.y = m_frameLimit.x;
}
