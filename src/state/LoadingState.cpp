#include "state/LoadingState.h"
#include "state/InstructionsState.h"


//------------------------------- constructor -------------------------------------------
LoadingState::LoadingState(StateController& control, sf::RenderWindow& window, const int mode)
	: m_loadingScreen(mode),  State(control, window)
{}


//------------------------------------ init ---------------------------------------------
void LoadingState::init()
{
	m_background.setTexture(Resources::getInstance().getBackgroud(m_loadingScreen)); 
}


//-------------------------------------- render -----------------------------------------
void LoadingState::render()
{
//	m_window.clear(); 
	m_window.draw(m_background); 
	m_window.display();
	sf::sleep(sf::seconds(3));

	changeState(); 
}


//-------------------------------------- changeState ------------------------------------
void LoadingState::changeState()
{
	if (m_loadingScreen == 0) //OPEN SCREEN
	{
		m_statesControl.changeState(StateController::buildState<MainMenuState>(m_statesControl, m_window));
	}

	else if (m_loadingScreen == 1) //END SCREEN
	{
		m_window.close();
	}
}