#include "StaticObjects/Ground.h"


//-----------------------------------------------------------------------------
Ground::Ground(std::unique_ptr<b2World>& world)
	:GameObject({ 0,0 })
{
	b2BodyDef bodyDef;

	bodyDef.type = b2_staticBody;// static or dinamic
	bodyDef.position.Set(200.f, 1200.f);
	bodyDef.allowSleep = true;
	bodyDef.awake = true;

	m_objectBody = world->CreateBody(&bodyDef);


	createBodyFixture(sf::Vector2f(4800.f, 1.f), 1.f, 1.f, GroundBits, playerBits);

	m_objectBody->SetUserData(this);
}