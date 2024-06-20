#pragma once
#include "MovingObject.h"
#include "gameManage/CheckPoint.h"
#include "MagicEffect.h"
#include "staticObjects/Ground.h"
#include "Enemy.h"
#include "gui/LifeStatusBar.h"

//--------------------------- Class Section --------------------------
class Player : public MovingObject
{
public:
	//					Constructors & Destructors
	//--------------------------------------------------------------- 
	Player(std::unique_ptr<b2World>&, CheckPoint&&, enum b2BodyType, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	virtual ~Player() {}


	//				          virtual functions
	//---------------------------------------------------------------
	void draw(sf::RenderWindow&)		   override;
	void move()                            override;
	void jump(const float);
	void update(std::unique_ptr<b2World>&) override;
	void manageAttack();
	void magicEffectAttack();


	//                           aux functions 
	//-----------------------------------------------------------------
	void manageDisqualified();
	void updateCoins() { ++m_coins; Audio::getInstance().playSoundEffect(COINCOLLECT); }
	void updateLives() { if (m_lifes == 3) { Audio::getInstance().playSoundEffect(LIFESOUND); return; } ++m_lifes; }
	void updateEnergy();
	void updateMagicEffect();
	void updateGravity() { m_objectBody->SetAwake(false); };
	void updateInjury () { --m_injury; if (m_injury == 0) { --m_lifes;  manageDisqualified(); } }


	//							  Get functions
	//---------------------------------------------------------------
	bool getMagicEffect() const { return m_newMagicEffect; }
	bool getPlayerWin  () const { return m_win && !m_animation.getFrameByClock(); }
	bool getPlayerLose () const { return m_lifes <= 0; }
	int  getLifesNum    () const { return m_lifes;      }
	int  getCoinNum     () const { return m_coins; }
	int  getEnergyNum  () const { return m_energy; }
	int  getEffectType () const { return m_magicEffect.getType(); }



	//							 Set functions
	//---------------------------------------------------------------
	void setPlayerJump(const bool cond) { m_jump = cond; }
	void setPlayerWin(const bool cond) { m_win = cond; }
	void setBounsSpeed(const int speed) { m_bonusSpeed = speed; }
	void setCollideWithEnemy(const bool cond) { m_collideEnemy = cond; }
	void initAttackWithNewEnemy(Enemy*);



	//							 Avatar functions
	//---------------------------------------------------------------
	void setAvatarSprite(const int);
	void drawAvatar(sf::RenderWindow&);



private:
	void specialAnimation(const int row) {
		m_animation.setRowAnimation(row);
		m_animation.setFrameByClock(true);
	}
	//							 Get private functions
	//---------------------------------------------------------------
	bool getPlyaerJump() const { return m_jump; }
	bool getPlyaerAttack() const { return m_attack; }

	void checkAttackEnemy();
	CheckPoint   m_checkPointPosition;
	MagicEffect  m_magicEffect;
	Ground       m_ground;
	bool m_attack = false;
	bool m_jump = false;
	bool m_collideEnemy = false;
	bool m_newMagicEffect = false;
	unsigned int m_bonusSpeed = 0;

	unsigned int m_coins = 0;
	int          m_energy = 100;
    int          m_lifes = 3;
	bool		 m_win = false;
	unsigned int m_injury = 3;
	sf::Sprite   m_avatarSprite;
	LifeStatusBar m_lifeBar;

	Enemy* m_enemy;
};