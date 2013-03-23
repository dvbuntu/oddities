#include "car.hpp"

// units in meters, seconds, kg

// hardcoded for now. It's a Honda Civic
Car::Car(const sf::Vector2f& p)
	: rect(sf::Vector2f(4.55676, 1.7526))
{
	vel = 0;
	trg_vel = 0;
	brk_acc = 0;
	brk_max = -37.17112; // 60-0 in 127 feet
	max_vel = 53.6448; // 120mph
	max_acc = 5.509; // 0-60 in 7.1 seconds (accounting for drag and such)
    mass = 1242.84; // 2740 lb
    weight = mass * 9.81; // kg*m/s^2
    roll_r = 0.015 * 9.81; // maybe not big enough?
	drag_m = (0.5 * 2.51516 * 0.45 * 1.225) / mass; // (1/2 * area of front of car * drag coefficient * density of air) / mass

    control = MANUAL;

	rect.setPosition(p);
	rect.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

void Car::set_gas(float g)
{
	brk_acc = 0;
	trg_vel = g * max_vel;
}

void Car::set_brake(float b)
{
	trg_vel = 0;
	brk_acc = b * brk_max;
}

void Car::set_control(unsigned char c)
{
	control = c;
}

float Car::get_auto_vel(Car leader)
{
    float new_vel;
    /* TODO Put self-driving algorithms into a nice array
     * algs[control] is the control scheme function.
     * No changes for MANUAL
     * Complain if control >= NUM_CONTROL_TYPES
     * Default to coasting
     */
    switch (control)
    {
        case MANUAL:
            new_vel = trg_vel;
            break;
        case AUTOMATIC1:
            new_vel = leader.trg_vel;
            break;
        default:
            new_vel = trg_vel; //Just keep doing what we're doing
    }

    return new_vel;
}

void Car::step(float time)
{
	acc = 0;

	// if not going the speed you want to, set acceleration proportional to the difference
    // TODO Change to accept an acc and compute those before step
	if (vel < trg_vel)
    {
		acc = ((max_vel - vel) / (float)max_vel) * max_acc;
    }
    /* slow down in proportion to trg_vel
     * Careful with epsilon so we don't divide by zero
     */
    else if (vel > trg_vel)
    {
		acc = ((trg_vel - vel) / ( (float)trg_vel + 
               FLT_EPSILON)) * brk_acc;
    }

    // if set to fixed braking or targeting low vel, ignore the trg_vel
	if (brk_acc < 0 || trg_vel < FLT_EPSILON)
		acc = brk_acc;

	// deceleration from drag
	drag = drag_m * vel * vel;

	vel += (acc - drag - roll_r) * time;

	// clamp velocity
	if (vel < 0)
		vel = 0;

	if (vel > max_vel)
		vel = max_vel;

	rect.move(vel * time, 0);
}
