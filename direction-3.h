/***********************************************************************
* Header File:
*    Direction : The representation of a Direction
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Direction
************************************************************************/
#pragma once
#include <cmath>

/***********************************************************************
* DIRECTION
* The representation of a Direction
* This class will calculate the direction of gravity
************************************************************************/
class Direction 
{
public:
	double calculateGravityDirection(double xs, double ys) const;
};
