#include "..\..\include\state\SettingsState.h"
#include "./buttons/StateButton.h"
#include "state/MainMenuState.h"


//------------------------------------------- constructor --------------------------------------
SettingsState::SettingsState(StateController& states, sf::RenderWindow& window)
	: BaseMenuState(states, window)
{
	m_background.setTexture(Resources::getInstance().getIcon(37));
	m_background.setTextureRect({ 1521,1,1545,940 });
	m_background.scale(0.53, 0.53);
	m_background.setPosition(330, 290);

	m_volumeBox.setTexture(Resources::getInstance().getIcon(37));
	m_volumeBox.setTextureRect({ 3068,1, 184,40 });
	m_volumeBox.setPosition(620, 660); 
	m_volumeBox.setScale(1.5,1.5);

	m_filler.setTexture(Resources::getInstance().getIcon(37));
	m_filler.setTextureRect({ 3254,1, 51,106 });
	m_filler.setScale(0.4,0.4);
}


//------------------------------------------- init ---------------------------------------------
void SettingsState::init()
{
	addButton(std::make_unique<SoundButtons>(SoundButtons({ 900,580 },0, sf::Vector2f(0.2, 0.15), false)));
	addButton(std::make_unique<SoundButtons>(SoundButtons({ 900,480 },0, sf::Vector2f(0.2, 0.15), true)));

	addButton(std::make_unique<VolumeButton>(VolumeButton({ 620, 660}, -10)));
	addButton(std::make_unique<VolumeButton>(VolumeButton({ 862,660 }, 10)));

	addButton(std::make_unique<StateButton<MainMenuState>>(StateButton<MainMenuState>({ 1080,350 }, std::string(""), EXIT, sf::Vector2f(2, 2), false, m_statesControl, POP)));

	m_window.setView(m_window.getDefaultView()); 
}

 
//------------------------------------------- render ---------------------------------------------
void SettingsState::render()
{
	m_window.clear();

	m_prevState->display();
	m_window.draw(m_background);

	m_window.draw(m_volumeBox);
	for (auto i = 0; i < Audio::getInstance().getVolume() / 10; ++i)
	{
		m_filler.setPosition(660+ (20 * i), 670);
		m_window.draw(m_filler);
	}

	for (const auto& button : m_menuButtons) button->render(m_window);

	m_window.display();
}