#pragma once
#include "Button.h"


//page button -> fits to instructtions state
class PagesButtons : public Button
{
public:
	PagesButtons(const int maxSize, sf::Vector2i& frameCoords, const int add = 1, const sf::Vector2f& pos = { 0,0 }, const std::string& txt = "",
		const int type = 1, const sf::Vector2f& scale = { 1,1 }, const bool hasPressedSprite = false)
		: Button(pos, txt, type, scale, hasPressedSprite), m_currFrame(frameCoords), m_addFrame(add), m_frameLimit(maxSize)
	{}

	~PagesButtons() = default;

	void excute(sf::RenderWindow& window) override
	{
		auto curr = m_currFrame.x + m_addFrame;
		if (curr >= 0 && curr < m_frameLimit) m_currFrame.x += m_addFrame;
	}

private:
	const int m_addFrame;
	const int m_frameLimit;
	sf::Vector2i& m_currFrame;
};