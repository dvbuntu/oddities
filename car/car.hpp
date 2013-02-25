#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>

class Car
{
	// 1-dimensional for now
	float vel;
	float trg_vel; // speed we want to go
	float brk_acc; // deceleration due to braking
	float brk_max; // max deceleration due to braking
	float max_vel; // max speed
	float max_acc; // max acceleration
	sf::RectangleShape rect;
public:
	Car(const sf::Vector2f& p);

	inline float get_pos() const
	{
		return rect.getPosition().x;
	}

	// set gas pedal amount between 0 and 1
	void set_gas(float g);
	// set brake pedal amount between 0 and 1
	void set_brake(float b);

	// advance simulation
	void step(float time);

	inline void draw_on(sf::RenderWindow& window) const
	{
		window.draw(rect);
	}
};

#endif
