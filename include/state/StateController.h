#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include <Stack>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace sf
{
	class RenderWindow;
}


// state controller -> manage all the states 
class StateController
{
public:
	StateController(sf::RenderWindow& window) : m_window(window) {}
	~StateController() {}

	//manage the stack wrapper
	void pushState(std::unique_ptr<State>);
	void changeState(std::unique_ptr<State>);
	void popState();

	// The three important actions in a game loop
	void render();
	void update();
	void handleEvents();
	void clearToStart();
	void changeDoubleState(std::unique_ptr<State>);

	//---------- template --------------
	template <typename T>
	static std::unique_ptr<State> buildState(StateController& stackController, sf::RenderWindow& window);


private:
	//states
	std::stack<std::unique_ptr<State>>  m_gameStates;
	sf::RenderWindow& m_window;
};



template <typename T>
std::unique_ptr<State> StateController::buildState(StateController& stackController, sf::RenderWindow& window)
{
	return std::make_unique<T>(stackController, window);
}
