#pragma once
#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED


// 1 meter (box2d) is more or less 64 pixels (sfml)
#define RATIO 30.0f
#define PIXELS_PER_METER RATIO

// 64 pixels (sfml) are more or less 1 meter (box2d)
#define UNRATIO (1.0F/RATIO)
#define METERS_PER_PIXEL UNRATIO

//formula to convert radians to degrees = (radians * (pi/180))
#define RADTODEG (b2_pi / 180.0)

#endif // GLOBALS_H_INCLUDED

class DebugDraw : public b2Draw
{
public:
	DebugDraw(sf::RenderWindow& window)
	{
		this->window = &window;
	};
	virtual ~DebugDraw() {};

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(vertexCount);
		sf::Vector2f pos;
		for (int32 i = 0; i < vertexCount; i++)
		{
			pos.x = vertices[i].x;
			pos.y = vertices[i].y;
			polygon.setPoint(i, pos);
			//polygon.AddPoint(vertex.x * RATIO, vertex.y * RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
		}
		polygon.setFillColor(sf::Color::Red);
		polygon.setOutlineThickness(1.0f);
		this->window->draw(polygon);
	};
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(vertexCount);
		sf::Vector2f pos;
		for (int32 i = 0; i < vertexCount; i++)
		{
			pos.x = vertices[i].x;
			pos.y = vertices[i].y;
			polygon.setPoint(i, pos);
			//polygon.AddPoint(vertex.x * RATIO, vertex.y * RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
		}
		polygon.setFillColor(sf::Color{ 111,12,184, 127 });
		polygon.setOutlineThickness(0.5f);
		//polygon.setOutlineColor(sf::Color{ 111, 12, 184 });
		this->window->draw(polygon);
	};

	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {};
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {};
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {};
	void DrawTransform(const b2Transform& xf) {};
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {};

	sf::Color B2SFColor(const b2Color& color, int alpha)
	{
		sf::Color result((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255), (sf::Uint8) alpha);
		return result;
	};

private:
	sf::RenderWindow* window;
};

/* Add to controller

//drawing  debug
	DebugDraw d(window);
	uint32 flags = b2Draw::e_shapeBit;
	d.SetFlags(flags);
	m_world.SetDebugDraw(&d);

*/

/* Add to board

void SetDebugDraw(DebugDraw* d)
	{
		m_box2dWorld.SetDebugDraw(d);
	}
*/

