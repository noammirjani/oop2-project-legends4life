#pragma once
#include "MovingObject.h"


//trap base class
class Trap : public MovingObject
{
public:
	//					Constructors & Destructors
	//--------------------------------------------------------------- 
	Trap(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~Trap() {}

	void draw() {};
	void move() {};

	//				      virtual functions
	//---------------------------------------------------------------
	virtual void updatePhysically() {};

	virtual void resetToFirstPosition() = 0;

	bool getEndCollison() const { return m_animation.getFrameByClock(); }
protected:
	sf::Clock    m_time;
	sf::Vector2f m_startPosition;
private:

};
