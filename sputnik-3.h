/***********************************************************************
* Header File:
*    Sputnik Satellite : The representation of a Sputnik Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Sputnik Satellite
************************************************************************/
#pragma once
#include "satellite.h"

/**************************************************************
 * SPUTNIK
 * The representation of a Sputnik Satellite
 *************************************************************/
class Sputnik : public Satellite
{
public:
   Sputnik() = default;

   void setupOrbit(Position& satellite);
};

