/***********************************************************************
* Header File:
*    Crew Dragon Satellite : The representation of a Crew Dragon Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Crew Dragon Satellite
************************************************************************/
#include "crewDragon.h"

/**********************************************************************
 * CREW DRAGON :: SETUP ORBIT
 * Set up the initial conditions of the Crew Dragon satellite
 **********************************************************************/
void CrewDragon::setupOrbit(Position& satellite)
{
   satellite.setMetersX(0.0);          // Initial x-coordinate
   satellite.setMetersY(16000000.0);   // 8,000,000 m above Earth's surface + earth's radius

   satelliteVelocityX = -5120.0;  // Initial velocity in m/s
   satelliteVelocityY = 0.0;     // No initial vertical velocity
}
