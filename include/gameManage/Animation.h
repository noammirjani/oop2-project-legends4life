#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"


//ANIMATION, for moving and static objects
class Animation
{
public:
	Animation(const sf::Vector2f& , const sf::Vector2f&, sf::Sprite&);
	virtual ~Animation() {}
	
	//				      virtual functions
	//---------------------------------------------------------------
	virtual void update                 (const directionData & = {});
	        void setFrameDataByKeyboard (const int = 0);
			void setSprite(sf::Sprite&);
	virtual void setFrameDataByClock    ();

	//							 Set functions
	//---------------------------------------------------------------
	void setRect             ();
	void setCurrentFrame     (const int x) { m_currentFrame.x = x; }
	void setImageFlip        (const bool, const float);
	void setRenderTimeByClock(const float x)   { m_renderByClock = x; }
	void setRowAnimation     (const int row  ) { m_currentFrame.y = row;}
	void setFrameByClock     (const bool cond) {m_frameByClock = cond;
										        m_currentFrame.x = 0;}
	//							 Get functions
	//---------------------------------------------------------------
	bool getIfImageFlip () const        { return m_imageFlip;    }
	sf::Vector2i getCurrentFrame() const{ return m_currentFrame; }
	bool getFrameByClock() const        { return m_frameByClock; }
	sf::IntRect getRect()  const        { return m_sprite.getTextureRect(); }

protected:
	sf::Vector2u m_frameLimit  ; //x, hold the num of modes, y-hold the num of pics in each mode
	sf::Vector2i m_currentFrame; 

private:
	bool m_imageFlip    = false;
	bool m_frameByClock = false;
	float m_renderByClock = 0.06f;
	sf::Clock m_timer;
	sf::Sprite&  m_sprite;
	sf::Vector2i m_sizeFrame;
};