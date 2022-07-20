#pragma once
#include <SFML/Graphics.hpp>

// directions for the movment 
enum class Direction
{
    Right,
    Left,
    Down,
    Jump,
    Attack,
    None,
};


// hold all the data that needed on movment -> first = direction enum, second -> the fitted offset
using directionData = std::pair<Direction, sf::Vector2f>;


//functions
directionData            toVector    ();
Direction                toDirection(const sf::Vector2f&);
Direction                next(Direction);