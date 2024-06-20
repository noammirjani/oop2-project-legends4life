#pragma once

#include <SFML/Graphics.hpp>
#include "StateController.h"
#include "State.h"
#include "macros.h"
#include "Resources.h"
#include "BaseMenuState.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>  

const int MAX_LEADBOARD = 9;

//leadoard state
class LeadboardState : public State
{
public:
	LeadboardState(StateController&, sf::RenderWindow&);
	~LeadboardState() { m_leadBoardFile.close(); }

	void init()         override;
	void update()       override {}
	void render()       override;
	void handleEvents() override;

	bool readDataFromValue();
	void beginOfLevelFiles();

	void setLeadboardData();


private:
	sf::Sprite				   m_leadBoardImage;
	sf::Text				   m_title;
	std::ifstream			   m_leadBoardFile;
	std::vector<sf::Text>      m_leadBoardData;
	std::map<int, std::string> m_sortedScores;
};