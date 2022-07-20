#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Button.h"

//choose level button
class ChooseLevelButton : public Button
{
public:
	ChooseLevelButton(const sf::Vector2f&, bool&, int, unsigned int&, const int);
	~ChooseLevelButton() {}

	//virtual
	void render(sf::RenderWindow&) override;
	void excute(sf::RenderWindow&) override;
	void update(Direction&)        override;
	bool isContain(const sf::Vector2f&) override;

private:
	
	void designButton(const sf::Vector2f );
	bool& m_successChoose;
	unsigned int& m_chosenIndex;
	const unsigned int m_myIndex;

	sf::Sprite			  m_target;
	sf::Sprite			  m_levelIcon;
	sf::CircleShape       m_buttonBackground;

};