#include "Resources.h"

//-------------------------constructor------------------------------
Resources::Resources()
	: m_font()
{
	//set texture 
	setBackground();
	setButtons();
	setTextureIcons();
	setLevelIcons();

	//text
	setFont();
}


//------------------------------------------------------------------
//the static function 
Resources& Resources::getInstance()
{
	static Resources instane;
	return instane;
}


//------------------------------------------------------------------
//d_tor
Resources::~Resources() {}


//--------------------------- set backround -------------------------
void Resources::setBackground()
{
	sf::Texture texture;

	for (size_t i = 0; i < BACKGROUND_TEXTURE_NAMES.size(); i++)
	{
		texture.loadFromFile(BACKGROUND_TEXTURE_NAMES[i]);
		texture.setSmooth(true);
		m_backgrounds.emplace_back(texture);
	}
}


//--------------------------- setTextureIcons -----------------------
void Resources::setLevelIcons()
{
	sf::Texture texture;

	for (size_t i = 0; i < levelIcon.size(); i++)
	{
		texture.loadFromFile(levelIcon[i]);
		texture.setSmooth(true);
		m_LevelICons.emplace_back(texture);
	}
}

//--------------------------- setTextureIcons -----------------------
void Resources::setTextureIcons()
{
	sf::Texture texture;

	for (auto& i : iconesVecNames)
	{
		texture.loadFromFile(i);
		texture.setSmooth(true);
		m_icons.emplace_back(texture);
	}
}


//--------------------------- get icon ------------------------------
sf::Texture& Resources::getIcon(const int index)
{
	return m_icons.at(index);
}


//--------------------------- get game icon -------------------------
sf::Image Resources::getGameIcon()
{
	sf::Image icon;
	icon.loadFromFile("gameIcon.png");
	return icon;
}


//--------------------------- set backround -------------------------
void Resources::setButtons()
{
	sf::Texture texture;

	for (size_t i = 0; i < BUTTONS.size(); i++)
	{
		texture.loadFromFile(BUTTONS[i]);
		texture.setSmooth(true);
		m_buttons.emplace_back(texture);
	}
}


//----------------------------get Backgroud -------------------------
sf::Texture& Resources::getLevelIcon(int enumIcone)
{
	return (m_LevelICons[enumIcone]);
}


//--------------------------- set font ------------------------------
void Resources::setFont()
{
	m_font.loadFromFile("ButtonFont.ttf");
}


//----------------------------- get font ----------------------------
sf::Font& Resources::getFont()
{
	return m_font;
}


//----------------------------get Backgroud -------------------------
sf::Texture& Resources::getBackgroud(int enumIcone)
{
	return (m_backgrounds[enumIcone]);
}

//----------------------------get Backgroud -------------------------
sf::Texture& Resources::getButtons(int enumIcone)
{
	return (m_buttons[enumIcone]);
}


//----------------------------get Backgroud -------------------------
sf::Text Resources::designText(const sf::Vector2f& loaction, std::string textString, unsigned int size, const sf::Color& color)
{
	sf::Text text;

	text.setFont(Resources::getInstance().getFont());
	text.setString(textString);
	text.setCharacterSize(size);
	text.setLineSpacing(2);
	text.setColor(color);
	text.setStyle(1);
	text.setPosition(loaction);

	return text;
}


//--------------------------- designTimer -------------------------
std::string Resources::designTimer(const int time)
{
	auto min = (time / 60 >= 10) ? std::to_string(time / 60) : "0" + std::to_string(time / 60);
	auto sec = (time % 60 >= 10) ? std::to_string(time % 60) : "0" + std::to_string(time % 60);

	return min + ":" + sec;
}
