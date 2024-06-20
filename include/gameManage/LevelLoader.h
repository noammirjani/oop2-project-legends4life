#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "StaticObjects/StaticObject.h"
#include "MovingObject/MovingObject.h"
#include "CheckPoint.h"
#include "MovingObject/Player.h"
#include "box2d/box2d.h"
#include <memory>
#include <fstream>
#include <sstream>

using moveAndStaticVec = std::pair < std::vector<std::unique_ptr<StaticObject>>, std::vector<std::unique_ptr<MovingObject>>>;
using objectsVectors = std::pair <std::unique_ptr<Player>, moveAndStaticVec>;


// LEVEL LOADER  - manage levels' files, SINGLESTON DEISGN PATTERN
class LevelLoader
{
public:
	//get to the data 
	static LevelLoader& getInstance();

	// d-tor
	~LevelLoader() {}

	//FUNCTIONS
	objectsVectors setMap(std::unique_ptr<b2World>&, const unsigned, const int);


private:

	//PRIVATE
    //c-tor, copy-c-tor, operator=
	LevelLoader() {}
	LevelLoader(const LevelLoader&)            = default;
	LevelLoader& operator=(const LevelLoader&) = default;

	// open file
	std::ifstream  openFile(const unsigned);

	std::vector < sf::Vector2f > initCheckPointCoordinate(std::istringstream&);
	// get
	sf::String   getName          (std::istringstream&) const;
	int          getIndex         (std::istringstream&) const;
	sf::Vector2f getCoordinate    (std::istringstream&) const;
	sf::IntRect  getRect          (std::istringstream&) const;

};

