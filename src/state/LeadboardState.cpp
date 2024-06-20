#include "state/LeadboardState.h"
#include <memory>


//------------------------------ CONSTRUCTOR ----------------------------------
LeadboardState::LeadboardState(StateController& states, sf::RenderWindow& window)
	: State(states, window)
{
	m_leadBoardFile.open("Leadboard.txt");
}


//------------------------------------- init ----------------------------------
void LeadboardState::init()
{
	
	m_title = Resources::getInstance().designText({ 550,40 }, "LEADBOARD", 45);
	
	m_background.setTexture(Resources::getInstance().getBackgroud(10));
	m_leadBoardImage.setTexture(Resources::getInstance().getBackgroud(9));
	m_leadBoardImage.setPosition(450, 100);
	m_leadBoardImage.setScale(1.4, 1.4);

	beginOfLevelFiles();

}


//---------------------------- render -----------------------------------------
//print the background for help, move on the text we want to illustrate to the
//user and with sf::clock introduce hin in a typing effect way
//-----------------------------------------------------------------------------
void LeadboardState::render()
{
	m_window.clear();
	
	//if (m_prevState) m_prevState->display();
		
	m_window.draw(m_background);
	m_window.draw(m_leadBoardImage);
	m_window.draw(m_title);
	for (int i = 0; i < m_leadBoardData.size(); i++)
		m_window.draw(m_leadBoardData[i]);


	m_window.display();
}


//------------------------------waitForClick-----------------------------------
//switch from page to page in help by clicking the user on the screen
//-----------------------------------------------------------------------------

void LeadboardState::handleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { m_statesControl.popState(); return; }
			break;

		}
	}
}
//---------------------------------------------------------------
// function that loads the next level in txt file
//---------------------------------------------------------------

bool LeadboardState::readDataFromValue() 
{
	int count = 0; 
	
	if (m_leadBoardFile.eof()) return (m_leadBoardFile.eof());

	for (auto line = std::string(); std::getline(m_leadBoardFile, line) &&
		(line.compare("\0") != 0);)
	{
		if(count < MAX_LEADBOARD)
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
								  std::istream_iterator<std::string>{} };

			m_sortedScores.insert({ std::stoi(tokens[1]), tokens[0] });
			count++;
		}
	}

	return true;

}
//---------------------------------------------------------------
// function that return to start of file
//---------------------------------------------------------------
void  LeadboardState::beginOfLevelFiles()
{
	m_leadBoardFile.seekg(0, m_leadBoardFile.beg);
	if (readDataFromValue())
		setLeadboardData();
}
//---------------------------------------------------------------
void  LeadboardState::setLeadboardData()
{
	int i = 0;
	
	for ( auto iter = m_sortedScores.rbegin(); iter != m_sortedScores.rend(); ++iter, i++) {
		
		auto score = std::to_string(iter->first);
		auto finalLine = iter->second + " " + score;

		m_leadBoardData.push_back( Resources::getInstance().designText({ 580, 290 + (50 * (float)i) }, finalLine, 20, sf::Color().White));
	}

}
