/***********************************************************************
* Header File:
*    Collisions : Test the Collisions class
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*   All the collisions needed for the program
************************************************************************/
#pragma once
#include "position.h"
#include <vector>

/***********************************************************************
* Collisions
* Class to handle all the collisions in the program
***********************************************************************/
class Collisions
{
public:
    // Existing static methods
    static double calculateDistance(const Position& p1, const Position& p2);
    static bool checkCollision(const Position& p1, const Position& p2, double threshold);

    // Updated method to return the index of the collided object
    static size_t checkProjectileCollisions(
        Position& projectile,
        std::vector<Position>& allObjects,
        double threshold,
        std::vector<bool>& objectsToRemove
    );

    static size_t checkEarthCollisions(
        Position& earthPosition,
        std::vector<Position>& allObjects,
        double threshold,
        std::vector<bool>& objectsToRemove
    );

    static void checkSatelliteCollisions(
        const std::vector<Position>& satellitePositions,
        double threshold
    );
};