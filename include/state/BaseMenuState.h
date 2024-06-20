#pragma once
#include "State.h"
#include <vector>
#include <memory>
#include"buttons/Button.h"
#include "Macros.h"
#include "Resources.h"
#include <stdexcept>

// holds pointer to button
using ButtonPtr = std::unique_ptr<Button>;

// base menu state
class BaseMenuState : public State
{
public:
	//c-tor && d-tor
	BaseMenuState(StateController&, sf::RenderWindow&);
	virtual ~BaseMenuState() = default;

	//virtual
	virtual void init() {};

	//override
	void handleEvents() override;
	bool eventsCases();
	void update()       override {}
	void render()       override;

	//set 
	void addButton(ButtonPtr);
	void updatePos();
	void setButtons(sf::Color, const int, const int = -120, const int = 0);

	//aux
	void handleClickEvent(sf::Vector2f);

protected:
	std::vector<ButtonPtr> m_menuButtons;

private:
	//handleCollisoun
	virtual void handleClickEvent();
	void handleMouseMovedEvent();
};