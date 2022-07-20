#include "buttons/ChooseCharecterButton.h"


//------------------------------------ constructor -----------------------------
ChooseCharecterButton::ChooseCharecterButton(const sf::Vector2f& pos, bool& isChosedAChar, int myIndex, unsigned int& chosenIndex, 
											const int resourseIndex, const std::string myName, std::string& charName, bool& isDefualt)
	: m_animation(sf::Vector2f(112.25, 86), sf::Vector2f(3, 8), m_charecter), m_border({ 300,300 }), Button(pos), m_successChoose(isChosedAChar),
	  m_chosenIndex(chosenIndex), m_myIndex(myIndex), m_myName(myName), m_charecterName(charName), m_defualtName(isDefualt)
{
	m_border.setPosition(pos);
	m_border.setFillColor(sf::Color(64, 219, 227, 50));

	m_charecter.setPosition(sf::Vector2f(pos.x -20,pos.y + 40));
	m_charecter.setOrigin(m_charecter.getGlobalBounds().width, m_charecter.getGlobalBounds().height);
	m_charecter.scale(3.f,2.f); 
	m_charecter.setTexture(Resources::getInstance().getIcon(resourseIndex));
	m_charecter.setTextureRect({3,3,112,86 });
}


//--------------------------------- render ---------------------------------------
void ChooseCharecterButton::render(sf::RenderWindow& window)
{
	window.draw(m_border);
	window.draw(m_charecter);
}


//--------------------------------- excute ---------------------------------------
void ChooseCharecterButton::excute(sf::RenderWindow&)
{
	m_border.setFillColor(sf::Color(30, 30, 30, 50));
	m_successChoose = true; 
	m_chosenIndex = m_myIndex; 
	m_charecterName = m_myName; 
	m_defualtName = true;
}

//--------------------------------- update ---------------------------------------
void ChooseCharecterButton::update(Direction& dir)
{
	m_animation.update({ dir, {0,0} });
	m_charecter.setTextureRect(m_animation.getRect()); 
	if (m_chosenIndex != m_myIndex) m_border.setFillColor(sf::Color(69, 125, 45, 50));
}


//--------------------------------- update ---------------------------------------
bool ChooseCharecterButton::isContain(const sf::Vector2f& loc)
{
	return m_border.getGlobalBounds().contains(loc); 
}