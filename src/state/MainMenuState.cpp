#include "state/MainMenuState.h"
#include "state/chooseCharecterState.h"
#include "state/ChooseLevelState.h"
#include "state/LeadboardState.h"



//--------------------------------- CONSTRUCTOR -------------------------------
MainMenuState::MainMenuState(StateController& states, sf::RenderWindow& window)
	: BaseMenuState(states, window), m_TitleInPlace(false)
{
	Audio::getInstance().playMusic(MENU_SOUND);
}


//--------------------------------- init --------------------------------------
void MainMenuState::init()
{
	//title
	m_title.setTexture(Resources::getInstance().getBackgroud(1));
	m_title.setPosition(230, 700);
	m_title.setScale(2, 2);
	m_TitleInPlace = false;
	//background
	m_background.setTexture(Resources::getInstance().getBackgroud(2));
	//buttons
	addButton(std::make_unique<StateButton<SettingsState>>		 (StateButton<SettingsState>		({1500,80}, std::string(""),          SETTINGS,   sf::Vector2f(1, 1), false, m_statesControl, PUSH)));
	addButton(std::make_unique<StateButton<ChooseCharecterState>>(StateButton<ChooseCharecterState> (SINGLE_POS,std::string("GAME"),      BUTTON_BOX, sf::Vector2f(1, 1), true, m_statesControl, PUSH, 1)));
	addButton(std::make_unique<StateButton<ChooseLevelState>>	 (StateButton<ChooseLevelState>		(MULT_POS,  std::string(" PRACTICE"), BUTTON_BOX, sf::Vector2f(1, 1), true, m_statesControl, PUSH)));
	addButton(std::make_unique<StateButton<InstructionsState>>	 (StateButton<InstructionsState>	(HELP_POS,  std::string("HELP"),      BUTTON_BOX, sf::Vector2f(1, 1), true, m_statesControl, PUSH)));
	addButton(std::make_unique<Button>							 (Button							(EXIT_POS,  std::string("EXIT"),      BUTTON_BOX, sf::Vector2f(1, 1), true)));
}


//---------------------------------- resume -----------------------------------
void MainMenuState::resume()
{
	m_window.setView(m_window.getDefaultView());
}


//---------------------------------- render -----------------------------------
void MainMenuState::render()
{
	m_window.clear();
	display();
	m_window.display();
}


//---------------------------------- update -----------------------------------
void MainMenuState::update()
{
	if (m_TitleInPlace) return;

	if (!m_TitleInPlace)
	{
		m_title.move({ 0.f,-0.1f });
	}

	if (m_title.getPosition().y < 100.f)
	{
		m_TitleInPlace = true;
	}

}


//---------------------------------- handleEvents -----------------------------
void MainMenuState::handleEvents()
{
	if (!m_TitleInPlace)
	{
		if (m_window.pollEvent(m_event)) {}
	}

	else
	{
		BaseMenuState::handleEvents();
	}
}


//---------------------------------- display ----------------------------------
void MainMenuState::display()
{
	BaseMenuState::render();
	m_window.draw(m_title);
}