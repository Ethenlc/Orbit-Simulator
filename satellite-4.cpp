/***********************************************************************
* Header File:
*    Satellite : The representation of a Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Satellite
************************************************************************/
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

	// Handling when the position is very close to (0, 0)
	const double threshold = 1e-6; // Small threshold to avoid (0, 0)
	if (std::abs(x) < threshold && std::abs(y) < threshold)
	{
		x = threshold;
		y = threshold;
	}

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

Position Satellite::getPosition() const
{
	return satellitePosition;  // Return the current position of the satellite
}

void Satellite::handleCollision(Satellite& satellite) {

}

void Satellite::maybeStartRotating() {
	// 0.04% chance to rotate each frame
	if (!isRotating && (rand() % 5000 < 2)) {
		isRotating = true;
	}
}

void Satellite::updateRotation(double timePerFrame) {
	if (isRotating) {
		rotationAngle += 0.0015 * timePerFrame;

		// Normalize angle to keep it between 0 and 360
		if (rotationAngle >= 360.0) {
			rotationAngle -= 360.0;
		}
	}
}