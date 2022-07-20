#pragma once
#include "gameManage/GameObject.h"
#include "box2d/box2d.h"

class Ground : public GameObject
{
public:
	//c-tor, d-tor
	Ground(std::unique_ptr<b2World>&);
	virtual ~Ground() {}

private:

};