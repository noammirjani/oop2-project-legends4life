#include "state/ChooseLevelState.h"
#include "state/ChooseCharecterState.h"


//------------------------------- constructor ---------------------------------
ChooseLevelState::ChooseLevelState(StateController& stateControl, sf::RenderWindow& window)
	: BaseMenuState(stateControl, window), m_successChoose(false), m_chosenSprite(4)
{
	m_title = Resources::getInstance().designText({ 500,100 }, "CHOOSE LEVEL:", 45);
	m_titleBackground.setTexture(Resources::getInstance().getButtons(0));
	m_titleBackground.setPosition({ 450,80 });
	m_titleBackground.setScale(1.5, 1.5);

	m_levelsBoard.setTexture(Resources::getInstance().getBackgroud(6));
	
	m_background.setTexture(Resources::getInstance().getLevelIcon(0));
	m_background.setPosition(350, 200);
	m_background.setScale(1.5f, 1.5f);
}


//-------------------------------- handleClickEvent ---------------------------
void ChooseLevelState::handleClickEvent()
{
	auto mouseLoc = m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y });

	for (auto index = 0; index < m_menuButtons.size(); ++index)
	{
		if (m_menuButtons[index]->isContain(mouseLoc))
		{
			if (index == 0 && !m_successChoose) break;  //cannot start without choose 

			if (index == 0 && m_successChoose) m_menuButtons[index]->setButton(m_chosenSprite); 

			m_menuButtons[index]->excute(m_window);
			break;
		}
	}
}


//-------------------------------- update -------------------------------------
void ChooseLevelState::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (!BaseMenuState::eventsCases()) return;
	}
}


//-------------------------------- render -------------------------------------
void ChooseLevelState::render()
{
	m_window.clear();
	m_window.draw(m_levelsBoard);
	BaseMenuState::render();
	m_window.draw(m_titleBackground);
	m_window.draw(m_title);
	m_window.display();
}


//-------------------------------- init ---------------------------------------
void ChooseLevelState::init()
{
	addButton(std::make_unique<StateButton<ChooseCharecterState>>(StateButton<ChooseCharecterState>({ 565,750 }, std::string("  Continue"), BUTTON_BOX, sf::Vector2f(1, 1), true, m_statesControl,CHANGE, m_chosenSprite)));
	addButton(std::make_unique<ChooseLevelButton>(ChooseLevelButton({ 410,400 }, m_successChoose, 1 , m_chosenSprite, 1)));
	addButton(std::make_unique<ChooseLevelButton>(ChooseLevelButton({ 670,400 }, m_successChoose, 2, m_chosenSprite,  2)));
	addButton(std::make_unique<ChooseLevelButton>(ChooseLevelButton({ 920,400 }, m_successChoose, 3, m_chosenSprite, 3)));
	 
	m_clock.restart();
} 