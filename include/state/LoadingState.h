#pragma once
#include "State.h"
#include "Resources.h"
#include "StateController.h"
#include "MainMenuState.h"


//loading state
class LoadingState : public State
{
public:
	LoadingState(StateController&, sf::RenderWindow&, const int);
	~LoadingState() = default;

	void init() override;
	void render() override;
	void changeState();
	void handleEvents() override{}
	void update() override{}


private:
	const int m_loadingScreen; 

};