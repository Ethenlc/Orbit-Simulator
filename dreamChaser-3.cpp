/***********************************************************************
* Header File:
*    Dream Chaser: The representation of a Dream Chaser ship
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Dream Chaser ship
************************************************************************/
#include "dreamChaser.h"

/***************************************************************************************
* DreamChaser: DreamChaser
 * Description: Constructor for the DreamChaser class. 
***************************************************************************************/
DreamChaser::DreamChaser() : angle(0.0)
{
   ptShipCenter.setPixelsX(-450.0);
   ptShipCenter.setPixelsY(450.0);

   // Set initial velocity (0.0 m/s, -2000.0 m/s)
   satelliteVelocityX = 0.0;
   satelliteVelocityY = -2000.0;
}

/**************************************************************************************
* DreamChaser: update
 * Description: Updates the position and velocity of the DreamChaser object.
***************************************************************************************/
void DreamChaser::updateSatellite(Position& position, double timePerFrame)
{
    Acceleration acceleration;
    Direction direction;

    // Get current position
    double x = ptShipCenter.getMetersX();
    double y = ptShipCenter.getMetersY();

    // Calculate gravity
    double altitude = acceleration.calculateAltitude(x, y);
    double gravityMagnitude = acceleration.calculateGravity(altitude);
    double gravityDirection = direction.calculateGravityDirection(x, y);

    // Calculate gravity's acceleration components
    double ddxGravity = acceleration.calculateHorizontalAcceleration(gravityMagnitude, gravityDirection);
    double ddyGravity = acceleration.calculateVerticalAcceleration(gravityMagnitude, gravityDirection);

    // Update velocity due to gravity
    satelliteVelocityX += ddxGravity * timePerFrame;
    satelliteVelocityY += ddyGravity * timePerFrame;

    // Update position based on velocity
    double newX = x + satelliteVelocityX * timePerFrame;
    double newY = y + satelliteVelocityY * timePerFrame;

    ptShipCenter.setMetersX(newX);
    ptShipCenter.setMetersY(newY);
}

/*******************************************************************************************
* DreamChaser: rotateLeft
* Description: Rotates the ship left (counter-clockwise).
*******************************************************************************************/
void DreamChaser::rotateLeft()
{
    angle -= 0.1;
}

/*******************************************************************************************
* DreamChaser: rotateRight
* Description: Rotates the ship right (clockwise).
*******************************************************************************************/
void DreamChaser::rotateRight()
{
    angle += 0.1;
}

/*******************************************************************************************
* DreamChaser: applyThrust
* Description: Applies thrust to the ship.
*******************************************************************************************/
void DreamChaser::applyThrust(double timePerFrame)
{
    Acceleration acceleration;

    // Calculate thrust in the direction of the ship's current angle
    double ddx = acceleration.calculateHorizontalAcceleration(thrustAcceleration, angle);
    double ddy = acceleration.calculateVerticalAcceleration(thrustAcceleration, angle);

    // Update velocities with thrust applied
    satelliteVelocityX += ddx * timePerFrame;
    satelliteVelocityY += ddy * timePerFrame;

    // Reset thrust acceleration to ensure it doesn't persist across frames
    thrustAcceleration = 0.0;
}

void DreamChaser::setThrustAcceleration(double thrust)
{
    thrustAcceleration = thrust;
}

/*******************************************************************************************
* DreamChaser: launchProjectile
* Description: Launches a projectile.
* ******************************************************************************************/
void DreamChaser::launchProjectile()
{
    // Define the speed of the projectile
    double speed = 12000.0;  // Adjust this value to control how fast the projectile moves

    // Calculate the horizontal and vertical components of the projectile's velocity
    projectileVelocityY = speed * cos(angle);
    projectileVelocityX = speed * sin(angle);

    // Initialize the position of the projectile at the ship's position
    projectilePos = ptShipCenter;
}

void DreamChaser::updateProjectile(double timePerFrame)
{
    // Update the projectile's position based on its velocity
    double newX = projectilePos.getMetersX() + projectileVelocityX * timePerFrame;
    double newY = projectilePos.getMetersY() + projectileVelocityY * timePerFrame;

    // Set the new position of the projectile
    projectilePos.setMetersX(newX);
    projectilePos.setMetersY(newY);
}

Position DreamChaser::getProjectilePos() const
{
    return projectilePos;
}

/*******************************************************************************************
* DreamChaser: setPosition
* Description: Sets the position of the ship.
********************************************************************************************/
void DreamChaser::setPosition(double x, double y)
{
   ptShipCenter.setMetersX(x);
   ptShipCenter.setMetersY(y);
}

/******************************************************************************************** 
* DreamChaser: setVelocity
* Description: Sets the velocity of the ship.
* *******************************************************************************************/
void DreamChaser::setVelocity(double vx, double vy)
{
   satelliteVelocityX = vx;
   satelliteVelocityY = vy;
}

/********************************************************************************************
* DreamChaser: getPosX
* Description: Gets the x position of the ship.
* *******************************************************************************************/
double DreamChaser::getPosX() const
{
   return ptShipCenter.getMetersX();
}

/********************************************************************************************
* DreamChaser: getPosY
* Description: Gets the y position of the ship.
* *******************************************************************************************/
double DreamChaser::getPosY() const
{
   return ptShipCenter.getMetersY();
}

/********************************************************************************************
* DreamChaser: getAngle
* Description: Gets the angle of the ship.
********************************************************************************************/
double DreamChaser::getAngle() const
{
   return angle;
}

