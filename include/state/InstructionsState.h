#pragma once
#include <SFML/Graphics.hpp>
#include "StateController.h"
#include "State.h"
#include "macros.h"
#include "Resources.h"
#include "buttons/Button.h"
#include "BaseMenuState.h"

//instructions state
class InstructionsState : public BaseMenuState
{
public:
	InstructionsState(StateController&, sf::RenderWindow&);
	~InstructionsState() = default; 

	void init()         override;
	void render()       override;
	void handleClickEvent() override; 


private:
	sf::Vector2i  m_currFrame; 
};