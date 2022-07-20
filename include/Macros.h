#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>


//----------------------------------------------------------- BOX2D --------------------------------------------------------------------------------------------------
enum EntityCategory 
{
	playerBits = 0x0001,
	BonusBits = 0x0002,
	PaltformBits = 0x0004,
	TrapsBits = 0x0008,
	WaterBits = 0x0010,
	GroundBits = 0x0020,
	EnemyBits = 0x0040,
	MagicEffectBits = 0x0080,
	BoxBits = 0x0100,
	checkPointBits = 0x0200,
	noneBit = 0x0400,
	floorObsBit = 0x0800,
	noHandleBit = 0x1000
};

//---------------------------------------------------------- ENUMS ---------------------------------------------------------------------------------------------------
enum Sound
{
	MENU_SOUND, BUTTONCLICK, COINCOLLECT, JUMPSOUND, ATTACK, LIFESOUND, ENEMYDIE, WATERFALLING, MAGICATTAK, PLAYERDIE, WinSOUND, LoseSOUND, LEVELSound

};
enum buttons 
{
	BUTTON_BOX = 0, MINIMAP_BOX = 2, NEXT_BOX = 4, PREV_BOX = 6, GAME_BOX = 8, HOME_BOX = 10, SETTINGS = 11, EXIT = 12, LEAD = 13
};
enum backgrounds 
{ 
	OPEN, MENU, LEVEL1 
};

//------------------------------------------------------------- COLORS ----------------------------------------------------------------------------------------------
const auto MENU_BUTTONS_TEXT = sf::Color(73, 117, 112);
const auto MENU_BUTTONS_TEXTURE = sf::Color(252, 241, 239);
const auto CLEAR = sf::Color(0, 0, 0, 0);
const auto BACKSPACE = 8;
const auto MAX_NAME_LEN = 20;
const sf::Color LOBBY_LIST{ 245,174,8,120 };
const sf::Color NAME_INPUT_BOX{ 70,70,70,120 };

//------------------------------------------------------------- RESOURCES ------------------------------------------------------------------------------------------
const std::string iconesVecNames[] = { "tileset1.png", "box1.png","movingTiles.png", "FallingBlock.png","GuillotineTrap.png","goblin.png",
									   "imp.png", "boss.png","MagicEffect.png", "PlayerStatus.png", "avatar.png","yeti.png","ent.png" ,"MineTrap.png",
									   "planetMineTrap.png","WinGate.png", "MagicEffectIcons.png" , "FallingBomb.png","knight.png","nadav.png","ariel.png",
										"noam.png","efrat.png","orc.png","beholder.png","dino.png","dworf.png","box2.png","scull.png", "gameStatus.png",
									   "tileset2.png" ,"tileset3.png", "laba.png", "imp2.png", "lamp.png", "ghost.png","goneTile.png", "sound.png", "victory.png", "defeat.png","snake.png","boos2.png" };

const std::vector <std::string> levelIcon = { "levelSelect.png","mountain.png", "forest.png","dungeon.png","circleBright.png" ,"circlePale.png" ,"target.png" };

const std::vector <std::string> BACKGROUND_TEXTURE_NAMES = { "OpenScreen.png", "GameName.png", "MenuBackground.png", "board.png", "InstructionsScreen.png", "network.png","board1.png","board2.png","board3.png", "blueSky.png", "Leadboard.png" };

const std::string soundFilesName[] = { "menuMusic.wav","buttonClick.wav","coinCollect.wav","jumpSound.wav","attack.wav","bonusLifeSound.wav", "enemyDie.wav", "waterFalling.wav", "magicAttack.wav","playerDie.wav" ,"Win.wav","Lose.wav","Level1.wav","Level2.wav","Level3.wav" };

const std::vector <std::string> BUTTONS = { "ButtonBox.png", "ButtonBoxPressed.png", "MinimapButton.png", "MinimapPressed.png", "nextBotton.png", "nextButtonPressed.png", "prevButton.png", "prevButtonPressed.png",  "gameBox.png", "gamePressedBox.png", "homeBox.png", "settingsButton.png", "exit.png", "lead.png"};



//------------------------------------------------------------- PLAYER STATUS  -------------------------------------------------------------------------------------
const sf::IntRect   bigBord(631, 1, 76, 79), smallerBord(554, 1, 40, 40), hpBar(15, 1, 127, 20), staminaBar(710, 1, 343, 28),
GreenFillerHp(494, 1, 3, 16), RedFillerHp(503, 1, 3, 16), BlueFillerHp(489, 1, 3, 16), YellowFillerHp(8, 1, 3, 16);
const int maxFillerSize = 80;
const sf::Vector2f nameBarOffset(96, 5), lifeBarOffset(96, 25), energyBarOffset(96, 45), coinBarOffset(96, 65), timerBarOffset(96, 85),
nameOffset(102, 9), lifeFillerOffset(100, 27), energyFillerOffset(100, 47), magicEffectAvatarOffset(227, 9), timerOffset(120, 87),
name(76, 5), coin(76, 65), life(76, 25), energy(76, 45), timer(76, 85), littleBord(223, 5), avatarOffset(9.2, 8.5);