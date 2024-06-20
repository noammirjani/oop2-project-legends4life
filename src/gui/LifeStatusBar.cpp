#include "gui/LifeStatusBar.h"


//--------------------------------------------- constructor ---------------------------------------
LifeStatusBar::LifeStatusBar(const sf::IntRect fillerRect, const int maxData, const int size) : m_maxData(maxData), m_bodySize(size + 15)
{
	m_bar.setTexture(Resources::getInstance().getIcon(9));
	m_bar.setTextureRect({709,1,97,13});
	m_bar.scale(0.66, 0.66); 

	m_filler.setTexture(Resources::getInstance().getIcon(9));
	m_filler.setTextureRect(fillerRect);
	m_filler.setScale(5, 0.9);
}


//--------------------------------------------- draw ----------------------------------------------
void LifeStatusBar::draw(sf::RenderWindow& window, const sf::Vector2f& charecterPos, const int currData)
{
	sf::Vector2f curPos(charecterPos.x - 30.f, charecterPos.y - m_bodySize);

	m_bar.setPosition(curPos);
	window.draw(m_bar);

	curPos += sf::Vector2f(0,-0.45);
	for (int counter = 0; counter < maxFiller * (currData / (float)m_maxData); ++counter)
	{
		m_filler.setPosition(curPos + sf::Vector2f(5 , 0) * float(counter));
		window.draw(m_filler);
	}
}
