/***********************************************************************
* Header File:
*    Dream Chaser: The representation of a Dream Chaser ship
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Dream Chaser ship
************************************************************************/
#pragma once

#include "position.h"
#include "acceleration.h"
#include "satellite.h"
#include <cmath>
#define M_PI 3.14159265358979323846

/***************************************************************************************
* DreamChaser: DreamChaser
* Description: Constructor for the DreamChaser class.
* **************************************************************************************/
class DreamChaser : public Satellite
{
public:
   Position getProjectilePos() const;
   // Constructor
   DreamChaser();

   void setupOrbit(Position& position) {
      // Override the setupOrbit from Satellite to use our initial conditions
      position.setPixelsX(-450.0);
      position.setPixelsY(450.0);

      satelliteVelocityX = 0.0;
      satelliteVelocityY = -2000.0;
   }

   // Update method to update the position and velocity
   void updateSatellite(Position& position, double timePerFrame);

   // Rotate ship
   void rotateLeft();
   void rotateRight();

   // Apply thrust
   void applyThrust(double timePerFrame);
   void setThrustAcceleration(double thrust);

   // Launch projectile
   void launchProjectile();
   void updateProjectile(double timePerFrame);

   // Setters and Getters for position and velocity
   void setPosition(double x, double y);
   void setVelocity(double vx, double vy);
   double getPosX() const;
   double getPosY() const;
	double getSatelliteVelocityX() const { return satelliteVelocityX; }
	double getSatelliteVelocityY() const { return satelliteVelocityY; }

   // Get the current angle
   double getAngle() const;

private:
   Position ptShipCenter;
   Position projectilePos;
   double projectileVelocityX;
   double projectileVelocityY;
   double satelliteVelocityX;
   double satelliteVelocityY;
   double angle;
   double thrustAcceleration;
   const double projectileSpeed = 9000.0;
   const double projectileDistance = 19.0;
};


