#include "buttons/MiniMapButton.h"
#include "gui/MiniMap.h"


//------------------------------------------------------------ CONSTRUCTOR --------------------------------------------------------------------
MiniMapButton::MiniMapButton(GameState* gamePtr,const sf::Vector2f& pos, const std::string& txt, const int type, const sf::Vector2f& scale, const bool hasPressedSprite)
	: Button(pos, txt, type, scale, hasPressedSprite), m_minimap(), m_game(gamePtr)
{
	m_SecondButton.setTexture(Resources::getInstance().getButtons(EXIT));
	m_SecondButton.setPosition(pos);
	m_SecondButton.setScale(1.5, 1.5);
}


//------------------------------------------------------------ EXCUTE -------------------------------------------------------------------------
void MiniMapButton::excute(sf::RenderWindow & window)
{
	m_showing = !m_showing;

	if (!m_showing) { m_minimap.init(window.getView(), window.getSize()); }
}


//------------------------------------------------------------ RENDER -------------------------------------------------------------------------
void MiniMapButton::render(sf::RenderWindow & window)
{
	if (!m_showing)
	{
		m_minimap.render(window, m_game);
		window.draw(m_SecondButton);
	}
	else
	{
		Button::render(window);
	}
}


//---------------------------------------------------- SET ORGIN POS --------------------------------------------------------------------------
void MiniMapButton::setOrginPos(sf::RenderWindow & window)
{
	if (m_showing) m_button.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x - 320, 40)));
	else  m_SecondButton.setPosition(window.mapPixelToCoords(sf::Vector2i(int(window.getSize().x / 2.3), 0)));
}


//------------------------------------------------------ IS CONTAIN  --------------------------------------------------------------------------
bool MiniMapButton::isContain(const sf::Vector2f & location)
{
	if (m_showing) return m_button.getGlobalBounds().contains(location);

	return m_SecondButton.getGlobalBounds().contains(location);
}