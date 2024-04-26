#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"
#include <ccomplex>
#include <cmath>
#include <sstream>
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
	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { x,y };
	m_state = CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_planeSize = { x,y };

	m_state = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_planeCenter = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
	stringstream tempStream;
	tempStream << "Mandelbrot Set" << endl << "Center: (" << m_planeCenter.x << ',' << m_planeCenter.y << ')' << endl << "Cursor: (" << m_mouseLocation.x << ',' << m_mouseLocation.y << ')' << endl << "Left-click to Zoom in" << endl << "Right-click to Zoom out";
	text.setString(tempStream.str());
}
void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		for (int i = 0; i < m_pixelSize.y; i++)
		{
			for (int j = 0; j < m_pixelSize.x; j++)
			{
				m_vArray[j + i * m_pixelSize.x].position = { (float)j,(float)i };
				//finish this
				int iterations = countIterations(mapPixelToCoords({ j,i }));
				Uint8 r, g, b;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[j + i * m_pixelSize.x].color = { r,g,b };
				//cout << m_vArray[j + i * m_pixelSize.y].color.r << ',' << m_vArray[j + i * m_pixelSize.y].color.g << ',' << m_vArray[j + i * m_pixelSize.y].color.b << ' ';
				//cout << (int)r << ',' << (int)g << ',' << (int)b << ' ';
			}
			cout << endl;
		}
		m_state = DISPLAYING;
	}
}
int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z(0, 0);
	for (int i = 0; i < MAX_ITER; i++)
	{
	//	double re = -0.77568377;
	//	double im = 0.13646737;
		
		z = z * z + c;
		if (abs(z) > 2.0)
		{
			return i;
		}
		
	}
	return MAX_ITER;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count < MAX_ITER / 5)
	{
		r = 255;
		g = 0;
		b = 0;
		for (size_t i = 0; i < count; i++)
		{
			g += (255 / (MAX_ITER/5));
		}
	}
	else if (count < (MAX_ITER*2) / 5)
	{
		r = 255;
		g = 255;
		b = 0;
		for (size_t i = 0; i < count - (MAX_ITER / 5); i++)
		{
			r -= (255 / (MAX_ITER / 5));
		}
	}
	else if (count < (MAX_ITER * 3) / 5)
	{
		r = 0;
		g = 255;
		b = 0;
		for (size_t i = 0; i < count - ((2*MAX_ITER) / 5); i++)
		{
			b += (255 / (MAX_ITER / 5));
		}
	}
	else if (count < (MAX_ITER * 4) / 5)
	{
		r = 0;
		b = 255;
		g = 255;
		for (size_t i = 0; i < count - ((3 * MAX_ITER) / 5); i++)
		{
			g -= (255 / (MAX_ITER / 5));
		}
	}
	else if (count < MAX_ITER)
	{
		r = 0;
		b = 255;
		g = 0;
		for (size_t i = 0; i < count - ((4 * MAX_ITER )/ 5); i++)
		{
			r += (255 / (MAX_ITER / 5));
		}
	}
	else
	{
		r = 0;
		g = 0;
		b = 0;
	}





}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	//Vector2f temp(((mousePixel.x - 0) / (m_pixelSize.x - 0)) * m_planeSize.x + (m_planeCenter.x - m_planeSize.x / 2.0), ((mousePixel.y - m_pixelSize.y) / (0 - m_pixelSize.y)) * m_planeSize.y + (m_planeCenter.y - m_planeSize.y / 2.0));
	float x = ((mousePixel.x - 0) / static_cast<float>(m_pixelSize.x - 0)) * m_planeSize.x + (m_planeCenter.x - m_planeSize.x / 2.0f);
	float y = (m_pixelSize.y != 0) ? ((mousePixel.y - m_pixelSize.y) / static_cast<float>(0 - m_pixelSize.y)) * m_planeSize.y + (m_planeCenter.y - m_planeSize.y / 2.0f) : 0.0f;
	return { x, y };
}