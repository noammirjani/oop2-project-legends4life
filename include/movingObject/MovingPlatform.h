#pragma once
#include "MovingObject.h"


// moving platfrom -> trap
class MovingPlatform :public MovingObject
{
public:
	MovingPlatform(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~MovingPlatform() {}


	void move()                  override;

	float updatePhysically();

private:
	bool m_changeDirection = false;
	sf::Vector2f m_startPosition;
	float m_offset = 100.f;
	float m_speed;
	sf::Clock    m_time;
	static bool  m_registerit;
};
