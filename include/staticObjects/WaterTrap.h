#pragma once
#include "StaticObjectAnimation.h"
class WaterTrap :public StaticObjectAnimation
{
public:
	WaterTrap(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~WaterTrap() {};

private:
	static bool m_registerit;
};
