#include "gui/PlayerStatus.h"


//------------------------------------ CONSTRUCTOR --------------------------------------
PlayerStatus::PlayerStatus(const std::string& playerName, const int typeAvatar, const sf::Vector2i pos)
	: m_posCoords(pos), m_totalTime(0), m_runningGame(true)
{
	m_timer.restart();
	m_playerName = Resources::getInstance().designText({ 0 ,0 }, playerName, 10, sf::Color::White);
	m_avatar.setTexture(Resources::getInstance().getIcon(10));
	m_avatar.setTextureRect({ ((typeAvatar - 1) * 66) + 1, 1, 64,64 });
	init();
}


//----------------------------------- init ----------------------------------------------
void PlayerStatus::init()
{
	initBords();
	initAnimationBodies();
	initAuxCoponents();
}


//----------------------------------- update ----------------------------------------------
void PlayerStatus::update()
{
	for (auto& anim : m_dataAnimation) anim.update();

	if (m_runningGame && m_timer.getElapsedTime() >= sf::seconds(1))
	{
		m_totalTime++;
		m_timer.restart();
	}
}


//------------------------------- get timer ---------------------------------------------
int PlayerStatus::getTotalTime() const
{
	return m_totalTime;
}


//------------------------------- stopClock ---------------------------------------------
void PlayerStatus::clock()
{
	m_runningGame = !m_runningGame;
}


//----------------------------------- draw ----------------------------------------------
void PlayerStatus::draw(sf::RenderWindow& window, const int playerLives, const int coinsNum, const int powerNum, const int effectIndex)
{
	sf::Vector2f curPos = window.mapPixelToCoords(m_posCoords);

	//draw board, avatar
	drawBoard(window, curPos, effectIndex % 3);

	//draw bars
	drawBars(window, curPos);

	//fill data
	printName(window, curPos);
	fillBar(window, playerLives, 3, curPos + lifeFillerOffset, RedFillerHp);
	fillBar(window, powerNum, 100, curPos + energyFillerOffset, BlueFillerHp);
	fillCoinBar(window, coinsNum, curPos);
	fillTimerBar(window, curPos);
}


//------------------------------- printName ---------------------------------------------
void PlayerStatus::printName(sf::RenderWindow& window, const sf::Vector2f& curPos)
{
	m_playerName.setPosition(curPos + nameOffset);
	window.draw(m_playerName);
}


//------------------------------- timer -------------------------------------------------
void PlayerStatus::fillTimerBar(sf::RenderWindow& window, const sf::Vector2f& curPos)
{
	window.draw(Resources::getInstance().designText(curPos + timerOffset, Resources::getInstance().designTimer(m_totalTime), 14, sf::Color::White));
}


//--------------------------------- setPos ----------------------------------------------
void PlayerStatus::drawBoard(sf::RenderWindow& window, const sf::Vector2f& curPos, const int effectIndex)
{
	m_avatarBord.setPosition(curPos);
	m_avatar.setPosition(curPos + avatarOffset);

	window.draw(m_avatarBord);
	window.draw(m_avatar);

	m_avatarSmallBord.setPosition(curPos + littleBord);
	m_magicEffectAvatar.setPosition(curPos + magicEffectAvatarOffset);
	m_magicEffectAvatar.setTextureRect({ 66 * effectIndex, 1, 66, 66 });

	window.draw(m_avatarSmallBord);
	window.draw(m_magicEffectAvatar);
}


//----------------------------------- fillLBar ------------------------------------------
void PlayerStatus::fillBar(sf::RenderWindow& window, const int data, const float maxData, const sf::Vector2f& basePos, const sf::IntRect rect)
{
	m_barFiller.setTextureRect(rect);

	for (int counter = 0; counter < maxFillerSize * (data / maxData); ++counter)
	{
		m_barFiller.setPosition(basePos + sf::Vector2f(1.5, 0) * float(counter));
		window.draw(m_barFiller);
	}
}


//------------------------------------ fill coin bar ------------------------------------
void PlayerStatus::fillCoinBar(sf::RenderWindow& window, const int coinNum, const sf::Vector2f& curPos)
{
	auto pos = curPos;

	if (coinNum == 0)       pos += sf::Vector2f(150, 67);
	else if (coinNum < 1000) pos += sf::Vector2f(140, 67);
	else                    pos += sf::Vector2f(119, 67);

	window.draw(Resources::getInstance().designText(pos, std::to_string(coinNum * 100), 14, sf::Color::White));
}


//----------------------------------- init ----------------------------------------------
void PlayerStatus::initBords()
{
	//big bord
	m_avatarBord.setTexture(Resources::getInstance().getIcon(9));
	m_avatarBord.setTextureRect(bigBord);
	//smalll bar
	m_avatarSmallBord.setTexture(Resources::getInstance().getIcon(9));
	m_avatarSmallBord.setTextureRect(bigBord);
	m_avatarSmallBord.scale(0.5, 0.5);
	//hp bar
	m_bar.setTexture(Resources::getInstance().getIcon(9));
	m_bar.setTextureRect(hpBar);
	//sprite bord
	m_typeBarBord.setTexture(Resources::getInstance().getIcon(9));
	m_typeBarBord.setTextureRect(smallerBord);
	m_typeBarBord.scale(0.5, 0.5);
}


//----------------------------------- init ----------------------------------------------
void PlayerStatus::initAnimationBodies()
{
	// sprites -> coin life cristal 
	m_coinSprite.setTexture(Resources::getInstance().getIcon(2));
	m_coinSprite.setTextureRect({ 5,42,34,36 });
	m_coinSprite.scale(0.5, 0.5);

	m_lifeSprite.setTexture(Resources::getInstance().getIcon(2));
	m_lifeSprite.setTextureRect({ 3,6,34,36 });
	m_lifeSprite.scale(0.5, 0.5);

	m_magicEffectSprite.setTexture(Resources::getInstance().getIcon(2));
	m_magicEffectSprite.setTextureRect({ 3,187,34,36 });
	m_magicEffectSprite.scale(0.5, 0.5);

	//init sprites anumation for coin creistal and life 
	m_dataAnimation.emplace_back(StaticAnimation({ 34,36 }, { 1, 10 }, m_coinSprite));
	m_dataAnimation.emplace_back(StaticAnimation({ 34,36 }, { 0, 10 }, m_lifeSprite));
	m_dataAnimation.emplace_back(StaticAnimation({ 34,37 }, { 5, 10 }, m_magicEffectSprite));
}


//----------------------------------- init ----------------------------------------------
void PlayerStatus::initAuxCoponents()
{

	//other sprites
	m_barFiller.setTexture(Resources::getInstance().getIcon(9));
	m_magicEffectAvatar.setTexture(Resources::getInstance().getIcon(16));
	m_magicEffectAvatar.scale(0.5, 0.5);

}


//--------------------------------- setPos ----------------------------------------------
void PlayerStatus::drawBars(sf::RenderWindow& window, const sf::Vector2f& curPos)
{
	//the name bar
	m_bar.setPosition(curPos + nameBarOffset);
	m_typeBarBord.setPosition(curPos + name);
	window.draw(m_bar);
	window.draw(m_typeBarBord);

	//the life bar
	m_lifeSprite.setPosition(curPos + life);
	m_bar.setPosition(curPos + lifeBarOffset);
	m_typeBarBord.setPosition(curPos + life);
	window.draw(m_bar);
	window.draw(m_typeBarBord);
	window.draw(m_lifeSprite);

	//the energy bar
	m_bar.setPosition(curPos + energyBarOffset);
	m_typeBarBord.setPosition(curPos + energy);
	m_magicEffectSprite.setPosition(curPos + energy);
	window.draw(m_bar);
	window.draw(m_typeBarBord);
	window.draw(m_magicEffectSprite);

	//the coin bar
	m_bar.setPosition(curPos + coinBarOffset);
	m_typeBarBord.setPosition(curPos + coin);
	m_coinSprite.setPosition(curPos + coin);
	window.draw(m_bar);
	window.draw(m_typeBarBord);
	window.draw(m_coinSprite);

	//timer
	m_bar.setPosition(curPos + timerBarOffset);
	m_typeBarBord.setPosition(curPos + timer);
	window.draw(m_bar);
	window.draw(m_typeBarBord);
}