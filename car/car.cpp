#include "car.hpp"

// units in meters, seconds, kg

// hardcoded for now. It's a Honda Civic
Car::Car(const sf::Vector2f& p)
	: rect(sf::Vector2f(CAR_LEN, CAR_WID))
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
    time_r = 0.5; // reaction time, proxy for now

    control = MANUAL; // Which self-driving algorithm

	rect.setPosition(p);
	rect.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

// Civic with some variance...
Car::Car(const sf::Vector2f& p, bool var)
	: rect(sf::Vector2f(CAR_LEN, CAR_WID))
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
    time_r = 0.5; // reaction time, proxy for now

    if (var)
    {
        brk_max += std::rand() % BRK_VAR - BRK_VAR/2;
        max_vel += std::rand() % VEL_VAR - VEL_VAR/2;
        max_acc += std::rand() % ACC_VAR - ACC_VAR/2;
        mass += std::rand() % MASS_VAR - MASS_VAR/2;
        time_r += (std::rand() % int (TIME_R_VAR*100))/ 100 - TIME_R_VAR/2;
    }
    control = MANUAL; // Which self-driving algorithm

	rect.setPosition(p);
	rect.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

void Car::set_gas(float g)
{
//	brk_acc = 0;
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

// Get the distance between my front bumper and the leader's back
float Car::get_headway(Car leader)
{
    float my_front;
    //float lead_front;
    float lead_back;

    my_front = get_pos() + get_size()/2;
    // this looks like it's computing front...which is wrong...
//    lead_front = leader.get_pos() + DELTA * leader.get_size()/2;
    lead_back = leader.get_pos() - DELTA * leader.get_size()/2; 
    return lead_back - my_front;
}

// Get the safe stopping distance, front to front
// 7 possible stop points
// 3 depend on a max falling within time bounds
float Car::get_stop_d(Car leader)
{
    float h_max = 0, h_current;
    float t;
    float time_test;
    float time_stop_lead;
    float time_stop_follow;

    // check if anyone is moving right now, if not, safe to proceed (unless we're already too close...)
    // if (vel == 0 && leader.get_vel() == 0)
    //    return MIN_SAFE_HEADWAY;

    // check time between 0 and time_r
    time_test = (leader.get_vel() - vel)/(acc - leader.get_brk_max() + FLT_EPSILON);
    if (0 < time_test && time_test < time_r) {
        h_current = 0.5*acc*pow(leader.get_vel() - vel,2)/pow(acc - leader.get_brk_max() + FLT_EPSILON,2) - 0.5*leader.get_brk_max()*pow(leader.get_vel() - vel,2)/pow(acc - leader.get_brk_max(),2) - (leader.get_vel() - vel)*leader.get_vel()/(acc - leader.get_brk_max() + FLT_EPSILON) + (leader.get_vel() - vel)*vel/(acc - leader.get_brk_max() + FLT_EPSILON);
        if (h_current > h_max) h_max = h_current;
    }

    h_current = 0.5*acc*pow(time_r,2) - 0.5*leader.get_brk_max()*pow(time_r,2) - time_r*leader.get_vel() + time_r*vel;
    /*
    std::cerr << "h_max0[2]:" << h_current
              << "\nacc:" << acc
              << "\ntr1:" << time_r
              << "\ndec0:" << leader.get_brk_max()
              << "\ndec1:" << get_brk_max()
              << "\nv0:" << leader.get_vel()
              << "\nv1:" << vel << "\n\n";
              */
    if (h_current > h_max) h_max = h_current;

    // check time between time_r and time_stop_leader
    time_stop_lead = leader.get_vel() / leader.get_brk_max();
    time_test = ((acc - brk_max)*time_r - leader.get_vel() + vel)/(leader.get_brk_max() - brk_max + FLT_EPSILON);
    if (time_r < time_test && time_test < time_stop_lead) {
        t = ((acc - brk_max)*time_r - leader.get_vel() + vel)/(leader.get_brk_max() - brk_max + FLT_EPSILON);
        h_current =  -0.5*pow(brk_max*(t - time_r) - leader.get_brk_max()*t + acc*time_r - leader.get_vel() + vel,2)*leader.get_brk_max() + 0.5*pow(brk_max*(t - time_r) - leader.get_brk_max()*t + acc*time_r + time_r - leader.get_vel() + vel,2)*brk_max + 0.5*acc*pow(time_r,2) - (brk_max*(t - time_r) - leader.get_brk_max()*t + acc*time_r + time_r - leader.get_vel() + vel)*(acc*time_r + vel) + (brk_max*(t - time_r) - leader.get_brk_max()*t + acc*time_r - leader.get_vel() + vel)*leader.get_vel() + time_r*vel;
        if (h_current > h_max) h_max = h_current;
    }

    h_current = 0.5*brk_max*pow(time_r - leader.get_vel()/leader.get_brk_max() + FLT_EPSILON,2) + 0.5*acc*pow(time_r,2) - (acc*time_r + vel)*(time_r - leader.get_vel()/leader.get_brk_max() + FLT_EPSILON) + time_r*vel - 3/2*pow(leader.get_vel(),2)/(leader.get_brk_max() + FLT_EPSILON);
    if (h_current > h_max) h_max = h_current;

    // check time between time_stop_leader and time_stop_follower
    time_stop_follow = -((acc - brk_max)*time_r + vel)/(brk_max + FLT_EPSILON);
    time_test = -((acc - brk_max)*time_r + vel)/(brk_max + FLT_EPSILON);
    if (time_stop_lead < time_test && time_test < time_stop_follow) {
        t = -1*((acc - brk_max)*time_r + vel)/(brk_max + FLT_EPSILON);
        h_current =  0.5*pow(brk_max*(t - time_r) + acc*time_r + time_r + vel,2)*brk_max + 0.5*acc*pow(time_r,2) - (brk_max*(t - time_r) + acc*time_r + time_r + vel)*(acc*time_r + vel) + time_r*vel - 3/2*pow(leader.get_vel(),2)/(leader.get_brk_max() + FLT_EPSILON);
        if (h_current > h_max) h_max = h_current;
    }

    h_current = 0.5*brk_max*pow(time_r + ((acc - brk_max)*time_r + vel)/(brk_max + FLT_EPSILON),2) + 0.5*acc*pow(time_r,2) - (acc*time_r + vel)*(time_r + ((acc - brk_max)*time_r + vel)/(brk_max + FLT_EPSILON)) + time_r*vel - 3/2*pow(leader.get_vel(),2)/(leader.get_brk_max() + FLT_EPSILON);
    if (h_current > h_max) h_max = h_current;

    return h_max;
}

// Get what the target gas setting of the car should be
// given the car it is following.
float Car::get_auto_vel(Car leader)
{
    float new_vel;
    float headway;
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
            // Follow the leader exactly
            new_vel = leader.get_vel();
            break;
        case AUTOMATIC2:
            /* Go fast until we get close, then follow
             * TODO still collides.  stopping calcs may be off
             * Still problems, but making progess
             */
            headway = get_headway(leader);
            set_current_headway(headway);
            stop_d = get_stop_d(leader);
            if (headway > 1.1*stop_d)
            {
                new_vel = max_vel;
            }
            else if (headway > stop_d)
            {
                // should ramp down target velocity so it's max at 2xstop_d and - and stop_d
                new_vel = headway / (stop_d + FLT_EPSILON);
            }
            else
            {
                new_vel = 0;
                /*
                new_vel = std::min(leader.vel, 
                            headway / (stop_d + FLT_EPSILON));
                            */
                //    2 * (headway ) / (PHI * time_r));
            }
            break;
        default:
            new_vel = std::min(max_vel, leader.get_vel()); //Try not to crash
    }

    return new_vel / (float)max_vel;
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

    // if set to fixed braking, ignore the trg_vel
	if (brk_acc < 0 )
		acc = brk_acc;

    // we desperately need to stop, so override braking
    // TODO there's probably a better way, but alg was naive
    if (trg_vel < FLT_EPSILON)
        acc = brk_max;

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
