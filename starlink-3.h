/***********************************************************************
* Header File:
*    Starlink Satellite : The representation of a Starlink Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Starlink Satellite
************************************************************************/
#pragma once
#include "satellite.h"

/**************************************************************
 * STARLINK
 * The class for the Starlink Satellite
 *************************************************************/
class Starlink :  public Satellite
{
public:
   Starlink() = default;

   void setupOrbit(Position& satellite);
};

