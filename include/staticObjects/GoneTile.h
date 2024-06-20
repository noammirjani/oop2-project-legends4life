#pragma once

#include "gameManage/Animation.h"
#include "StaticObjects/Platform.h"
class GoneTile : public Platform
{
public:
	//c-tor, d-tor
	 GoneTile(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~GoneTile() {}
	
	void draw(sf::RenderWindow&) override;
	void handleCollide   ();
	void updatePhysically();


private:
	Animation m_animation;
	sf::Clock m_goneTimer;
	bool m_sensor = false;
	static bool m_registerit;

};