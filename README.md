oddities
========
Collaborative project on self-driving car simulation

# Self-driving Algorithm Development
Self-driving cars a coming; it's only a matter of time.  Many people are working on developing indidivually awesome cars.  But once we have a network of such cars, all communicating with each other, how should they drive to optimize traffic flow?

In traditional traffic engineering, we model traffic flow based on human behavior.  The classic Greenshield's and Greenberg model at a macroscopic scale, and similar models at the microscopic level predict traffic patterns (in particular travel times).  The self-driving car network, however, works in reverse.  We want minimizing travel time to determine how our cars drive.

This project seeks to explore the ideal algorithm for a simple convoy of self-driving cars with varying acceleration and braking capabilities.  For simplicity, these cars are only going forward in a straight line with no change in terrain nor road conditions.  While the cars in are communication as far as their current speed and capabilities, each one acts independently and does not know the others' actions in advance.  In particular, if one car comes to a sudden stop (e.g. due to an obstacle or mechanical failure), the trailing vehicles *react* to this.  Avoiding a rear-end collision becomes our core criteria for how these vehicle drive.  For human safety purposes, however, we can be slightly more loose.  By actually allowing a collision, but at sufficiently low relative velocity, we can limit human injury, but allow much smaller headways (intervehicle spacing).  Here's a [Description](car/headway.md) of phases of stopping a vehicle and necessary initial headways to avoid collision (and the math behind it).  Given this criterion (along with some factor of safety), our network of cars travel as closely together as possible, maximizing traffic flow and minimizing travel time.

![Example Video](http://i.imgur.com/2DsBwO0.gif)

# Code so far

+ car/sim - basic traffic simulator with simple self-driving car who follows you
+ car.py - A simple class for a vehicle object.  Currently just worries about stopping distance and time.  Includes plot.
+ SFML_examples - a basic SFML app in different languages
	main.cpp
	main.py
