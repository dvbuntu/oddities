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
#include <algorithm>

// define manual and automatic control constants
#ifndef MANUAL
#define MANUAL 0
#endif

#ifndef AUTOMATIC1
#define AUTOMATIC1 1
#endif

#ifndef AUTOMATIC2
#define AUTOMATIC2 2
#endif

#ifndef CAR_LEN
#define CAR_LEN 4.55676
#endif

#ifndef CAR_WID
#define CAR_WID 1.7526
#endif

#ifndef BRK_VAR
#define BRK_VAR 2
#endif

#ifndef VEL_VAR
#define VEL_VAR 3
#endif

#ifndef ACC_VAR
#define ACC_VAR 1
#endif

#ifndef MASS_VAR
#define MASS_VAR 50
#endif

#ifndef TIME_R_VAR
#define TIME_R_VAR 0.1
#endif

/* Reaction time factor of safety
 * TODO Compute this based on accuracy of estimate to ensure
 * 99.9% safety or something
 */
#ifndef PHI
#define PHI float(1.1)
#endif

/* Vehicle length factor of safety
 * TODO See if we really need this?  Change to track back of veh.
 */
#ifndef DELTA
#define DELTA float(1.1)
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
    float time_r; //reaction time in seconds

    float stop_d; // Safe following distance between us and leader

    unsigned char control; // manual, or type of self-driving

	sf::RectangleShape rect;
public:
	Car(const sf::Vector2f& p);
	Car(const sf::Vector2f& p, bool var);

    void set_max_vel(float mv)
    {
        max_vel = mv;
    }

	inline float get_max_vel() const
	{
		return max_vel;
	}

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

	inline float get_current_stop_d() const
	{
		return stop_d;
	}

	inline float get_vel() const
	{
		return vel;
	}

	inline float get_trg_vel() const
	{
		return trg_vel;
	}

	inline float get_acc() const
	{
		return acc;
	}

    void set_acc(float a)
    {
        acc = a;
    }

	inline float get_drag() const
	{
		return drag;
	}

    inline unsigned char get_control() const
    {
        return control;
    }
    inline float get_brk_max() const
    {
        return brk_max;
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

    // get the distance from front to front
    float get_headway(Car leader);

    // get the safe stopping dist, front to front
    float get_stop_d(Car leader);

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
