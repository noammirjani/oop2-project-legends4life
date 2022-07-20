#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "macros.h"
#include "state/StateController.h"
#include "GameManage/Direction.h"



//Button Base Class
class Button
{
public:
	//c-tor, d-tor
	Button(const sf::Vector2f & = { 0,0 }, const std::string & = std::string(), const int = BUTTON_BOX, const sf::Vector2f & = { 1,1 }, const bool = false);
	virtual ~Button() = default;

	//set 
	virtual void setButton(const unsigned int) {}
	void setDesign(sf::Color, const int, const int = -120);
	void setButtons(const sf::Vector2f&, const std::string&, const int, const sf::Vector2f&);
	virtual void HandleHover(const sf::Vector2f&);

	//virtual
	virtual void update(Direction&) {}
	virtual void render(sf::RenderWindow&);
	virtual bool isContain(const sf::Vector2f&);
	virtual void excute(sf::RenderWindow&);
	virtual void setOrginPos(sf::RenderWindow&) {}

	//aux
	virtual void ClickedButton(StateController&);

protected:
	sf::Sprite	 m_button;
	const int    m_spriteNum;

private:
	//private members
	sf::Text	 m_text;
	const bool   m_hasPressedSprite;
};