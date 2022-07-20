#pragma once
#include "LevelLoader.h"
#include "box2d/box2d.h"
#include "DebugDraw.h"
#include "gui/PlayerStatus.h"
#include "movingObject/Player.h"


//Manage the objects vectors
class DataManagement
{
public:
	// c-tor | d-tor
//	DataManagement(const std::string & = "", const unsigned int = 10);
	~DataManagement() {}

	DataManagement(const std::string& playerName, const unsigned int playerAvatar, PlayerStatus* playerStatus);

	// set function
	void setWorld(std::unique_ptr<b2World>&, const unsigned);

	bool getWin ()  const  { return m_player->getPlayerWin (); }
	bool getLose()  const { return m_player->getPlayerLose(); }
	// update data
	void update(std::unique_ptr<b2World>&);
	void eraseObject    (std::unique_ptr<b2World>&);
	void move           ();


	// display
	void draw(sf::RenderWindow&);
	void renderMinimapObj(sf::RenderWindow& window);

	// get location for view
	sf::Vector2f getPlayerPos() const;
	unsigned int getTotalScore() const;

private:
	void eraseStaticObject(std::unique_ptr<b2World>& );
	void eraseMovingObject(std::unique_ptr<b2World>& );
	//sfml
	sf::Clock        m_gameClock;

	//box2d
	int m_resourcesPlayer;
	//game objects
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects; 
	std::vector<std::unique_ptr<MovingObject>> m_movingObjects; 
	std::unique_ptr<Player>					   m_player;

	//player data 
	PlayerStatus* m_statusBar;
};
