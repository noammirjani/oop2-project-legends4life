#pragma once
#include "gameManage/GameObject.h"


class StaticObject : public GameObject
{
public:
	//c-tor, d-tor
	StaticObject(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~StaticObject() {}
	//  FUNCTIONS


private:

	//PRIVATE - FUNCTIONS

};