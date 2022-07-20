#pragma once
#include "BaseMenuState.h"
#include "buttons/SoundButtons.h"


//settings state
class SettingsState : public BaseMenuState
{
public:
	SettingsState(StateController&, sf::RenderWindow&);
	~SettingsState() = default; 

	void init()   override;
	void render() override;

private:
	sf::Sprite m_filler, m_volumeBox; 

};