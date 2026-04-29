/***********************************************************************
* Header File:
*    Hubble Satellite : The representation of a Hubble Satellite
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Hubble Satellite
************************************************************************/
#pragma once
#include "satellite.h"

/***********************************************************************
* Hubble: Hubble
* Description: Constructor for the Hubble class.
* ***********************************************************************/
class Hubble : public Satellite 
{
public:
    Hubble() = default;

    void setupOrbit(Position& position);
};
