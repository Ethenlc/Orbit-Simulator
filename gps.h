#pragma once
#include "satellite.h"

class GPS : public Satellite {
public:
	GPS() = default;

	void setupOrbit(Position& satellite);
};