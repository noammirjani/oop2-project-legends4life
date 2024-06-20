 #pragma once
#include "Trap.h"


//falling block - trap
class FallingBlock :public Trap
{
public:
	FallingBlock(std::unique_ptr<b2World>&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	~FallingBlock() {}

	void draw(sf::RenderWindow&) override;
	void move( )                 override;
	void updatePhysically    ()  override;
	void resetToFirstPosition()  override;
private:
	static bool m_registerit;
};
