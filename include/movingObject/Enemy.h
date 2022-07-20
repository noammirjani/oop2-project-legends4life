#pragma once
#include "MovingObject.h"
#include "gui/LifeStatusBar.h"

const float Offset = 150.f;
const int ATTACK_FRAME = 1;

//--------------------------- Class Section --------------------------
class Enemy : public MovingObject
{
public:
	//					Constructors & Destructors
	//--------------------------------------------------------------- 
	Enemy(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~Enemy() {}

	//				      virtual functions
	//---------------------------------------------------------------
	void draw  (sf::RenderWindow&)         override;
	void update(std::unique_ptr<b2World>&) override;
	void move              ()              override;
	void manageAttack      ();
	void manageDisqualified();
	void setAttack         (const bool cond) { m_attack = cond; }

	//							 Get functions
	//---------------------------------------------------------------
	float updatePhysically() ;
	bool  getAttack       () const { return m_attack; }



private:
	bool m_changeDirection = false;
	bool m_attack = false;
	
	int m_life;
	sf::Vector2f m_startPosition;
	static bool m_registerit;
	float m_offset;
	LifeStatusBar m_lifeBar;
};