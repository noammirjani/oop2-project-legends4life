//m_collideFunctionsMap[Key(typeid(Platform), typeid(Player))] = &[](GameObject* objA, GameObject* objB) {playerOnPlatform(objB, objA)});
#include "gameManage/CollisionHandler.h"
#include "MovingObject/Player.h"
#include "StaticObjects/Platform.h"
#include "StaticObjects/BonusCoin.h"
#include "StaticObjects/BonusSpeed.h"
#include "StaticObjects/BonusLive.h"
#include "StaticObjects/WinGate.h"
#include "MovingObject/FallingBlock.h"
#include "StaticObjects/MineTrap.h"
#include "MovingObject/MovingPlatform.h"
#include "movingObject/MagicEffect.h"
#include "MovingObject/GuillotineTrap.h"
#include "StaticObjects/BonusMagicEffect.h"
#include "StaticObjects/GoneTile.h"
#include "movingObject/MovingPlatform.h"
#include "MovingObject/Enemy.h"
#include "StaticObjects/WaterTrap.h"
#include "StaticObjects/Box.h"
#include "StaticObjects/Ground.h"

//-----------------------------------------------------------------------------
CollisionHandler& CollisionHandler::getInstance()
{
	static CollisionHandler instane;
	return instane;
}


//-----------------------------------------------------------------------------
CollisionHandler::CollisionHandler()
{
	initializeMap();
}

//-----------------------------------------------------------------------------
void CollisionHandler::initializeMap()
{

	m_collideFunctionsMap[Key(typeid(Player),         typeid(Platform))]       = &CollisionHandler::playerOnPlatform;
	m_collideFunctionsMap[Key(typeid(Platform),       typeid(Player))]         = &CollisionHandler::platformOnPlatform;
	m_collideFunctionsMap[Key(typeid(Player),         typeid(MovingPlatform))] = &CollisionHandler::playerOnPlatform;
	m_collideFunctionsMap[Key(typeid(MovingPlatform), typeid(Player))]         = &CollisionHandler::platformOnPlatform;

	//------------------------------------- Bonus collison ---------------------------------------------
	m_collideFunctionsMap[Key(typeid(Player),           typeid(BonusCoin))]   = &CollisionHandler::playerOnCoin;
	m_collideFunctionsMap[Key(typeid(BonusCoin),        typeid(Player))]      = &CollisionHandler::coinOnPlayer;
	m_collideFunctionsMap[Key(typeid(Player),           typeid(BonusSpeed))]  = &CollisionHandler::playerOnBonusSpeed;
	m_collideFunctionsMap[Key(typeid(BonusSpeed),       typeid(Player))]      = &CollisionHandler::bonusSpeedOnPlayer;
	m_collideFunctionsMap[Key(typeid(Player),           typeid(BonusLive))]   = &CollisionHandler::playerWithBonusLive;
	m_collideFunctionsMap[Key(typeid(BonusLive),        typeid(Player))]      = &CollisionHandler::bonusLiveWithPlayer;
	m_collideFunctionsMap[Key(typeid(Player),           typeid(BonusMagicEffect))] = &CollisionHandler::playerWithBonusMagicEffect;
	m_collideFunctionsMap[Key(typeid(BonusMagicEffect), typeid(Player))]      = &CollisionHandler::bonusMagicEffectWithPlayer;

	//------------------------------------- Falling Block collison ---------------------------------------------
	m_collideFunctionsMap[Key(typeid(FallingBlock),    typeid(Platform))]       = &CollisionHandler::fallingBlockOnPlatform;
	m_collideFunctionsMap[Key(typeid(Platform),        typeid(FallingBlock))]   = &CollisionHandler::platformOnFallingBlock;
	m_collideFunctionsMap[Key(typeid(FallingBlock),    typeid(Player))]         = &CollisionHandler::fallingBlockOnPlayer;
	m_collideFunctionsMap[Key(typeid(Player),          typeid(FallingBlock))]   = &CollisionHandler::playerWithFallingBlock;
	m_collideFunctionsMap[Key(typeid(FallingBlock),    typeid(MovingPlatform))] = &CollisionHandler::fallingBlockOnPlatform;
	m_collideFunctionsMap[Key(typeid(MovingPlatform),  typeid(FallingBlock))]   = &CollisionHandler::platformOnFallingBlock;
	m_collideFunctionsMap[Key(typeid(Player),          typeid(Box))]            = &CollisionHandler::playerWithBox;
	m_collideFunctionsMap[Key(typeid(Box),             typeid(Player))]         = &CollisionHandler::boxWithPlayer;
	m_collideFunctionsMap[Key(typeid(Player),          typeid(GoneTile))]       = &CollisionHandler::playerWithGoneTile;
	m_collideFunctionsMap[Key(typeid(GoneTile),        typeid(Player))]         = &CollisionHandler::goneTileWithPlayer;

	//--------------------------------------- Guillotine Trap collison -----------------------------------------
	m_collideFunctionsMap[Key(typeid(GuillotineTrap), typeid(Platform))]       = &CollisionHandler::guillotineTrapOnPlatform;
	m_collideFunctionsMap[Key(typeid(Platform),       typeid(GuillotineTrap))] = &CollisionHandler::platformOnGuillotineTrap;
	m_collideFunctionsMap[Key(typeid(GuillotineTrap), typeid(Player))]         = &CollisionHandler::guillotineTrapOnPlayer;
	m_collideFunctionsMap[Key(typeid(Player),         typeid(GuillotineTrap))] = &CollisionHandler::playerWithGuillotineTrap;
	//--------------------------------------- Mine Trap collison -----------------------------------------
	m_collideFunctionsMap[Key(typeid(Player),         typeid(MineTrap))]       = &CollisionHandler::playerWithMineTrap;
	m_collideFunctionsMap[Key(typeid(MineTrap),       typeid(Player))]         = &CollisionHandler::mineTrapWithPlayer;

	//--------------------------------------- Win Gate collison -----------------------------------------
	m_collideFunctionsMap[Key(typeid(Player),         typeid(WinGate))]        = &CollisionHandler::playerWithWinGate;
	m_collideFunctionsMap[Key(typeid(WinGate),        typeid(Player))]         = &CollisionHandler::winGateWithPlayer;

	//------------------------------------------- Enemy collison -----------------------------------------------
	m_collideFunctionsMap[Key(typeid(Player),        typeid(Enemy))]           = &CollisionHandler::playerAttackWithEnemy;
	m_collideFunctionsMap[Key(typeid(Enemy),         typeid(Player))]          = &CollisionHandler::enemyAttackWithPlayer;

	//------------------------------------------- MagicEffect collison -----------------------------------------
	m_collideFunctionsMap[Key(typeid(MagicEffect),   typeid(Enemy))]           = &CollisionHandler::magicEffectWithEnemy;
	m_collideFunctionsMap[Key(typeid(Enemy),         typeid(MagicEffect))]     = &CollisionHandler::enemyWithMagicEffect;
	m_collideFunctionsMap[Key(typeid(MagicEffect),   typeid(Platform))]        = &CollisionHandler::magicEffectWithPlatform;
	m_collideFunctionsMap[Key(typeid(Platform),      typeid(MagicEffect))]     = &CollisionHandler::platformWithMagicEffect;

	//----------------------------------------------------------------------------------------------------------
	m_collideFunctionsMap[Key(typeid(Player),        typeid(Ground))]          = &CollisionHandler::playerOnGround;
	m_collideFunctionsMap[Key(typeid(Ground),        typeid(Player))]          = &CollisionHandler::groundOnPlayer;
	m_collideFunctionsMap[Key(typeid(Player),        typeid(WaterTrap))]       = &CollisionHandler::playerInWaterTrap;
	m_collideFunctionsMap[Key(typeid(WaterTrap),     typeid(Player))]          = &CollisionHandler::waterTrapWithPlayer;
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerOnPlatform(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	player->setPlayerJump(false);
}
//-----------------------------------------------------------------------------
void CollisionHandler::platformOnPlatform(GameObject* objA, GameObject* objB)
{
	playerOnPlatform(objB, objA);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerOnCoin(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	BonusCoin* coin = static_cast<BonusCoin*> (objB);

	player->updateCoins();

	coin->setIsDisposed(true);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerOnBonusSpeed(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	BonusSpeed* bonusSpeed = static_cast<BonusSpeed*> (objB);

	player->setBounsSpeed(bonusSpeed->getBounsSpeed());
	bonusSpeed->setIsDisposed(true);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerWithBonusMagicEffect(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	BonusMagicEffect* bonusEffect = static_cast<BonusMagicEffect*> (objB);

	player->updateMagicEffect();
	bonusEffect->setIsDisposed(true);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerWithBonusLive(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	BonusLive* bonusSpeed = static_cast<BonusLive*> (objB);

	player->updateLives();
	bonusSpeed->setIsDisposed(true);
}
//-----------------------------------------------------------------------------
void CollisionHandler::fallingBlockOnPlatform(GameObject* objA, GameObject* objB)
{
	FallingBlock* trap = static_cast<FallingBlock*> (objA);
	trap->resetToFirstPosition();
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerWithBox(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	playerOnPlatform(objA, objB);
	player->updateGravity();
}
//-----------------------------------------------------------------------------
void CollisionHandler::guillotineTrapOnPlatform(GameObject* objA, GameObject*)
{
	GuillotineTrap* trap = static_cast<GuillotineTrap*> (objA);
	trap->resetToFirstPosition();
}
//-----------------------------------------------------------------------------
void CollisionHandler::guillotineTrapOnPlayer(GameObject* objA, GameObject* objB)
{
	GuillotineTrap* trap = static_cast<GuillotineTrap*> (objA);
	if (trap->getEndCollison())
		playerOnGround(objB, objA);

	guillotineTrapOnPlatform(objA, objB);
}
//-----------------------------------------------------------------------------
void CollisionHandler::fallingBlockOnPlayer(GameObject* objA, GameObject* objB)
{
	FallingBlock* trap = static_cast<FallingBlock*> (objA);
	if (!trap->getEndCollison())
		playerOnGround(objB, objA);

	fallingBlockOnPlatform(objA, objB);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerOnGround(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	if(!player->getIfCollide())
	player->manageDisqualified();
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerAttackWithEnemy(GameObject* objA, GameObject* objB)
{

	Player* player = static_cast<Player*> (objA);
	Enemy* enemy = static_cast  <Enemy*>    (objB);
	bool playerAttack = true;


	if ((player->getSideOfMovebleObject()) // go left
		&& player->getPositionOfMovebleObject().x < enemy->getPositionOfMovebleObject().x)
	{
		playerAttack = false;
	}

	else if (!(player->getSideOfMovebleObject()) // go right
		&& player->getPositionOfMovebleObject().x > enemy->getPositionOfMovebleObject().x)
	{
		playerAttack = false;
	}
	player->initAttackWithNewEnemy(enemy);

	if ((enemy->getSideOfMovebleObject()) // go left
		&& enemy->getPositionOfMovebleObject().x < player->getPositionOfMovebleObject().x)
	{
		return;
	}

	else if (!(enemy->getSideOfMovebleObject()) // go right
		&& enemy->getPositionOfMovebleObject().x > player->getPositionOfMovebleObject().x)
	{
		return;
	}
	if (!enemy->getAttack()) {
		enemy->manageAttack();
		player->updateInjury();
	}

}
//-----------------------------------------------------------------------------
void CollisionHandler::magicEffectWithEnemy(GameObject* objA, GameObject* objB)
{
	Enemy* enemy = static_cast<Enemy*>    (objB);
	MagicEffect* magic = static_cast <MagicEffect*> (objA);
	if (!magic->getIsBodyDisposed()) {
		magic->collisionMagicEffect();
		enemy->manageDisqualified();
	}
	//magicEffectWithPlatform  (objA, objB);
}
//-----------------------------------------------------------------------------
void CollisionHandler::magicEffectWithPlatform(GameObject* objA, GameObject* objB)
{
	MagicEffect* magic = static_cast <MagicEffect*> (objA);
	magic->collisionMagicEffect();
}

//-----------------------------------------------------------------------------
void CollisionHandler::playerWithMineTrap(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	MineTrap* trap = static_cast<MineTrap*> (objB);
	if (!trap->endCollide()) {
		trap->handleCollide();
		playerOnGround(objA, objB);
	}
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerWithWinGate(GameObject* objA, GameObject* objB)
{
	Player* player = static_cast<Player*> (objA);
	WinGate* gate = static_cast <WinGate*> (objB);

	gate->handleCollide();
	player->setPlayerWin(true);
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerWithGoneTile(GameObject* objA, GameObject* objB)
{
	playerOnPlatform(objA, objB);
	GoneTile* gone_tile = static_cast<GoneTile*> (objB);
	gone_tile->handleCollide();
}
//-----------------------------------------------------------------------------
void CollisionHandler::playerInWaterTrap(GameObject* objA, GameObject* objB)
{
	playerOnGround(objA, objB);
	Audio::getInstance().playSoundEffect(WATERFALLING);
}
//-----------------------------------------------------------------------------
void CollisionHandler::enemyAttackWithPlayer(GameObject* objA, GameObject* objB)
{
	playerAttackWithEnemy(objB, objA);
}
//-----------------------------------------------------------------------------
void CollisionHandler::handleCollision(GameObject* object1, GameObject* object2)
{
	//returns type MapEntery to the hash table - the search using the KeyEqual function struct
	auto mapEntry = m_collideFunctionsMap.find(Key(typeid(*object1), typeid(*object2)));

	if (mapEntry != m_collideFunctionsMap.end())
	{
		auto func = mapEntry->second;
		(this->*(func))(object1, object2);
	}
}
