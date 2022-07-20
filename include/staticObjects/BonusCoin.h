#pragma once
#include "Bonus.h"

class BonusCoin :public Bonus
{
public:
	  BonusCoin(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	 ~BonusCoin() {};

private:
	static bool m_registerit;
};
