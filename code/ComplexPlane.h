#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State
{
	CALCULATING,
	DISPLAYING
};


class ComplexPlane : public Drawable
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight); //: public Drawable();
//	~ComplexPlane : public Drawable();
	void draw(RenderTarget& target, RenderStates states) const;
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void setMouseLocation(Vector2i mousepixel);
	void loadText(Text& text);
	void updateRender();
private:
	int countIterations(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoords(Vector2i mousePixel);

	VertexArray m_vArray;
	State m_state;
	Vector2f m_mouseLocation;
	Vector2i m_pixelSize;
	Vector2f m_planeCenter;
	Vector2f m_planeSize;
	int m_zoomCount;
	float m_aspectRatio;
};


