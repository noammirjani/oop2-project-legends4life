#pragma once
#include "BaseMenuState.h"
#include "Resources.h"
#include "buttons/StateButton.h"
#include "buttons/ChooseLevelButton.h"



//choose level state
class ChooseLevelState : public BaseMenuState
{
public:
	ChooseLevelState(StateController&, sf::RenderWindow&);
	~ChooseLevelState() {}

	void render()          override;
	void init()            override;
	void handleClickEvent()override;
	void handleEvents()    override;

private:
	bool m_successChoose;
	unsigned int m_chosenSprite;

	sf::Clock     m_clock;
	sf::Text      m_title;
	sf::Sprite    m_titleBackground;
	sf::Sprite    m_levelsBoard;
};