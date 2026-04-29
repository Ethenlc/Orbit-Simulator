/***********************************************************************
* Header File:
*    Starlink Satellite : The representation of a Starlink Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Starlink Satellite
************************************************************************/
#include "starlink.h"

/**************************************************************
 * STARLINK
 * The class for the Starlink Satellite
 *************************************************************/
void Starlink::setupOrbit(Position& satellite)
{
   satellite.setMetersX(0.0);
   satellite.setMetersY(-13020000.0);

   satelliteVelocityX = 5800.0;  // Initial velocity in m/s
   satelliteVelocityY = 0.0;
}
