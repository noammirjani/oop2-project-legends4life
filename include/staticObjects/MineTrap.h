#pragma once
#include "StaticObjectAnimation.h"
class MineTrap :public StaticObject
{
public:
	MineTrap(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~MineTrap() {}


	void draw(sf::RenderWindow&) override;

	void handleCollide();

	bool endCollide() const { return m_mineAnimation.getFrameByClock(); }

private:
	Animation m_mineAnimation;
	static bool m_registerit;
};
