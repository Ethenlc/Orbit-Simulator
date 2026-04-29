#pragma once

class TimeUtils {
public:
	// Time calculations
	double calculateTimeDilation(int hoursDay = 24, int minutesHour = 60) const;
	double calculateTimePerFrame(double timeDilation, int frameRate = 30) const;
	double calculateRotationPerFrame(double timeDilation, int frameRate, double secondsDay) const;

};
