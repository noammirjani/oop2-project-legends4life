#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Button.h"
#include "../gameManage/Animation.h"


//choose charecter button class
class ChooseCharecterButton : public Button
{
public:
	ChooseCharecterButton(const sf::Vector2f&, bool&, int, unsigned int&, const int, const std::string, std::string&, bool&);
	~ChooseCharecterButton() {}

	//virtual
	void render(sf::RenderWindow&) override;
	void excute(sf::RenderWindow&) override;
	void update(Direction&)        override;
	bool isContain(const sf::Vector2f&) override;

private:
	bool& m_successChoose;
	unsigned int& m_chosenIndex;
	const unsigned int m_myIndex;
	sf::RectangleShape m_border;
	sf::Sprite m_charecter;
	Animation m_animation;
	const std::string m_myName;
	std::string& m_charecterName;
	bool& m_defualtName;
};