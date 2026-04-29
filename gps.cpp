#include "gps.h"
void GPS::setupOrbit(Position& satellite)
{
	// GEO altitude: 35,786 km above Earth's surface
	// Total distance from Earth's center: 42,164 km
	satellite.setMetersX(0.0);
	satellite.setMetersY(42164000.0);  // 42,164 km in meters

	// GEO orbital velocity: 3,075 m/s
	satelliteVelocityX = -3075.0;  // Initial velocity in m/s
	satelliteVelocityY = 0.0;
}