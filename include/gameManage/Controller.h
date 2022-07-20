#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "state/StateController.h"
#include "state/LoadingState.h"

//CONTROLLER = manage all the state and basic game preformens 
class Controller
{
public:
	//c-tor, d-tor
	Controller();
	~Controller() {}

	//FUNCTIONS
	void run();

private:
	//sfml
	sf::RenderWindow m_window;
	StateController  m_statesControl;

	std::unique_ptr<b2World> m_world;

	//privateFunctions
	void setWindowIcone();
	void initStack();
};
