#pragma once
#include "HashHandler.h"
#include "GameObject.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <iostream>



//handle collision class - SINGLTONE CLASS 
class CollisionHandler
{
public:
	using collideFuncPtr = void (CollisionHandler::*)(GameObject*, GameObject*);
	using Key = std::pair<std::type_index, std::type_index>;
	using collideFunctionsMap = std::unordered_map<Key, collideFuncPtr, PairKeysHash, KeyEqual>;
	//the unordermap constructor gets - key(pair of two values), val to hash, hask function ans key compartion func. 

	//get to the data 
	static CollisionHandler& getInstance();

	//D-tor
	~CollisionHandler() {};

	//getFunctions
	void handleCollision(GameObject*, GameObject*);

private:
	//PRIVATE
	std::unordered_map<Key, collideFuncPtr, PairKeysHash, KeyEqual> m_collideFunctionsMap;

	//c-tor, copy-c-tor, operator=
	CollisionHandler();
	CollisionHandler(const CollisionHandler&) = default;
	CollisionHandler& operator=(const CollisionHandler&) = default;


	//aux
	void initializeMap();


	//handle collision functions 
	void playerOnPlatform(GameObject*, GameObject*);
	void platformOnPlatform(GameObject*, GameObject*);

	void playerOnCoin(GameObject*, GameObject*);
	void coinOnPlayer(GameObject* objA, GameObject* objB) { coinOnPlayer(objB, objA); }

	void playerWithBonusLive(GameObject*, GameObject*);
	void bonusLiveWithPlayer(GameObject* objA, GameObject* objB) { playerWithBonusLive(objB, objA); }

	void playerOnBonusSpeed(GameObject*, GameObject*);
	void bonusSpeedOnPlayer(GameObject* objA, GameObject* objB) { playerOnBonusSpeed(objB, objA); }

	void playerWithBonusMagicEffect(GameObject*, GameObject*);
	void bonusMagicEffectWithPlayer(GameObject* objA, GameObject* objB) { playerWithBonusMagicEffect(objB, objA); }

	void fallingBlockOnPlatform(GameObject*, GameObject*);
	void platformOnFallingBlock(GameObject* objA, GameObject* objB) { fallingBlockOnPlatform(objB, objA); }

	void playerWithBox(GameObject*, GameObject*);
	void boxWithPlayer(GameObject* objA, GameObject* objB) { playerWithBox(objB, objA); }

	void fallingBlockOnPlayer(GameObject*, GameObject*);
	void playerWithFallingBlock(GameObject* objA, GameObject* objB) { fallingBlockOnPlayer(objB, objA); }

	void guillotineTrapOnPlatform(GameObject*, GameObject*);
	void platformOnGuillotineTrap(GameObject* objA, GameObject* objB) { guillotineTrapOnPlatform(objB, objA); }

	void guillotineTrapOnPlayer(GameObject*, GameObject*);
	void playerWithGuillotineTrap(GameObject* objA, GameObject* objB) { guillotineTrapOnPlayer(objB, objA); }

	void playerOnGround(GameObject*, GameObject*);
	void groundOnPlayer(GameObject* objA, GameObject* objB) { playerOnGround(objB, objA); }

	void playerAttackWithEnemy(GameObject*, GameObject*);

	void playerInWaterTrap(GameObject*, GameObject*);
	void waterTrapWithPlayer(GameObject* objA, GameObject* objB) { playerInWaterTrap(objB, objA); }

	void enemyAttackWithPlayer(GameObject* objA, GameObject* objB);

	void magicEffectWithEnemy(GameObject*, GameObject*);
	void enemyWithMagicEffect(GameObject* objA, GameObject* objB) { magicEffectWithEnemy(objB, objA); }

	void magicEffectWithPlatform(GameObject*, GameObject*);
	void platformWithMagicEffect(GameObject* objA, GameObject* objB) { magicEffectWithPlatform(objB, objA); }

	void playerWithMineTrap(GameObject*, GameObject*);
	void mineTrapWithPlayer(GameObject* objA, GameObject* objB) { playerWithMineTrap(objB, objA); }

	void playerWithWinGate(GameObject*, GameObject*);
	void winGateWithPlayer(GameObject* objA, GameObject* objB) { playerWithWinGate(objB, objA); }


	void playerWithGoneTile(GameObject*, GameObject*);
	void goneTileWithPlayer(GameObject* objA, GameObject* objB) { playerWithGoneTile(objB, objA); }


};