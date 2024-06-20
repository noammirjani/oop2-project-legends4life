#pragma once
#include <SFML/Graphics.hpp>

class GameState;

//displying the map in mini virsion
class MiniMap
{
public:
	MiniMap(const sf::View, const sf::Vector2u&);
	MiniMap() {}
	~MiniMap() {}

	void render(sf::RenderWindow&, GameState*);
	void init(const sf::View, const sf::Vector2u&);
private:
	sf::View        m_miniMapView;

};