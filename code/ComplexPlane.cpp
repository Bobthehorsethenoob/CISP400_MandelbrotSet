#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"
#include <ccomplex>
#include <cmath>
using namespace sf;
using namespace std;

ComplexPlane /*: public Drawable*/::ComplexPlane(int pixelWidth, int pixelHeight) //: public Drawable()
{
	m_pixelSize = { pixelWidth, pixelHeight };
	m_aspectRatio = pixelHeight / (double)pixelWidth;
	m_planeCenter = { 0,0 };
	m_planeSize = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

//ComplexPlane : public Drawable::~ComplexPlane : public Drawable()
//{
//}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { x,y };
	m_state = CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { x,y };
	m_state = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousepixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}
void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		for (int i = 0; i < m_pixelSize.y; i++)
		{
			for (int j = 0; j < m_pixelSize.x; j++)
			{
				m_vArray[j + i * m_pixelSize.y].position = { (float)j,(float)i };
				//finish this
			}
		}
	}
}
int ComplexPlane::countIterations(Vector2f coord)
{

}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}