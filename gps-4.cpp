/***********************************************************************
* Header File:
*    GPS Satellite : The representation of a GPS Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the GPS Satellite
************************************************************************/

#include "gps.h"
/***********************************************************************
* GPS :: SETUP ORBIT
* Sets up the orbit for the GPS Satellite
* ***********************************************************************/
void GPS::setupOrbit(Position& satellite, double startX, double startY, double velocityX, double velocityY)
{
    satellite.setMetersX(startX);
    satellite.setMetersY(startY);

    satelliteVelocityX = velocityX;
    satelliteVelocityY = velocityY;
}
