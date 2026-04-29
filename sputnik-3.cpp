/***********************************************************************
* Header File:
*    Sputnik Satellite : The representation of a Sputnik Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Sputnik Satellite
************************************************************************/
#include "sputnik.h"

/**********************************************************************
 * SPUTNIK :: SETUP ORBIT
 * Set up the orbit of the Sputnik satellite
 **********************************************************************/
void Sputnik::setupOrbit(Position& satellite)
{
   satellite.setMetersX(-36515095.13);
   satellite.setMetersY(21082000.0);

   satelliteVelocityX = 1750.0;  // Initial velocity in m/s
   satelliteVelocityY = 2384.68;
}
