#pragma once
#include "StaticObjectAnimation.h"
class WinGate :public StaticObject
{
public:
	WinGate(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~WinGate() {}

	void draw(sf::RenderWindow&) override;

	void handleCollide();


private:
	Animation m_gateAnimation;
	static bool m_registerit;
};
