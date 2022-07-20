#pragma once
#include "BaseMenuState.h"
#include "Resources.h"
#include "gameManage/Direction.h"
#include "buttons/ChooseCharecterButton.h"


//choose charecter state
class ChooseCharecterState : public BaseMenuState
{
public:
	ChooseCharecterState(StateController&, sf::RenderWindow&, const int, const bool);
	~ChooseCharecterState() {}

	void update()          override;
	void render()          override;
	void init()            override;
	void handleClickEvent()override;
	void handleEvents()    override;
	void setTextToTextBox();

private:
	bool m_successChoose;
	unsigned int m_chosenSprite;

	Direction     m_currDirDisplay;
	sf::Clock     m_clock;
	sf::Text      m_title, m_enterNameTxt, m_inputText;
	std::string   m_charecterName = "";
	sf::Sprite    m_enterNameSprite;
	bool          m_defualtName;
	const int level; 
};