/***********************************************************************
 * Header File:
 *    Satellite : The representation of a Satellite
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    Everything we need to know about the Satellite
 ************************************************************************/
#pragma once
#include "direction.h"
#include "acceleration.h"
#include "position.h"

 /***********************************************************************
  * SATELLITE
  * The representation of a Satellite
  * This class will calculate the satellite's position
  ************************************************************************/
class Satellite 
{
public:
   // Satellite state
   double satelliteVelocityX;
   double satelliteVelocityY;
   Position getPosition() const;

   Satellite() : satelliteVelocityX(0.0), satelliteVelocityY(0.0) {}

   void updateSatellite(Position& satellite, double timePerFrame);
   void handleCollision(Satellite& satellite);
   void maybeStartRotating();
   void updateRotation(double timePerFrame);

   double getRotationAngle() const {
       return rotationAngle;
   }
   bool getIsRotating() const {
       return isRotating;
   }

private:
    bool isRotating = false;
    double rotationAngle = 0.0;
    Position satellitePosition; // Assume this stores the satellite's position
};
