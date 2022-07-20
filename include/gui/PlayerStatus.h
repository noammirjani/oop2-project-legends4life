#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "staticObjects/StaticAnimation.h"


//player status -> name, coins, life, kind of attack, energy
class PlayerStatus
{
public:
	PlayerStatus(const std::string & = "", const int = 10, const sf::Vector2i = { 40,40 });
	~PlayerStatus() = default;

	void clock();

	void draw(sf::RenderWindow&, const int, const int, const int, const int);
	void update();
	int getTotalTime() const;

private:
	sf::Sprite m_avatar, m_avatarBord, m_avatarSmallBord, m_bar, m_barFiller, m_typeBarBord, m_coinSprite, m_lifeSprite, m_magicEffectSprite, m_magicEffectAvatar;
	sf::Vector2i                 m_posCoords;
	sf::Text                     m_playerName;
	std::vector<StaticAnimation> m_dataAnimation;
	sf::Clock                    m_timer;
	unsigned int                 m_totalTime;
	bool                         m_runningGame;

	//init
	void init();
	void initBords();
	void initAnimationBodies();
	void initAuxCoponents();

	//fill
	void fillBar(sf::RenderWindow& window, const int data, const float maxData, const sf::Vector2f& curPos, const sf::IntRect rect);
	void fillCoinBar(sf::RenderWindow&, const int, const sf::Vector2f&);
	void fillTimerBar(sf::RenderWindow&, const sf::Vector2f&);

	//draw
	void drawBoard(sf::RenderWindow&, const sf::Vector2f&, const int);
	void drawBars(sf::RenderWindow&, const sf::Vector2f&);
	void printName(sf::RenderWindow&, const sf::Vector2f&);
};

