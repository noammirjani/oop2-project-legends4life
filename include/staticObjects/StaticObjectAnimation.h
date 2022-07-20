#pragma once
#include "StaticObject.h"
#include "StaticAnimation.h"

class StaticObjectAnimation : public StaticObject
{
public:
	//c-tor, d-tor
	StaticObjectAnimation(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~StaticObjectAnimation() {}

	//				          Mangemanet functions
	//---------------------------------------------------------------
    void draw(sf::RenderWindow&) override;
    void updateDisposeAnimation(sf::RenderWindow& );
	void setDisposeAnimation() { m_disposeAnimation = true; m_time.restart(); }
	void destroyBody(std::unique_ptr<b2World>& world) override;
	bool getIsSpriteDisposed() const { return m_isDisposed && m_disposeAnimation && m_time.getElapsedTime().asSeconds() >= 1.5f; }
	
	//  FUNCTIONS
protected:
	StaticAnimation m_animation;

private:
	sf::Clock m_time;
	bool m_disposeAnimation = false;
	//PRIVATE - FUNCTIONS

};