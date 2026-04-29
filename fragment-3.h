#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "position.h"

class Fragment {
public:
    Fragment();

    // Initialize a fragment at a specific position and angle
    void initialize(const Position& startPos, double angle);

    // Update fragment's position and lifetime
    void update(double timeStep);

    // Check if fragment is still active
    bool isActive() const;

    // Get the current position of the fragment
    Position getPosition() const;

private:
    Position pos;     // Current position of the fragment
    double angle;     // Initial direction of movement
    double velocity;  // Current velocity of the fragment
    double lifetime;  // Remaining time before fragment disappears
    bool active;      // Whether the fragment is currently visible/active
};

#endif // FRAGMENT_H