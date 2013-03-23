/* Very simple car class. Only handles acceleration and deceleration. It's very
 * hacky and rough - for example the position and size are stored in the visual
 * representation (the sf::RectangleShape) which probably isn't the best idea
 * down the road
 */

#ifndef CAR_HPP
#define CAR_HPP

#include <cstdlib>
#include <cfloat>
#include <SFML/Graphics.hpp>

// define manual and automatic control constants
#ifndef MANUAL
#define MANUAL 0
#endif

#ifndef AUTOMATIC1
#define AUTOMATIC1 1
#endif

#ifndef NUM_CONTROL_TYPES
#define NUM_CONTROL_TYPES 2 // hard-coded, easy way to automate?
#endif


class Car
{
	// 1-dimensional for now
	float vel;
	float acc;
	float trg_vel; // speed we want to go
	float brk_acc; // deceleration due to braking
	float brk_max; // max deceleration due to braking
	float max_vel; // max speed
	float max_acc; // max acceleration
	float drag_m; // drag multiplier
	float mass; // mass of vehicle in kg
	float weight; // weight of vehicle in mg * m / s^2
	float roll_r; // deceleration due to rolling resistance, constant for a given vehicle/tire types/mass
	float drag;

    unsigned char control; // manual, or type of self-driving

	sf::RectangleShape rect;
public:
	Car(const sf::Vector2f& p);

	inline float get_pos() const
	{
		return rect.getPosition().x;
	}

	inline float get_size() const
	{
		return rect.getSize().x;
	}

	inline sf::FloatRect get_rect() const
	{
		return rect.getGlobalBounds();
	}

	inline float get_vel() const
	{
		return vel;
	}

	inline float get_acc() const
	{
		return acc;
	}

	inline float get_drag() const
	{
		return drag;
	}

	void set_pos(float p)
	{
		rect.setPosition(p, rect.getPosition().y);
	}

	// set gas pedal amount between 0 and 1
	void set_gas(float g);
	// set brake pedal amount between 0 and 1
	void set_brake(float b);
	// set control manual or automatic
	void set_control(unsigned char c);

    // get the automated velocity based on leading car
    float get_auto_vel(Car leader);

	// advance simulation
	void step(float time);

	inline void draw_on(sf::RenderWindow& window) const
	{
		window.draw(rect);
	}
};

#endif
