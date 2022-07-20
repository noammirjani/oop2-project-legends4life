#include "gameManage/CheckPoint.h"

CheckPoint::CheckPoint(const std::vector<sf::Vector2f>& checkPointPosition)
	:m_checkPointPosition(checkPointPosition)
{}


//-------------------------------------------------------------------
sf::Vector2f CheckPoint::currCheckPointPosition(const sf::Vector2f& playerPosition)
{
	int index = 0;
	float minDistnace = abs(m_checkPointPosition[0].x - playerPosition.x);

	for (auto i = 0; i < m_checkPointPosition.size(); ++i)
	{
		if (abs(m_checkPointPosition[i].x - playerPosition.x) < minDistnace && (m_checkPointPosition[i].x < playerPosition.x))
		{
			minDistnace = abs(m_checkPointPosition[i].x - playerPosition.x);
			index = i;
		}
	}
	return m_checkPointPosition[index];
}
