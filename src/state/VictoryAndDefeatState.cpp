#include "state/VictoryAndDefeatState.h"
#include "state/MainMenuState.h"
#include "state/GameState.h"


// m_gameEndMode: true == lose | false == win gameType: true == regular | false == practice 

//--------------------------------------- constructor -----------------------------------------
VictoryAndDefeatState::VictoryAndDefeatState(StateController& states, sf::RenderWindow& window, const int& totalTime,
	const unsigned int totalScore, const bool mode, std::string& name, unsigned int& charIndex, const int level, const bool gameType)
	: BaseMenuState(states, window), m_timer(totalTime), m_score(totalScore), m_gameEndMode(mode)
{
	std::cout << level << std::endl;
	addButton(std::make_unique<StateButton<MainMenuState>>(StateButton<MainMenuState>({ 560,690 }, std::string(" MENU "), GAME_BOX, sf::Vector2f(1.7, 1.7), true, m_statesControl, RESTART)));

	if(!gameType || m_gameEndMode)
		addButton(std::make_unique<StateButton<GameState>>(StateButton<GameState>({ 790,690 }, std::string("RESTART"), GAME_BOX, sf::Vector2f(1.7, 1.7), true, m_statesControl, CHANGE_DOUBLE, name, charIndex, level)));
	else
		addButton(std::make_unique<StateButton<GameState>>(StateButton<GameState>({ 790,690 }, std::string("CONTINUE "), GAME_BOX, sf::Vector2f(1.7, 1.7), true, m_statesControl, CHANGE_DOUBLE, name, charIndex, level)));

	setButtons(sf::Color::Black, 20, 0);
}


//------------------------------------------- init ---------------------------------------------
void VictoryAndDefeatState::init()
{
	m_window.setView(m_window.getDefaultView());
	m_window.setView(m_window.getDefaultView());

	m_victory.setTexture(Resources::getInstance().getIcon(38));
	m_victory.setScale(0.27, 0.27);

	m_defeat.setTexture(Resources::getInstance().getIcon(39));
	m_defeat.setScale(0.27, 0.27);

	m_victory.setPosition(m_window.getSize().x / 3.7f, m_window.getSize().y / 4.0f);
	m_defeat.setPosition(m_window.getSize().x / 2.70f, m_window.getSize().y / 3.25f);

	
}


//------------------------------------------- init ---------------------------------------------
void VictoryAndDefeatState::render()
{
	m_window.clear();
	m_prevState->display();

	if (!m_gameEndMode)
		m_window.draw(m_victory);
	else
		m_window.draw(m_defeat);

	BaseMenuState::render();


	m_window.draw(Resources::getInstance().designText({ 625,610 }, Resources::getInstance().designTimer(m_timer), 22, sf::Color::Black));
	m_window.draw(Resources::getInstance().designText({ 845,610 }, std::to_string(m_score), 22, sf::Color::Black));

	m_window.display();
}


//------------------------------------------- update ---------------------------------------------
void VictoryAndDefeatState::update()
{
	m_window.setView(m_window.getDefaultView());
}
