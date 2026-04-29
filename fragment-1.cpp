#include "fragment.h"
#include <cmath>
#include <cstdlib>  // for rand()

Fragment::Fragment() : active(false), lifetime(0.0), velocity(0.0), angle(0.0) {}

void Fragment::initialize(const Position& startPos, double angle) {
    pos = startPos;
    this->angle = angle;

    // More realistic random velocity and lifetime
    velocity = 1500;  // More varied velocity
    lifetime = 2500;

    active = true;
}

void Fragment::update(double timeStep) {
    if (!active) return;

    // Calculate movement based on angle and velocity
    double dx = velocity * cos(angle) * timeStep;
    double dy = velocity * sin(angle) * timeStep;

    pos.addMetersX(dx);
    pos.addMetersY(dy);

    // Gradually reduce velocity (simulate deceleration)
    velocity *= 0.98;  // Slight deceleration

    // Reduce lifetime
    lifetime -= timeStep;

    // Deactivate if lifetime expires
    if (lifetime <= 0) {
        active = false;
    }
}

bool Fragment::isActive() const {
    return active;
}

Position Fragment::getPosition() const {
    return pos;
}