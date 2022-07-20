#include "gameManage/Direction.h"
#include <stdexcept>
#include <iostream>


//-----------------------------------------------------------------------------
Direction toDirection(const sf::Vector2f& posOffset)
{
    if(posOffset.x > 0)
        return Direction::Right;
    if(posOffset.x < 0)
        return Direction::Right;
   if (posOffset.y > 0)
       return Direction::Right;

     return Direction::None;
}


//-----------------------------------------------------------------------------
Direction next(Direction dir)
{
    switch (dir)
    {
    case Direction::Right: return Direction::Jump; 
        break;
    case Direction::Left: return Direction::Right;
        break;
    case Direction::Down: return Direction::Attack;
        break;
    case Direction::Jump:  return Direction::Down;
        break;
    case Direction::Attack: return Direction::Left;
        break;
    }

    return Direction::None;
}


//-----------------------------------------------------------------------------
directionData toVector()
{
    sf::Vector2f movmentPos = { 0,0 };

    static const std::initializer_list<std::pair<sf::Keyboard::Key, sf::Vector2f>> keyToVectorMapping =
    {
        { sf::Keyboard::Right, { 14, 0  }  },
        { sf::Keyboard::Left , { -14,0  }  },
        { sf::Keyboard::Space , { 0, 55 }  },
        { sf::Keyboard::Down , { 0, - 10 }  }
    };

    for (const auto& pair : keyToVectorMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            movmentPos += pair.second;
        }
    }

    return { toDirection(movmentPos), movmentPos };
}
