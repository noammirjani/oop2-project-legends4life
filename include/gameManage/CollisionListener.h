#pragma once
#include "box2d/box2d.h"
#include "CollisionHandler.h"
#include "GameObject.h"


//  Collision Listener inhertor from bix2d class 
class CollisionListener:public b2ContactListener
{
public:
	 CollisionListener () {};
	~CollisionListener()  {};

	void BeginContact(b2Contact* ) override;
	void EndContact  (b2Contact* ) override;
private:
	void checkPlayerEndContactWithEnemy(b2Contact* );
};
