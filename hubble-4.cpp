/***********************************************************************
* Header File:
*    Hubble Satellite : The representation of a Hubble Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Hubble Satellite
************************************************************************/
#include "hubble.h"
#include "satellite.h"

/***********************************************************************
* Hubble :: SETUP ORBIT
* Sets up the orbit for the Hubble Satellite
***********************************************************************/
void Hubble::setupOrbit(Position& position) 
{
    position.setMetersX(0.0);
    position.setMetersY(-32164000.0);

    // Set Hubble's initial velocity for a low Earth orbit
    satelliteVelocityX = 3500.0; // Velocity in m/s
    satelliteVelocityY = 0.0;
}
