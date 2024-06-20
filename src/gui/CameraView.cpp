#include "gui/CameraView.h"
#include <iostream>


//------------------------------ CONSTRUCTOR ----------------------------------
CameraView::CameraView(sf::RenderWindow& windowView, const float moveSpeed)
	: m_WindowView(windowView), m_mapScrollSpeed(moveSpeed)
{
	setZoom(0.8f);
}


//------------------------------------- setZoom -------------------------------
void CameraView::setZoom(const float scale)
{
	sf::View view = m_WindowView.getView();
	//view.zoom(scale);
	view.setCenter(750, 550);
	view.setSize(1500, 800); 
	m_WindowView.setView(view);
}


//------------------------------------- setView -------------------------------
void CameraView::setView(const sf::Vector2f mainObjPosition)
{
	auto view = m_WindowView.getView();

	auto x = setCenter(mainObjPosition.x, 750.f, 4200.f, 750.f, 4200.f, m_WindowView.getSize().x / 3.f, view.getCenter().x);
	auto y = setCenter(mainObjPosition.y, 400.f, 730.f, 730.f, 400.f, m_WindowView.getSize().y / 3.f, view.getCenter().y);

	view.setCenter(x, y);

	m_WindowView.setView(view);

}


//------------------------------------- setCenter -----------------------------
float CameraView::setCenter(const float objPos, const float centerMin, const float centerMax, const float defualtMin, const float defualtMax, const float offset, const float curCenter)
{
	//dill with overflow or underflow
	if (objPos > centerMax || objPos < centerMin)
	{
		if (objPos > curCenter - 800.f && objPos < curCenter + 800.f) return curCenter;

		if (objPos > centerMax) return defualtMax;
		else  return defualtMin;
	}

	return objPos;
}