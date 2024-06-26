// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

//class RainbowScreen : public Drawable
//{
//public:
//	RainbowScreen(int pixelWidth, int pixelHeight);
//	void draw(RenderTarget& target, RenderStates states) const override;
//	void update();
//private:
//	VertexArray m_va;
//	Vector2i m_pixel_size;
//};
//
//void RainbowScreen::update()
//{
//	int pixelHeight = m_pixel_size.y;
//	int pixelWidth = m_pixel_size.x;
//
//	for (int i = 0; i < pixelHeight; i++)
//	{
//		//random color for each row
//		Uint8 r, g, b;
//		r = rand() % 256;
//		g = rand() % 256;
//		b = rand() % 256;
//		for (int j = 0; j < pixelWidth; j++)
//		{
//			m_va[i * pixelWidth + j].position = { (float)j, (float)i };
//			m_va[i * pixelWidth + j].color = { r,g,b };
//		}
//	}
//}
//
//RainbowScreen::RainbowScreen(int pixelWidth, int pixelHeight)
//{
//	m_pixel_size = { pixelWidth, pixelHeight };
//	m_va.setPrimitiveType(Points);
//	m_va.resize(pixelWidth * pixelHeight);
//}
//
//void RainbowScreen::draw(RenderTarget& target, RenderStates states) const
//{
//	target.draw(m_va);
//}

int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width/2;
	int pixelHeight = VideoMode::getDesktopMode().height/2;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	
	//resize window for different resolutions
	//View view;
	//view.setSize(pixelWidth, pixelHeight);
	//view.setCenter(pixelWidth / 2, pixelHeight / 2);
	//window.setView(view);
	
	//RainbowScreen rain(pixelWidth, pixelHeight);

	//bool update = true;


	ComplexPlane real( pixelWidth, pixelHeight );

	Text text;

	

	Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font); // font is a Font
	text.setCharacterSize(24); // in pixels, not points!
	text.setFillColor(Color::White);
	

	//Vector2i mousePosition = Mouse::getPosition(window);

	//real.loadText(text);





	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Right)
				{
					//		std::cout << "the left button was pressed" << std::endl;
					//		std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					//		std::cout << "mouse y: " << event.mouseButton.y << std::endl;

							//update = true;
					real.zoomOut();
					real.setCenter({ event.mouseButton.x, event.mouseButton.y });
					//real.loadText(text);
				}
				if (event.mouseButton.button == Mouse::Left)
				{
					//		std::cout << "the left button was pressed" << std::endl;
					//		std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					//		std::cout << "mouse y: " << event.mouseButton.y << std::endl;

							//update = true;
					real.zoomIn();
					real.setCenter({event.mouseButton.x, event.mouseButton.y});
					//real.loadText(text);
				}
				
			}
		}
		if (Event::MouseMoved)
		{
			real.setMouseLocation({ event.mouseMove.x, event.mouseMove.y });
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		real.updateRender();
		real.loadText(text);
		/*
		****************************************
		Update the scene
		****************************************
		*/
		//if (update)
		//{
		//	//rain.update();
		//	update = false;
		//}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		//window.draw(rain);
		window.draw(real);
		window.draw(text);

		window.display();
	}
}