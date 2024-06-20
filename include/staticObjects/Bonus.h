#pragma once
#include "StaticObjectAnimation.h"
class Bonus :public StaticObjectAnimation
{
public:
	 Bonus(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~Bonus() {};

     
private:
};
