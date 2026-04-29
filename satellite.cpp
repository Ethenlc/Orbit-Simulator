#include "satellite.h"

/***************************************************************************
* Satellite Update
* Called every frame in callback() to update satellite position and velocity
* **************************************************************************/
void Satellite::updateSatellite(Position& satellite, double timePerFrame)
{
	Acceleration acceleration;
	Direction direction;

	// Get current position
	double x = satellite.getMetersX();
	double y = satellite.getMetersY();

	// Calculate gravity
	double altitude = acceleration.calculateAltitude(x, y);
	double gravityMagnitude = acceleration.calculateGravity(altitude);
	double gravityDirection = direction.calculateGravityDirection(x, y);

	// Calculate acceleration components
	double ddx = acceleration.calculateHorizontalAcceleration(gravityMagnitude, gravityDirection);
	double ddy = acceleration.calculateVerticalAcceleration(gravityMagnitude, gravityDirection);

	// Update velocity (v = v0 + at)
	satelliteVelocityX += ddx * timePerFrame;
	satelliteVelocityY += ddy * timePerFrame;

	// Update position (s = s0 + vt + 1/2at^2)
	double newX = x + (satelliteVelocityX * timePerFrame) + (0.5 * ddx * timePerFrame * timePerFrame);
	double newY = y + (satelliteVelocityY * timePerFrame) + (0.5 * ddy * timePerFrame * timePerFrame);

	satellite.setMetersX(newX);
	satellite.setMetersY(newY);
}