/* This is a really rough simulation of a car. It's 1 dimensional, there are no
 * collisions, and the car's behavior in terms of gas and brakes are 100% made
 * up on the spot - though they're kind of decent at mimicking real car
 * behavior.
 *
 * In the 1-D case it should be easy enough to implement basic car behavior.
 * Cars could be stored sorted in a list, making it easy for a car to respond
 * to the one ahead of it
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "car.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::rand;

int main()
{
	std::srand(std::time(nullptr));

	// load resources
	sf::Font font;
	if (!font.loadFromFile("../resources/DejaVuSans.ttf"))
	{
		cerr << "Couldn't find font DejaVuSans.ttf!\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulator");
	window.setVerticalSyncEnabled(true);
	sf::View view = window.getDefaultView();
	view.zoom(0.1);
	window.setView(view);

	float width = view.getSize().x;
	float right = width / 2 + view.getCenter().x;

	sf::Text stats("", font, 12);
	stats.setColor(sf::Color::White);

	std::stringstream stat_s;

	sf::Color background(22, 22, 22);

	Car car(view.getCenter());

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
						car.set_gas(0);
						break;
					case sf::Keyboard::Right:
						car.set_gas(1);
						break;
					case sf::Keyboard::Up:
						car.set_brake(0);
						break;
					case sf::Keyboard::Down:
						car.set_brake(1);
						break;
					default:
						break;
				}
			}
		}

		// frame-time-dependent stuff
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		// wrap car around screen
		if (car.get_pos() > right)
			car.set_pos(car.get_pos() - width - car.get_size());

		car.step(time);

		// draw
		window.clear(background);

		car.draw_on(window);

		// draw car stats
		window.setView(window.getDefaultView());

		stat_s.str("");
		stat_s << car.get_vel() << " m/s";
		stats.setString(stat_s.str());
		stats.setPosition(10, 10);
		window.draw(stats);

		stat_s.str("");
		stat_s << car.get_acc() << " m/s^2";
		stats.setString(stat_s.str());
		stats.setPosition(10, 22);
		window.draw(stats);

		stat_s.str("");
		stat_s << car.get_drag() << " m/s^2";
		stats.setString(stat_s.str());
		stats.setPosition(10, 34);
		window.draw(stats);

		window.setView(view);

		window.display();
	}

	return 0;
}
