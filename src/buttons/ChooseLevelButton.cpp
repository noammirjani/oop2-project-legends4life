#include "buttons/ChooseLevelButton.h"


//------------------------------------ constructor -----------------------------
ChooseLevelButton::ChooseLevelButton(const sf::Vector2f& pos, bool& isChosedlvl, int myIndex, unsigned int& chosenIndex, const int resourseIndex)
	: m_buttonBackground({120}) ,Button(pos), m_successChoose(isChosedlvl), m_myIndex(myIndex), m_chosenIndex(chosenIndex)
{
	m_levelIcon.setTexture(Resources::getInstance().getLevelIcon(resourseIndex));
	m_levelIcon.setPosition(pos);
	
	auto position = sf::Vector2f(pos.x -20 , pos.y -60);
	designButton(position);
}
//--------------------------------------------------------------------------------
void ChooseLevelButton::designButton(const sf::Vector2f pos)
{
	
	m_target.   setTexture(Resources::getInstance().getLevelIcon(6));
	m_target.   setPosition(pos.x - 15, pos.y -10);
	m_target.   setScale(2.f, 2.f);
	
	m_buttonBackground.setPosition(pos);
	m_buttonBackground.setFillColor(sf::Color(251,244,218,30)); // non taken 
}

//--------------------------------- render ---------------------------------------
void ChooseLevelButton::render(sf::RenderWindow& window)
{
	if (m_chosenIndex != m_myIndex)
		m_buttonBackground.setFillColor(sf::Color(251, 244, 218, 30));

	window.draw(m_buttonBackground);
		
	if(m_chosenIndex == m_myIndex)
		window.draw(m_target);


	window.draw(m_levelIcon);
}


//--------------------------------- excute ---------------------------------------
void ChooseLevelButton::excute(sf::RenderWindow&)
{
	m_successChoose = true;
	m_chosenIndex = m_myIndex;
	m_buttonBackground.setFillColor(sf::Color(243, 218, 133)); //taken 
}

//--------------------------------- update ---------------------------------------
void ChooseLevelButton::update(Direction& dir)
{

}

//--------------------------------- update ---------------------------------------

bool ChooseLevelButton::isContain(const sf::Vector2f& loc)
{
	if (m_chosenIndex != m_myIndex) return m_buttonBackground.getGlobalBounds().contains(loc);

	return m_buttonBackground.getGlobalBounds().contains(loc);
}

