#pragma once
#include "state/BaseMenuState.h"


// victory & defeat 
class VictoryAndDefeatState : public BaseMenuState
{
public:
	VictoryAndDefeatState(StateController&, sf::RenderWindow&, const int&, const unsigned int, const bool, std::string&, unsigned int&, const int, const bool);
	~VictoryAndDefeatState() {}

	void init() override;
	void render() override;
	void update() override;

private:
	const int m_timer;
	const unsigned int m_score;
	sf::Sprite m_defeat, m_victory;
	bool m_gameEndMode;

};