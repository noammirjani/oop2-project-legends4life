#include "state/BaseMenuState.h"
#include "state/StateController.h"
#include "state/GameState.h"
#include <iostream>
#include "buttons/StateButton.h"


//------------------------------ CONSTRUCTOR ----------------------------------
BaseMenuState::BaseMenuState(StateController& states, sf::RenderWindow& window)
	: State(states, window)
{}


//------------------------------- handleEvents --------------------------------
void BaseMenuState::addButton(ButtonPtr newButton)
{
	m_menuButtons.emplace_back(std::move(newButton));
}


//------------------------------- handleEvents --------------------------------
void BaseMenuState::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (!eventsCases()) return; //if the state pop out -> return 
	}
}


//------------------------------- handleEvents --------------------------------
//needed for the inhirnts classes to add more cases withot another loop event
bool BaseMenuState::eventsCases()
{
	switch (m_event.type)
	{
	case sf::Event::Closed:
		m_statesControl.popState();
		return false;
		break;

	case sf::Event::MouseButtonReleased:
		handleClickEvent();
		return false;
		break;

	case sf::Event::MouseMoved:
		handleMouseMovedEvent();
		break;
	}
	return true;
}


//------------------------------- render --------------------------------------
void BaseMenuState::render()
{
	m_window.draw(m_background);
	for (const auto& button : m_menuButtons) button->render(m_window);
}


//--------------------------------- truckMouse --------------------------------
void BaseMenuState::handleMouseMovedEvent()
{
	auto mouseLoc = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	for (const auto& button : m_menuButtons) button->HandleHover(mouseLoc);
}


//--------------------------------- handleClickEvent --------------------------
void BaseMenuState::handleClickEvent()
{
	auto mouseLoc = m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y });

	for (auto& button : m_menuButtons)
	{
		if (button->isContain(mouseLoc))
		{
			button->ClickedButton(m_statesControl);
			button->excute(m_window);
			break;
		}
	}
}


//--------------------------------- handleClickEvent --------------------------
void BaseMenuState::handleClickEvent(sf::Vector2f mouseLoc)
{
	for (auto& button : m_menuButtons)
	{
		if (button->isContain(mouseLoc))
		{
			button->ClickedButton(m_statesControl);
			button->excute(m_window);
			break;
		}
	}
}


//------------------------------------- updatePos -----------------------------
// 
//-----------------------------------------------------------------------------
void BaseMenuState::updatePos()
{
	for (const auto& button : m_menuButtons) { button->setOrginPos(m_window); }
}



//------------------------------------- setButtons -----------------------------
// 
//-----------------------------------------------------------------------------
void BaseMenuState::setButtons(sf::Color color, const int size, const int move, const int range)
{
	if (range >= m_menuButtons.size()) throw std::overflow_error("trying to set button that not found in vec");

	for (auto i = range; i < m_menuButtons.size(); ++i)
	{
		m_menuButtons[i]->setDesign(color, size, move);
	}
}
