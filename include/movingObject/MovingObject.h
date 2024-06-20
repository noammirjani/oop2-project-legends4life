#pragma once
#include "gameManage/GameObject.h"
#include "gameManage/Animation.h"


// moving object -> game oject
class MovingObject : public GameObject
{
public:
	//					Constructors & Destructors
	//---------------------------------------------------------------
	MovingObject(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f& );
	virtual ~MovingObject   () {}
	

	//				      virtual functions
	//---------------------------------------------------------------
	virtual void update (std::unique_ptr<b2World>&) {};
	virtual void move   () = 0;

	//							 Set functions
	//---------------------------------------------------------------

	void specialAnimation(const int);

	//							 Get functions
    //---------------------------------------------------------------
	bool         getSideOfMovebleObject    () const {  return m_animation.getIfImageFlip(); }
	bool         getEndOfClockAnimation    () const {  return m_animation.getFrameByClock();}
	sf::Vector2f getPositionOfMovebleObject() const {  return m_sprite.getPosition();       }
	bool getIsSpriteDisposed()                const { return m_isDisposed && !m_animation.getFrameByClock(); } 


protected:
	Animation m_animation;
private:
};