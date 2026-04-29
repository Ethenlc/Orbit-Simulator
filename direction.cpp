#include "direction.h"

/*************************************************************************
* Gravity Direction Calculation
* Used in updateSatellite() to determine direction of gravitational pull
* ************************************************************************/
double Direction::calculateGravityDirection(double xs, double ys) const
{
	return atan2(-xs, -ys); // Points towards earth center (0,0)
}