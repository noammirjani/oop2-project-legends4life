#pragma once
#include "gameManage/Animation.h"

const directionData NONEMOVE = { Direction::None, {0,0} };
const auto AnimationTime = 0.1f;

class StaticAnimation : public Animation
{
public:
	StaticAnimation(const sf::Vector2f& , const sf::Vector2f&, sf::Sprite&);
	~StaticAnimation() {}

	void update(const directionData& = NONEMOVE) override;
	void setFrameDataByClock() override;

private:
	 sf::Clock m_timer;
};