#pragma once
#include "StaticObject.h"

class Platform : public StaticObject
{
public:
	//c-tor, d-tor
	Platform(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~Platform() {}

private:
	static bool m_registerit;

};