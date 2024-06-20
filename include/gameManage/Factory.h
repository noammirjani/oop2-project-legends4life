#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "GameObject.h"
#include "box2d/box2d.h"

//FACTORY - template class, manage the building of the objects
//			used while the level is being set
template <class T_OBJECT>
class Factory
{
public:									 // num in resourse      position     the rect for animation
	using pFnc = std::unique_ptr<T_OBJECT>(*)(std::unique_ptr<b2World>&, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	static std::unique_ptr<T_OBJECT> create  (const std::string&, std::unique_ptr<b2World>&, const int, const sf::Vector2f&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	static bool registerit(const std::string&, pFnc);

private:
	static auto& getMap();
};


//------------------------------------ GETMAP ---------------------------------
//
template <class T_OBJECT>
auto& Factory<T_OBJECT>::getMap()
{
	static std::map<std::string, pFnc> map;
	return map;
};


//------------------------------------ CREATE ---------------------------------
//
template <class T_OBJECT>
std::unique_ptr<T_OBJECT> Factory<T_OBJECT>::create(const std::string& name,
													std::unique_ptr<b2World>& world,
													const int resourcesIndex,
													const sf::Vector2f& position, 
													const sf::IntRect& rect,
	                                                const sf::Vector2f& frameLimit,
													const sf::Vector2f& bodySize,
	                                                const sf::Vector2f& offsetBody)
{
	auto it = Factory::getMap().find(name);

	if (it == Factory::getMap().end())
	{
		return nullptr;
	}

	return it->second(world, resourcesIndex, position, rect, frameLimit, bodySize, offsetBody);
}


//------------------------------------ REGESTER IT ----------------------------
//
template <class T_OBJECT>
bool Factory<T_OBJECT>::registerit(const std::string& name, pFnc f) {
	Factory::getMap().emplace(name, f);
	return true;
}
