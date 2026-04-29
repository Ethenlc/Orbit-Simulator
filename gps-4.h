/***********************************************************************
* Header File:
*    GPS Satellite : The representation of a GPS Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the GPS Satellite
************************************************************************/
#pragma once
#include "satellite.h"

/***********************************************************************
* GPS: GPS
* Description: Constructor for the GPS class.
* ***********************************************************************/
class GPS : public Satellite 
{
public:
	GPS() = default;

	void setupOrbit(Position& satellite, double startX, double startY, double velocityX, double velocityY);
};