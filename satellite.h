#pragma once
#include "direction.h"
#include "acceleration.h"
#include "position.h"

class Satellite {
public:
    // Satellite state
    double satelliteVelocityX;
    double satelliteVelocityY;

    Satellite() : satelliteVelocityX(0.0), satelliteVelocityY(0.0) {}

    void updateSatellite(Position& satellite, double timePerFrame);
};
