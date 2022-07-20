#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameManage/DataManagement.h"
#include "gameManage/Direction.h"
#include "gameManage/Animation.h"
#include "gameManage/CollisionListener.h"
#include "gui/CameraView.h"
#include "State.h"
#include "macros.h"
#include "Resources.h"
#include "StateController.h"
#include "staticObjects/Ground.h"
#include "gui/MiniMap.h"
#include "BaseMenuState.h"
#include "VictoryAndDefeatState.h"


// game state -> manage the game 
class GameState : public State
{
public:
	GameState(StateController&, sf::RenderWindow&, const std::string&, const unsigned int, const unsigned int, const bool);
	~GameState() {}

	void pause()        override;
	void resume()       override;
	void init()         override;
	void update()       override;
	void render()       override;
	void display()      override;
	void handleEvents() override;
	void checkEndLevel();
	void renderGameBase();
private:
	//------------------------- Members SFML-------------------------
	sf::Sprite       m_background;
	//sf::Clock        m_gameClock;

	//------------------------- Members Box2d------------------------
	std::unique_ptr<b2World> m_world;

	//----------------------- more game members ----------------------
	DataManagement   m_dataManage;
	CameraView       m_view;
	BaseMenuState    m_bottonsMenu;
	PlayerStatus     m_statusBar;

	//------------------------ more data ------------------------------
	std::string      m_userName;
	unsigned int     m_userCharecter;
	unsigned int     m_level;
	const bool       m_gameType; //practice \ story mode
	sf::View         m_currView; 
};
