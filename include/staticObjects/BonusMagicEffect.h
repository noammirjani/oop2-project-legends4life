#pragma once
#include "Bonus.h"

class BonusMagicEffect :public Bonus
{
public:
	BonusMagicEffect(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~BonusMagicEffect() {};

private:
	static bool m_registerit;
};
