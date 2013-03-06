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
#include <list>
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

	std::list<Car*> cars;
	cars.push_front(new Car(view.getCenter() - sf::Vector2f(width / 2, 0)));
	cars.push_front(new Car(view.getCenter()));

	cars.back()->set_gas(1);

	float timescale = 1;
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
					case sf::Keyboard::Space:
						timescale = 1 - timescale;
						break;
					default:
						break;
				}
			}
		}

		// frame-time-dependent stuff
		float time = clock.getElapsedTime().asSeconds() * timescale;
		clock.restart();

		// wrap cars around screen
		while (cars.front()->get_pos() > right)
		{
			cars.front()->set_pos(cars.front()->get_pos() - width - cars.front()->get_size());
			cars.push_back(cars.front());
			cars.pop_front();
		}

		// update car positions
		for (auto car : cars)
			car->step(time);

		// detect collisions
		auto pcar = cars.rbegin();
		auto pnext = cars.rbegin();
		++pnext;
		for (; pnext != cars.rend(); pcar++, pnext++)
		{
			Car& car = **pcar;
			Car& next = **pnext;
			if (car.get_rect().intersects(next.get_rect()))
			{
				cerr << "Collision at " << (car.get_vel() - next.get_vel()) << " m/s\n";
				// backup so the cars don't overlap TODO physics!?!?!?!?
				car.set_pos(next.get_pos() - car.get_size());
				// pause
				timescale = 0;
			}
		}

		// have to handle last car differently due to wrapping TODO better way?
		sf::FloatRect back_rect = cars.front()->get_rect();
		back_rect.left -= width + cars.front()->get_size();
		if (back_rect.intersects(cars.back()->get_rect()))
		{
			cerr << "Collision at " << (cars.front()->get_vel() - cars.back()->get_vel()) << " m/s\n";
			cars.front()->set_pos(cars.back()->get_pos() + width);
			timescale = 0;
		}

		// draw
		window.clear(background);

		for (auto car : cars)
			car->draw_on(window);

		// draw car stats
		window.setView(window.getDefaultView());

		unsigned int i = 0;
		for (auto pcar = cars.rbegin(); pcar != cars.rend(); pcar++)
		{
			const Car& car = **pcar;
			stat_s.str("");
			stat_s << car.get_vel() << " m/s";
			stats.setString(stat_s.str());
			stats.setPosition(10 + 200 * i, 10);
			window.draw(stats);

			stat_s.str("");
			stat_s << car.get_acc() << " m/s^2";
			stats.setString(stat_s.str());
			stats.setPosition(10 + 200 * i, 22);
			window.draw(stats);

			stat_s.str("");
			stat_s << car.get_drag() << " m/s^2";
			stats.setString(stat_s.str());
			stats.setPosition(10 + 200 * i, 34);
			window.draw(stats);
			++i;
		}

		window.setView(view);

		window.display();
	}

	return 0;
}
