/***********************************************************************
* Header File:
*    Crew Dragon Satellite : The representation of a Crew Dragon Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Crew Dragon Satellite
************************************************************************/
#pragma once
#include "satellite.h"

/**************************************************************
 * CREW DRAGON
 * The class for the Crew Dragon satellite
 *************************************************************/
class CrewDragon : public Satellite
{
public:
   CrewDragon() = default;

   void setupOrbit(Position& satellite);
};

