#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

const float maxFiller = 13.f; 

//life status bar -> the bar that found above the players/enemies => stamina bar
class LifeStatusBar
{
public:
	LifeStatusBar(const sf::IntRect fillerRect, const int maxData, const int bodySize);
	~LifeStatusBar() {}

	void draw(sf::RenderWindow&, const sf::Vector2f&, const int);

private:
	sf::Sprite m_bar, m_filler; 
	const int m_maxData;
	const int m_bodySize; 

};