#include "gui/MiniMap.h"
#include "state/GameState.h"

//---------------------------------- constructor ------------------------------
MiniMap::MiniMap(const sf::View stansdaetView, const sf::Vector2u& windowSize)
	: m_miniMapView(stansdaetView)
{
	init(stansdaetView, windowSize);
}


//------------------------------------ draw -----------------------------------
void MiniMap::render(sf::RenderWindow& window, GameState* world)
{
	sf::View standartView = window.getView();

	window.setView(m_miniMapView);
	world->renderGameBase();

	window.setView(standartView);
}


//------------------------------------ init -----------------------------------
void MiniMap::init(const sf::View stansdaetView, const sf::Vector2u& windowSize)
{
	if (m_miniMapView.getViewport() == sf::FloatRect(0.f, -0.38f, 1.f, 1.f)) return;
	m_miniMapView.setViewport(sf::FloatRect(0.f, -0.38f, 1.f, 1.f));
	m_miniMapView.zoom(8.3);
}