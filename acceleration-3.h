/***********************************************************************
* Header File:
*    Acceleration : The representation of a Acceleration
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Acceleration
************************************************************************/
#pragma once
#include <cmath>

/***********************************************************************
* Acceleration
* The representation of a Acceleration
* ***********************************************************************/
class Acceleration 
{
private:
	// Constants
	const double GRAVITY_EARTH = 9.80665;  // m/s^2
	const double EARTH_RADIUS = 6378000.0; // meters

public:
	double calculateAltitude(double x, double y) const;
	double calculateGravity(double altitude) const;
	double calculateHorizontalAcceleration(double acceleration, double angle) const;
	double calculateVerticalAcceleration(double acceleration, double angle) const;
};
