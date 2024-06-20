#pragma once
#include "Button.h"
#include "state/StateController.h"
#include "state/gameState.h"
#include "state/ChooseCharecterState.h"


// how to switch the state consts
const int PUSH = 0, CHANGE = 1, POP = 2, RESTART = 3, CHANGE_DOUBLE = 4;


// state button -> template
template <class T>
class StateButton : public Button
{
public:
	StateButton(const sf::Vector2f& pos, const std::string& txt, const int type, const sf::Vector2f& scale, const bool pressedSprite, StateController& states, const int mode, const bool movingButton = false)
		: Button(pos, txt, type, scale, pressedSprite), m_stateController(states), m_mode(mode), m_moving(movingButton){}
	~StateButton() {}

	void excute(sf::RenderWindow& window) override
	{
		if (m_mode == POP) { m_stateController.popState(); return; }
		if (m_mode == RESTART) { m_stateController.clearToStart(); return; }

		auto tempState = StateController::buildState<T>(m_stateController, window);

		if (m_mode == PUSH)  m_stateController.pushState(std::move(tempState));
		if (m_mode == CHANGE)  m_stateController.changeState(std::move(tempState));
	}

	void render(sf::RenderWindow& window) override
	{
		if(m_moving)  m_button.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 130)));
		Button::render(window);
	}

private:
	StateController& m_stateController;
	const int m_mode;
	const bool m_moving; 
};



// class template specialization:
template <>
class StateButton<GameState> : public Button
{
public:
	StateButton(const sf::Vector2f& pos, const std::string& txt, const int type, const sf::Vector2f& scale, const bool pressedSprite,
		StateController& states, const int mode, std::string& charName, unsigned int& index, const unsigned int level, const bool gameType = true)
		: Button(pos, txt, type, scale, pressedSprite), m_stateController(states), m_stateMode(mode), m_name(charName), m_indexIcon(index), m_level(level), m_gameMode(gameType) {}
	~StateButton() {}

	void excute(sf::RenderWindow& window) override
	{
		auto tempState = std::make_unique<GameState>(m_stateController, window, m_name, m_indexIcon, m_level, m_gameMode);

		if (m_stateMode == PUSH)  m_stateController.pushState(std::move(tempState));
		if (m_stateMode == CHANGE)  m_stateController.changeState(std::move(tempState));
		if (m_stateMode == CHANGE_DOUBLE)  m_stateController.changeDoubleState(std::move(tempState));
	}

	void setButton(const unsigned int type) override
	{
		m_gameMode = type;
	}

private:
	StateController& m_stateController;
	int m_stateMode;
	unsigned int m_level;
	std::string& m_name;
	unsigned int& m_indexIcon;
	bool m_gameMode;
};



// class template specialization:
template <>
class StateButton<ChooseCharecterState> : public Button
{
public:
	StateButton(const sf::Vector2f& pos, const std::string& txt, const int type, const sf::Vector2f& scale, const bool pressedSprite, StateController& states, const int stateMode, const unsigned int level = 1)
		: Button(pos, txt, type, scale, pressedSprite), m_stateController(states), m_level(level), m_stateMode(stateMode) {}
	~StateButton() {}

	void excute(sf::RenderWindow& window) override
	{
		auto tempState = std::make_unique<ChooseCharecterState>(m_stateController, window, m_level, m_regularGame);
		if (m_stateMode == PUSH)  m_stateController.pushState(std::move(tempState));
		if (m_stateMode == CHANGE)  m_stateController.changeState(std::move(tempState));
	}

	void setButton(const unsigned int level) override
	{
		m_level = level;
		m_regularGame = false;
	}

private:
	StateController& m_stateController;
	unsigned int m_level = 1;
	bool m_regularGame = true;
	int m_stateMode;
};