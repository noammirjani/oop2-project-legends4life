#pragma once
#include "Bonus.h"
const int speed = 2;

class BonusSpeed :public Bonus
{
public:
   	BonusSpeed(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~BonusSpeed() {};

	int getBounsSpeed() const { return speed; }
private:
	static bool m_registerit;
};
