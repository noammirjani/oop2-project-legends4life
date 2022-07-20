#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Resources.h"
#include "Macros.h"
#include "Factory.h"
#include "box2d/box2d.h"
#include "Audio.h"

// GAME OBJECT - main inhirints calss for all the kinds of objects in the game 
class GameObject
{
public:
	//---------------------------------------------------------------	
	// 			Constructors & Destructors
    //--------------------------------------------------------------- 
	GameObject(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&);
	GameObject(const sf::Vector2f& bodyOffset) :m_bodyOffset(bodyOffset) {}
	GameObject(const int, const sf::IntRect&, const sf::Vector2f& bodyOffset);
	virtual ~GameObject() {}

	//---------------------------------------------------------------
	//				      virtual functions
	//---------------------------------------------------------------
	virtual void draw(sf::RenderWindow&) ;


	//---------------------------------------------------------------	
    //							 Get functions
    //---------------------------------------------------------------
	        bool getIsBodyDisposed   () const {return m_isDisposed; }
	virtual bool getIsSpriteDisposed () const {return getIsBodyDisposed(); }
	virtual void destroyBody(std::unique_ptr<b2World>& world) { world->DestroyBody(m_objectBody);}
	bool getIfCollide  () const { return m_collide;   }
	sf::Vector2f getPos()const; 


	//---------------------------------------------------------------	
	//							 Set functions
	//---------------------------------------------------------------
	void setIsDisposed(const bool cond) { m_isDisposed = cond; }
	void setCollide   (const bool cond) { m_collide = cond; }

	void convertPositionFromBox2dToSprite();



protected:
	sf::Sprite   m_sprite;
	b2Body*      m_objectBody;
	sf::Vector2f m_bodyOffset;

	bool m_isDisposed = false;
	void           createBodyDefinition(std::unique_ptr<b2World>&, b2BodyType,const bool condbullet = false);
	void           createBodyFixture(const sf::Vector2f& , float , float , uint16 , uint16 );

private:
	bool m_collide    = false;

	//PRIVATE - FUNCTIONS
	void setSprite   (const sf::Vector2f&);
	void setSprite   (const int);
};