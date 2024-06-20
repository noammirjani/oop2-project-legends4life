#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "macros.h"


class Resources
{
public:
	//get to the data 
	static Resources& getInstance();

	//D-tor
	~Resources();

	//get functions
	sf::Texture& getLevelIcon(int);
	sf::Texture& getBackgroud(int);
	sf::Texture& getButtons(int);
	sf::Font& getFont();
	sf::Text designText(const sf::Vector2f&, std::string, unsigned int = 40, const sf::Color & = MENU_BUTTONS_TEXT);
	std::string designTimer(const int time);
	sf::Texture& getIcon(const int);
	sf::Image getGameIcon();
private:
	//  TEXT 
	sf::Font                        m_font;

	//  TEXTURE
	std::vector <sf::Texture>       m_backgrounds;
	std::vector <sf::Texture>       m_icons;
	std::vector <sf::Texture>       m_buttons;
	std::vector <sf::Texture>       m_LevelICons;

	//PRIVATE
	//c-tor, copy-c-tor, operator=
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;

	//set functions
	void setButtons();
	void setBackground();
	void setTextureIcons();
	void setFont();
	void setLevelIcons();
};