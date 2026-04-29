#pragma once
#include "satellite.h"

class Hubble : public Satellite {
public:
    Hubble() = default;

    void setupOrbit(Position& position);
};
