#include "state/InstructionsState.h"
#include "state/MainMenuState.h"
#include "state/SettingsState.h"
#include <memory>
#include "buttons/PageButton.h"


//------------------------------ CONSTRUCTOR ----------------------------------
InstructionsState::InstructionsState(StateController& states, sf::RenderWindow& window)
	: BaseMenuState(states, window), m_currFrame(1, 1)
{}


//------------------------------------- init ----------------------------------
void InstructionsState::init()
{
	m_background.setTexture(Resources::getInstance().getBackgroud(4));
	m_background.setTextureRect({ m_currFrame.x ,m_currFrame.y,700,800 });
	m_background.setPosition(450, 50);

	PagesButtons next(4914, m_currFrame, 702, { 1050,750 }, "", NEXT_BOX, { 1.4,1.4 }, true);
	PagesButtons pre(4914, m_currFrame, -702, { 510,750 }, "", PREV_BOX, { 1.4,1.4 }, true);

	addButton(std::make_unique<PagesButtons>(next));
	addButton(std::make_unique<PagesButtons>(pre));
	addButton((std::make_unique<StateButton<MainMenuState>>(StateButton<MainMenuState>({ 1080,65 }, std::string(""), EXIT, sf::Vector2f(2, 2), false, m_statesControl, POP))));
}


//---------------------------- render -----------------------------------------
//print the background for help, move on the text we want to illustrate to the
//user and with sf::clock introduce hin in a typing effect way
//-----------------------------------------------------------------------------
void InstructionsState::render()
{
	m_window.clear();
	if (m_prevState) m_prevState->display();
	BaseMenuState::render();
	m_window.display();
}


//---------------------------- handleClickEvent -------------------------------
//
//-----------------------------------------------------------------------------
void InstructionsState::handleClickEvent()
{
	auto mouseLoc = m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y });
	BaseMenuState::handleClickEvent(mouseLoc);
	m_background.setTextureRect({ m_currFrame.x , m_currFrame.y, 700,800 });
}
