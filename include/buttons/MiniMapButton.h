#pragma once
#include "Button.h"
#include "state/GameState.h"
#include "gui/MiniMap.h"


//mini map button
class MiniMapButton : public Button
{
public:
	MiniMapButton(GameState*, const sf::Vector2f& = { 0,0 }, const std::string& = " ", const int = BUTTON_BOX, const sf::Vector2f & = {1,1}, const bool = false);
	~MiniMapButton() = default;

	void excute(sf::RenderWindow&) override;
	void render(sf::RenderWindow&) override;     //make it const
	bool isContain(const sf::Vector2f&) override; //make it const

	void setOrginPos(sf::RenderWindow&);


private:
	bool         m_showing = true;
	MiniMap      m_minimap;
	sf::Sprite	 m_SecondButton;
	GameState*   m_game; 

};