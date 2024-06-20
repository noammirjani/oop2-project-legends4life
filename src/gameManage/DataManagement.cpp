#include "gameManage/DataManagement.h"
#include <iostream>
#include "box2d/box2d.h"


//-----------------------------------------------------------------------------
DataManagement::DataManagement(const std::string& playerName, const unsigned int playerAvatar, PlayerStatus* playerStatus)
	: m_statusBar(playerStatus), m_resourcesPlayer(playerAvatar + 18)
{}


//-----------------------------------------------------------------------------
void DataManagement::setWorld(std::unique_ptr<b2World>& world ,const unsigned level)
{
	auto currVectors = LevelLoader::getInstance().setMap(world,level, m_resourcesPlayer);

	m_staticObjects = std::move(currVectors.second.first);
	m_movingObjects = std::move(currVectors.second.second);

	m_player = std::move(currVectors.first);
	m_player->setAvatarSprite(m_resourcesPlayer - 18);
}


//-----------------------------------------------------------------------------
void DataManagement::update(std::unique_ptr<b2World>& world)
{

	for ( auto& obj : m_movingObjects)
	{
		obj->update(world);
	}
	m_player->update(world);
	m_statusBar->update(); 
}


//-----------------------------------------------------------------------------
void DataManagement::draw(sf::RenderWindow& window)
{

	for (const auto& obj : m_staticObjects)
	{
		obj->draw(window);
	}

	for (const auto& obj : m_movingObjects)
	{
		obj->draw(window);
	}

	m_player->draw(window);
	m_statusBar->draw(window, m_player->getLifesNum(), m_player->getCoinNum(), m_player->getEnergyNum(), m_player->getEffectType());
}


//-----------------------------------------------------------------------------
void DataManagement::move()
{
	for (const auto& obj : m_movingObjects)
	{
		obj->move(); 
	}
	m_player->move();
}


//--------------------------------------------------------------------------------
// * This function passes over the vector of the staticObject and *
// * When a collision occurs that requires the object to disappear* 
// * the flag lights up And deletes according to the flag         *
//--------------------------------------------------------------------------------
void DataManagement::eraseObject(std::unique_ptr<b2World>& world)
{
	eraseStaticObject(world);
	eraseMovingObject(world);
}


//--------------------------------------------------------------------------------
void DataManagement::eraseStaticObject(std::unique_ptr<b2World>& world) {

	//Erases all elements that isDisposed() is true
	for (const auto& obj : m_staticObjects)
	{
		if (obj->getIsBodyDisposed())
			obj->destroyBody(world);
	}

	std::erase_if(m_staticObjects, [](auto& unmovable)
		{
			return unmovable->getIsSpriteDisposed();
		});
}


//--------------------------------------------------------------------------------
void DataManagement::eraseMovingObject(std::unique_ptr<b2World>& world) {

	//Erases all elements that isDisposed() is true
	for (const auto& movable : m_movingObjects)
	{
		if (movable->getIsSpriteDisposed())
			movable->destroyBody(world);
	}

	std::erase_if(m_movingObjects, [](auto& movable)
		{
			return movable->getIsSpriteDisposed();
		});

}


//-----------------------------------------------------------------------------
sf::Vector2f DataManagement::getPlayerPos() const
{
	return m_player->getPos();
}


//-----------------------------------------------------------------------------
void DataManagement::renderMinimapObj(sf::RenderWindow& window)
{
	for (const auto& obj : m_staticObjects)
	{
		obj->draw(window);
	}

	m_player->drawAvatar(window);
}


//-----------------------------------------------------------------------------
unsigned int DataManagement::getTotalScore() const
{
	return m_player->getCoinNum();
}