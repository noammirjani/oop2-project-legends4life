#pragma once
#include "Bonus.h"

class BonusLive :public Bonus
{
public:
	BonusLive(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~BonusLive() {};

private:
	static bool m_registerit;
};
