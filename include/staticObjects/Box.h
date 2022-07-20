#pragma once
#include "StaticObject.h"
class Box : public StaticObject
{
public:
	 Box(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~Box() {}

	void draw(sf::RenderWindow&) override;

	//void handleCollide();


private:
	static bool m_registerit;
};
