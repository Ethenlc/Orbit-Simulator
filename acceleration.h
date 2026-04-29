#pragma once
#include <cmath>

class Acceleration {
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
