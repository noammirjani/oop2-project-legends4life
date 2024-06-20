#include "state/GameState.h"
#include "state/SettingsState.h"
#include "buttons/MiniMapButton.h"
#include "buttons/StateButton.h"


//at global scope
CollisionListener ContactListenerInstance;
//------------------------------ CONSTRUCTOR ----------------------------------
GameState::GameState(StateController& states, sf::RenderWindow& window, const std::string& playerName, const unsigned int playerAvatar,const unsigned int level, const bool type)
	: State(states, window), m_view(m_window, 20.f), m_dataManage(playerName, playerAvatar, &m_statusBar), m_bottonsMenu(m_statesControl, m_window),m_level(level), m_gameType(type),
	m_userName(playerName), m_userCharecter(playerAvatar), m_statusBar(playerName, playerAvatar, { 40,40 })
{
	Audio::getInstance().playMusic((LEVELSound - 1) + m_level);
	b2Vec2 Gravity(0.f, 9.8f);
	m_world = std::make_unique<b2World>(Gravity);
	m_world->SetContactListener(&ContactListenerInstance);
}

//-------------------------------------- pause ----------------------------------
// 
//-----------------------------------------------------------------------------
void GameState::pause()
{
	m_statusBar.clock();
	m_currView = m_window.getView();
	m_window.setView(m_window.getDefaultView());
	m_bottonsMenu.updatePos();
}


//-------------------------------------- pause ----------------------------------
// 
//-----------------------------------------------------------------------------5
void GameState::resume()
{
	m_window.setView(m_currView);
	m_statusBar.clock();
}


//-------------------------------------- init ----------------------------------
// 
//-----------------------------------------------------------------------------
void GameState::init()
{
	//window
	m_window.setFramerateLimit(700);

	m_background.setTexture(Resources::getInstance().getBackgroud(5 + m_level));
	m_background.setScale(m_window.getSize().x / 1200.f, m_window.getSize().y / 700.f);

	m_dataManage.setWorld(m_world, m_level);
	m_bottonsMenu.addButton(std::make_unique<MiniMapButton>(MiniMapButton(this, sf::Vector2f(2, 2), std::string(""), MINIMAP_BOX, sf::Vector2f(1, 1), false)));
	m_bottonsMenu.addButton(std::make_unique<StateButton<SettingsState>>(StateButton<SettingsState>({ 0,0 }, std::string(""), SETTINGS, sf::Vector2f(1, 1), false, m_statesControl, PUSH, true)));
}


//------------------------------------- update -------------------------------
// update
//-----------------------------------------------------------------------------
void GameState::update()
{
	m_dataManage.move();
	m_world->    Step(1.0f / 60.0f, 8, 3);
	m_dataManage.eraseObject(m_world);
	m_dataManage.update(m_world);
	m_bottonsMenu.updatePos();

}


//------------------------------------- display -------------------------------
// mange the prints of the game 
//-----------------------------------------------------------------------------
void GameState::render()
{
	m_view.setView(m_dataManage.getPlayerPos());

	/*DebugDraw d(m_window);
	uint32 flags = b2Draw::e_shapeBit;
	d.SetFlags(flags);
	m_world->SetDebugDraw(&d);*/
	m_window.clear();
	display();
   //m_world->DebugDraw();
	m_window.display();
}


//------------------------------------- display -------------------------------
// 
//-----------------------------------------------------------------------------
void GameState::display()
{
	m_window.draw(m_background);
	m_dataManage.draw(m_window);
	m_bottonsMenu.render();
}

//------------------------------------- renderGameBase ------------------------
// for the mini map needed option to draw the game objects and board
//-----------------------------------------------------------------------------
void GameState::renderGameBase()
{
	m_window.draw(m_background);
	m_dataManage.renderMinimapObj(m_window);
}


//------------------------------------- manageEvents --------------------------
// mange the events - temporary  
//-----------------------------------------------------------------------------
void GameState::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		// check the type of the event...
		switch (m_event.type)
		{
		case sf::Event::Closed:
	
			m_statesControl.popState();
			return;
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { m_statesControl.popState(); return; }
			break;

		case sf::Event::MouseButtonReleased:
			m_bottonsMenu.handleClickEvent(m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y }));
		}
	}
	checkEndLevel(); 
}


//------------------------------------- isLevelEnd --------------------------
//=
//-----------------------------------------------------------------------------
void GameState::checkEndLevel()
{
	
	if (m_dataManage.getWin())
	{
		Audio::getInstance().playSoundEffect(WinSOUND);
		
	if (m_gameType)
		++m_level;
	if (m_level == 3) {
		m_statesControl.popState();
		return;
	}
	  m_statesControl.pushState(std::make_unique<VictoryAndDefeatState>(m_statesControl, m_window, m_statusBar.getTotalTime(), m_dataManage.getTotalScore(), false, m_userName, m_userCharecter, m_level, m_gameType));
	}
	else if (m_dataManage.getLose()) {
		Audio::getInstance().playSoundEffect(LoseSOUND);
		m_statesControl.pushState(std::make_unique<VictoryAndDefeatState>(m_statesControl, m_window, m_statusBar.getTotalTime(), m_dataManage.getTotalScore(), true, m_userName, m_userCharecter, m_level, m_gameType));
	 
	}
}