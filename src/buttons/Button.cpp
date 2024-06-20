#include "buttons/Button.h"


//----------------------------- CONSTRUCTOR -----------------------------------
Button::Button(const sf::Vector2f& location, const std::string& text, const int buttonType, const sf::Vector2f& scale, const bool hasPressedSprite)
	:m_spriteNum(buttonType), m_hasPressedSprite(hasPressedSprite)
{
	setButtons(location, text, buttonType, scale);
}


//----------------------------- excute ----------------------------------------
void Button::excute(sf::RenderWindow& window)
{
	if (m_text.getString() == "EXIT") window.close();
}


//----------------------------- setDesign --------------------------------------
void Button::setDesign(sf::Color color, const int size, const int move)
{
	m_text.setColor(color);
	m_text.setCharacterSize(size);
	m_text.move(move, 0);
}

//------------------------------ set Background -------------------------------
//set the background of the menu (and volume)
//-----------------------------------------------------------------------------
void Button::setButtons(const sf::Vector2f& location, const std::string& text, const int buttonType, const sf::Vector2f& scale)
{
	m_button.setPosition(location);
	m_button.setTexture(Resources::getInstance().getButtons(buttonType));
	m_button.setScale(scale);

	sf::Vector2f offset(0, 0);
	if (text.size() <= 4) offset = { 150.f, 15.f };
	if (text.size() == 5) offset = { 14.f, 15.f };
	if (text.size() > 5) offset = { 20.f, 15.f };

	m_text = Resources::getInstance().designText(location + offset, text);
	m_text.setOutlineThickness(6);
	m_text.setOutlineColor(CLEAR);
}



//--------------------------------- draw --------------------------------------
void Button::render(sf::RenderWindow& window)
{
	window.draw(m_button);
	window.draw(m_text);
}


//---------------------------------- isContain --------------------------------
// returns if the location is contains in the button
//-----------------------------------------------------------------------------
bool Button::isContain(const sf::Vector2f& location)
{
	return m_button.getGlobalBounds().contains(location);
}


//----------------------------------- HandleHover -----------------------------
// how the text will look in the buttons
//-----------------------------------------------------------------------------
void Button::HandleHover(const sf::Vector2f& location)
{
	if (isContain(location))
	{
		m_text.setOutlineColor(MENU_BUTTONS_TEXTURE);
	}
	else
	{
		m_text.setOutlineColor(CLEAR);
	}
}


//---------------------------------- ClickesButton ----------------------------
void Button::ClickedButton(StateController& states)
{
	Audio::getInstance().playSoundEffect(BUTTONCLICK);
	if (!m_hasPressedSprite) return;

	m_button.setTexture(Resources::getInstance().getButtons((int)m_spriteNum + 1));
	states.render();
	sf::sleep(sf::milliseconds(90));
	m_button.setTexture(Resources::getInstance().getButtons((int)m_spriteNum));
	states.render();
}
