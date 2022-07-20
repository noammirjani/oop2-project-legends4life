#pragma once
#include <SFML/Graphics.hpp>
#include "state/BaseMenuState.h"
#include "state/GameState.h"
#include "state/StateController.h"
#include "state/InstructionsState.h"
#include "buttons/Button.h"
#include <memory>
#include "buttons/StateButton.h"
#include "state/SettingsState.h"


//buttons location 
const auto MULT_POS = sf::Vector2f(565, 380);
const auto SINGLE_POS = sf::Vector2f(565, 490);
const auto HELP_POS = sf::Vector2f(565, 600);
const auto EXIT_POS = sf::Vector2f(565, 710);


//main menu state
class MainMenuState : public BaseMenuState
{
public:
	MainMenuState(StateController&, sf::RenderWindow&);
	~MainMenuState() {}

	void init()   override;
	void resume() override;
	void render() override;
	void update() override;
	void handleEvents() override;
	void display()      override;

private:
	bool m_TitleInPlace;
	sf::Sprite m_title; 
};