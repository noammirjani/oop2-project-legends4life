#include"gameManage/LevelLoader.h"
#include <iostream>


//------------------------------------------------------------------
//the stsic function 
LevelLoader& LevelLoader::getInstance()
{
	static LevelLoader instane;
	return instane;
}


//-----------------------------------  setMap ---------------------------------
objectsVectors LevelLoader::setMap(std::unique_ptr<b2World>& world, const unsigned level, const int resourcesPlayer)
{
	auto levelFile = openFile(level);

	objectsVectors UniqueVectors;
	std::string   inpLine;
	char type;
	std::getline(levelFile, inpLine);

	while (!levelFile.eof())
	{
		std::istringstream buffer(inpLine);
		buffer >> type;

		std::getline(levelFile, inpLine);
		auto name  = getName(buffer);
		auto index = getIndex(buffer);
		auto pos   = getCoordinate(buffer);
		auto rect  = getRect(buffer);
		auto frameLimit = getCoordinate(buffer);
		auto bodySize   = getCoordinate(buffer);
		auto offsetBody = getCoordinate(buffer);

		if (type == 'P') 
		{
			auto vectorOfCheckPOintPos = initCheckPointCoordinate(buffer);
			UniqueVectors.first = std::make_unique<Player> (world, CheckPoint(vectorOfCheckPOintPos) ,b2_dynamicBody, resourcesPlayer, pos, rect, frameLimit, bodySize, offsetBody);
		}
	    if (type == 'S')
		{
			UniqueVectors.second.first.emplace_back(Factory<StaticObject>::create(name, world, index, pos, rect, frameLimit, bodySize, offsetBody));
		}
	     if (type == 'M')
		{
			UniqueVectors.second.second.emplace_back(Factory<MovingObject>::create(name, world, index, pos, rect, frameLimit, bodySize, offsetBody));
		}
	}

	return UniqueVectors;
}


//-----------------------------------  openFile -------------------------------
std::ifstream LevelLoader::openFile(const unsigned level)
{
	std::ifstream  file;
	file.open("Level" + std::to_string(level) + ".txt");
	
	if (!file.is_open())
	{
		throw std::invalid_argument("file doesnt found || cannot be open");
	}

	return file; 
}
//-----------------------------------------------------------------------------
std::vector<sf::Vector2f> LevelLoader::initCheckPointCoordinate(std::istringstream& buffer)
{
	std::vector < sf::Vector2f> checkPointPosition;
	checkPointPosition.reserve(3);
	
	while (!buffer.eof())
	{
		
		checkPointPosition.push_back( getCoordinate(buffer));
	}

	return checkPointPosition;
}

//-----------------------------------  manageLine -----------------------------
//-----------------------------------  getName --------------------------------
sf::String LevelLoader::getName      (std::istringstream& buffer) const
{
	std::string name;
	buffer >> name;
	return name; 
}


//-----------------------------------  getResourceIndex -----------------------
int LevelLoader::getIndex    (std::istringstream& buffer) const
{
	int index;
	buffer >> index;
	return index;
}


//-----------------------------------  getPosition ----------------------------
sf::Vector2f LevelLoader::getCoordinate(std::istringstream& buffer) const
{
	sf::Vector2f pos; 
	buffer >> pos.x >> pos.y;
	return pos;
}


//-----------------------------------  getRect --------------------------------
sf::IntRect LevelLoader::getRect     (std::istringstream& buffer) const
{
	sf::IntRect rect;
	buffer >> rect.left >> rect.top >> rect.width >> rect.height;
	return rect;
}