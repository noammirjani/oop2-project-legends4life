#include "gameManage/Controller.h"


//------------------------------ CONSTRUCTOR ----------------------------------
Controller::Controller() : m_window({ 1600,900 }, "LEGENDS4LIFE"), m_statesControl(m_window)
{
	setWindowIcone();
	m_window.setActive(true); 
}

//------------------------------ setWindowIcone -------------------------------
void Controller::setWindowIcone()
{
	sf::Image icon = Resources::getInstance().getGameIcon();
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}


//---------------------------------- run --------------------------------------
//run the state loop 
void Controller::run() try
{
	initStack();
	// Main loop
	while (m_window.isOpen())
	{
		m_statesControl.handleEvents();
		m_statesControl.update();
		m_statesControl.render();
	}
	//endState
}
catch (std::exception& ex){std::cerr << "Exception: " << ex.what() << '\n';}
catch (...){std::cerr << "Unknown exception\n";}


//---------------------------------- initStack --------------------------------
// Initialize the engine
void Controller::initStack()
{
	m_statesControl.pushState(std::make_unique<LoadingState>(m_statesControl, m_window, 0));
}