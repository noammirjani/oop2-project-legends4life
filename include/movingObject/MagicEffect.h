#pragma once
#include "gameManage/Animation.h"
#include "gameManage/GameObject.h"

//magic effect -> player's attack
class MagicEffect: public GameObject
{
public:
	//					Constructors & Destructors
	//--------------------------------------------------------------- 
	MagicEffect(const sf::Vector2f &);
	virtual ~MagicEffect() {}


	void initNewMagicEffect(std::unique_ptr<b2World>&, const sf::Vector2f &, const bool);
	//				      virtual functions
	//---------------------------------------------------------------
	void draw(sf::RenderWindow&);
	void move();
	void update(std::unique_ptr<b2World>&);

	void destroyBody(std::unique_ptr<b2World>& world);

	void collisionMagicEffect();
	void updatePhysically    ();
	void updateRowAnimationEffect();

	//							 Get functions
	//---------------------------------------------------------------
	int getType() const { return m_rowAnimationEffect; }

private:
	bool m_shotMagicEffect = false;
	unsigned int m_rowAnimationEffect = 0;
	sf::Clock m_shotTime;
	Animation  m_animation;
};