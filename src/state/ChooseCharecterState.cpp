#include "state/ChooseCharecterState.h"
#include "buttons/StateButton.h"

//------------------------------- constructor ---------------------------------
ChooseCharecterState::ChooseCharecterState(StateController& stateControl, sf::RenderWindow& window, const int level, const bool gameType)
	: BaseMenuState(stateControl, window), m_successChoose(false), m_chosenSprite(5), m_currDirDisplay(Direction::Right), level(level)
{
	m_enterNameTxt = Resources::getInstance().designText({ 575, 650 }, "enter name:", 19, sf::Color::Black);
	m_title = Resources::getInstance().designText({ 345,100 }, "CHOOSE YOUR CHARECTER", 45);
	m_background.setTexture(Resources::getInstance().getBackgroud(5));

	addButton(std::make_unique<StateButton<GameState>>(StateButton<GameState>({ 565,710 }, std::string(" continue"), BUTTON_BOX, sf::Vector2f(1, 1), true, m_statesControl, CHANGE, m_charecterName, (m_chosenSprite), level, gameType)));
	if(!gameType)m_menuButtons[0]->setButton(false);
}


//-------------------------------- handleClickEvent ---------------------------
void ChooseCharecterState::handleClickEvent()
{
	auto mouseLoc = m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y });

	for (auto index = 0; index < m_menuButtons.size(); ++index)
	{
		if (m_menuButtons[index]->isContain(mouseLoc))
		{
			if (index == 0 && !m_successChoose) break;  //cannot start without choose 

			m_menuButtons[index]->excute(m_window);    
			break;
		}
	}
}


//-------------------------------- update -------------------------------------
void ChooseCharecterState::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (!BaseMenuState::eventsCases()) return;

		if (m_event.type == sf::Event::TextEntered)
		{
			if (m_event.text.unicode < 128) // Handle ASCII characters only
			{
				setTextToTextBox();
				m_inputText.setString(m_charecterName);
			}
		}
	}
}


//-------------------------------- setTextToTextBox ---------------------------
void ChooseCharecterState::setTextToTextBox()
{
	if (m_defualtName)
	{
		m_charecterName.clear();
		m_defualtName = false;
	}
	if (m_event.text.unicode == BACKSPACE)
	{
		if (m_charecterName.size() > 0)
			m_charecterName.pop_back();
	}
	else if (m_inputText.getString().getSize() < 10)
	{
		m_charecterName += m_event.text.unicode;
	}
}


//-------------------------------- update -------------------------------------
void ChooseCharecterState::update()
{
	if (m_clock.getElapsedTime() > sf::seconds(5))
	{
		m_currDirDisplay = next(m_currDirDisplay);
		m_clock.restart();
	}

	for (auto& charecter : m_menuButtons) charecter->update(m_currDirDisplay);
}


//-------------------------------- render -------------------------------------
void ChooseCharecterState::render()
{
	m_window.clear();
	BaseMenuState::render();
	m_window.draw(m_title);
	m_window.draw(m_enterNameSprite);

	m_enterNameTxt.setPosition(575, 650);
	m_enterNameTxt.setString("ENTER NAME: ");
	m_window.draw(m_enterNameTxt);

	m_enterNameTxt.setPosition(800, 650);
	m_enterNameTxt.setString(m_charecterName);
	m_window.draw(m_enterNameTxt);

	m_window.display();
}


//-------------------------------- init ---------------------------------------
void ChooseCharecterState::init()
{
	m_enterNameSprite.setTexture(Resources::getInstance().getButtons(0));
	m_enterNameSprite.setPosition(565, 630);

	addButton(std::make_unique<ChooseCharecterButton>(ChooseCharecterButton({ 40,200 }, m_successChoose, 1, m_chosenSprite, 19, "NADAV-HERO", m_charecterName, m_defualtName)));
	addButton(std::make_unique<ChooseCharecterButton>(ChooseCharecterButton({ 410,200 }, m_successChoose, 2, m_chosenSprite, 20, "ARIEL-HERO", m_charecterName, m_defualtName)));
	addButton(std::make_unique<ChooseCharecterButton>(ChooseCharecterButton({ 790,200 }, m_successChoose, 3, m_chosenSprite, 21, "NOAM-HERO", m_charecterName, m_defualtName)));
	addButton(std::make_unique<ChooseCharecterButton>(ChooseCharecterButton({ 1170,200 }, m_successChoose, 4, m_chosenSprite, 22, "EFRAT-HERO", m_charecterName, m_defualtName)));

	setButtons(sf::Color(127, 127, 127), 20, -100, 1);

	m_clock.restart();
}