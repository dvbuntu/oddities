// g++ -std=c++11 main.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <cmath>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");

	sf::Font font;
	if (!font.loadFromFile("DejaVuSans.ttf"))
		return 1;

	// create text to display
	sf::Text text("SFML!!!", font, 32);
	text.setColor(sf::Color::Black);
	// center text
	auto bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2, bounds.height / 2);
	text.setPosition(window.getDefaultView().getCenter());

	// create a stringstream for converting fps to string, and text for displaying it
	std::stringstream fps;
	sf::Text fps_text("", font, 12);
	fps_text.setColor(sf::Color(127, 127, 127));
	fps_text.setPosition(10, 10);

	sf::Clock timer; // for measuring time per frame
	sf::Clock clock; // for measuring overall time

	while (window.isOpen())
	{
		// process all input events that have occured since last frame
		sf::Event event;
		while (window.pollEvent(event))
		{
			// clicking the OS's close button or pressing escape
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			// left clicking
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				auto position = sf::Mouse::getPosition(window);
				text.setPosition(position.x, position.y);
			}
		}

		// crazy-ass transforms
		float time = clock.getElapsedTime().asSeconds();
		text.setRotation(std::sin(time) * 45);
		text.setScale(std::cos(time / 2), std::cos(time / 3));

		time = timer.getElapsedTime().asSeconds();
		timer.restart();

		// update fps text
		fps << (int)(1 / time) << " FPS";
		fps_text.setString(fps.str());
		fps.str("");

		// draw everything to the window
		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(fps_text);

		// refresh the window
		window.display();
	}

	return 0;
}
