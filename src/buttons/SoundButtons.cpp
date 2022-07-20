#include "..\..\include\buttons\SoundButtons.h"


//---------------------------------------------- sound buttons -----------------------------------------------
SoundButtons::SoundButtons(const sf::Vector2f& pos, const int type, const sf::Vector2f& scale, const bool typeOfButton)
	: Button(pos, "", type, scale, false), m_typeOfButton(typeOfButton), m_frameLimit(!Audio::getInstance().getMode(typeOfButton))
{
	m_button.setTexture(Resources::getInstance().getIcon(37));
	m_button.setTextureRect({ (m_frameLimit * 756) + 1 ,1,756,406 });
}


//------------------------------------------------------ excute -----------------------------------------------
void SoundButtons::excute(sf::RenderWindow&)
{
	m_frameLimit = (++m_frameLimit) % 2;
	Audio::getInstance().setMode(m_typeOfButton);
	m_button.setTextureRect({(m_frameLimit*756)+1 ,1,756,406});
}

void SoundButtons::ClickedButton(StateController&)
{
	if (Audio::getInstance().getMode(0))
	{
		Audio::getInstance().playSoundEffect(BUTTONCLICK);
	}
	else
	{
		// no click sound
	}
}


//---------------------------------------------- sound buttons -----------------------------------------------
VolumeButton::VolumeButton(const sf::Vector2f& pos, const int addVal)
	: Button(pos, "", 0, { 1,1 }, false), m_addVal(addVal)
{
	m_volSprite.setSize({ 35, 60 });
	m_volSprite.setFillColor(sf::Color({ 0,0,0,0 }));
	m_volSprite.setPosition(pos); 
}


//------------------------------------------------------ excute -----------------------------------------------
void VolumeButton::excute(sf::RenderWindow&)
{
	Audio::getInstance().setVolume(m_addVal);
}


//------------------------------------------------------ render -----------------------------------------------
void VolumeButton::render(sf::RenderWindow& window)
{
	window.draw(m_volSprite);
}


//------------------------------------------------------ contains -----------------------------------------------
bool VolumeButton::isContain(const sf::Vector2f& loc)
{
	return m_volSprite.getGlobalBounds().contains(loc);
}