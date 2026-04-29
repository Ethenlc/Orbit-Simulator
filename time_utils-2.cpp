/***********************************************************************
* Header File:
*    Time Utils : The representation of a Time Utils
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Time Utils
************************************************************************/
#include "time_utils.h"

/*************************************************************************
* Time Dilation
* Calculate the time dilation
*************************************************************************/
double TimeUtils::calculateTimeDilation(int hoursDay, int minutesHour) const
{
	return hoursDay * minutesHour;
}

/*************************************************************************
* Time per Frame
* Calculate the time per frame
*************************************************************************/
double TimeUtils::calculateTimePerFrame(double timeDilation, int frameRate) const
{
	return timeDilation / frameRate;
}

/**************************************************************************
* Rotation per Frame
* Calculates Earth's rotation per frame and is used in callback() to update angleEarth
**************************************************************************/
double TimeUtils::calculateRotationPerFrame(double timeDilation, int frameRate, double secondsDay) const
{
	return -(2.0 * 3.14159 / frameRate) * (timeDilation / secondsDay);
}