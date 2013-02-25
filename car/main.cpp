#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "car.hpp"

using std::cerr;

int main()
{
	// load resources
	sf::Font font;
	if (!font.loadFromFile("DejaVuSans.ttf"))
	{
		cerr << "Couldn't find font DejaVuSans.ttf!\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulator");
	window.setVerticalSyncEnabled(true);
	sf::View view = window.getDefaultView();
	sf::Color background(22, 22, 22);

	sf::Clock clock;

	// game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::Left:
						break;
					case sf::Keyboard::Right:
						break;
					case sf::Keyboard::Up:
						break;
					case sf::Keyboard::Down:
						break;
					default:
						break;
				}
			}
		}

		// frame-time-dependent stuff
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		// draw
		window.clear(background);

		window.display();
	}

	return 0;
}
