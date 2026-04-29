#include "hubble.h"
#include "satellite.h"

// Setup Hubble's unique orbit
void Hubble::setupOrbit(Position& position) {
    position.setMetersX(32164000.0);
    position.setMetersY(0.0); // Earth's radius + 547 km altitude

    // Set Hubble's initial velocity for a low Earth orbit
    satelliteVelocityX = 0.0; // Velocity in m/s
    satelliteVelocityY = 3075.0;
}
