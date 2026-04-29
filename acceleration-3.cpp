/***********************************************************************
* Header File:
*    Acceleration : The representation of a Acceleration
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Acceleration
************************************************************************/
#include "acceleration.h"

/*************************************************************************
* Altitude Calculation
* Used in calculateGravity() to determine satellite's height above the surface
* ************************************************************************/
double Acceleration::calculateAltitude(double x, double y) const
{
	return sqrt(x * x + y * y) - EARTH_RADIUS;
}

/*************************************************************************
* Gravity Calculation
* Used in updateSatellite() to determine gravitational force magnitude
* ************************************************************************/
double Acceleration::calculateGravity(double altitude) const
{
	return GRAVITY_EARTH * pow(EARTH_RADIUS / (EARTH_RADIUS + altitude), 2);
}

/*************************************************************************
* Horizontal Acceleration
* Used in updateSatellite() to compute x-component of gravitational acceleration
* ************************************************************************/
double Acceleration::calculateHorizontalAcceleration(double acceleration, double angle) const
{
	return acceleration * sin(angle);
}

/*************************************************************************
* Vertical Acceleration
* Used in updateSatellite() to compute y-component of gravitational acceleration
* ************************************************************************/
double Acceleration::calculateVerticalAcceleration(double acceleration, double angle) const
{
	return acceleration * cos(angle);
}
