/***********************************************************************
* Header File:
*    Time Utils : The representation of a Time Utils
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    Everything we need to know about the Time Utils
************************************************************************/
#pragma once

/******************************************************
 * TIME UTILS
 * The representation of a Time Utils
 ******************************************************/
class TimeUtils {
public:
	// Time calculations
	double calculateTimeDilation(int hoursDay = 24, int minutesHour = 60) const;
	double calculateTimePerFrame(double timeDilation, int frameRate = 30) const;
	double calculateRotationPerFrame(double timeDilation, int frameRate, double secondsDay) const;

};
