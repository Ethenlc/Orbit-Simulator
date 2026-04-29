/***********************************************************************
* Header File:
*    Collisions : Test the Collisions class
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*   All the collisions needed for the program
************************************************************************/

#include "collisions.h"
#include <cmath>
#include <iostream>

/**********************************************************************
* Calculate Distance
* Function to calculate the distance between two positions
***********************************************************************/
double Collisions::calculateDistance(const Position& p1, const Position& p2) 
{
    double dx = p2.getPixelsX() - p1.getPixelsX();
    double dy = p2.getPixelsY() - p1.getPixelsY();
    return sqrt(dx * dx + dy * dy);
}

/***********************************************************************
* Check Collision
* Function to check if two satellites are overlapping
************************************************************************/
bool Collisions::checkCollision(const Position& p1, const Position& p2, double threshold) 
{
    double distance = calculateDistance(p1, p2);
    return distance < threshold;
}

/***********************************************************************
* Check Satellite Collisions
* Function to check collisions between satellites
************************************************************************/
void Collisions::checkSatelliteCollisions(const std::vector<Position>& satellitePositions, double threshold) {
    for (size_t i = 0; i < satellitePositions.size(); ++i) 
    {
        for (size_t j = i + 1; j < satellitePositions.size(); ++j) 
        {
            if (checkCollision(satellitePositions[i], satellitePositions[j], threshold)) 
            {
                std::cout << "Collision detected between satellite " << i << " and satellite " << j << "!" << std::endl;
            }
        }
    }
}

/************************************************************************
* Check Projectile Collisions
* Function to check if the projectile collides with anything
*************************************************************************/
size_t Collisions::checkProjectileCollisions(
    Position& projectile,
    std::vector<Position>& allObjects,
    double threshold,
    std::vector<bool>& objectsToRemove
) {
    for (size_t i = 0; i < allObjects.size(); ++i) 
    {
        if (checkCollision(projectile, allObjects[i], threshold)) 
        {
            // Mark projectile and object for removal
            objectsToRemove[allObjects.size() - 1] = true; // Last index is projectile
            objectsToRemove[i] = true;

            // Return the index of the object hit
            return i;
        }
    }

    // No collision
    return -1;
}

/************************************************************************
* Check Earth Collisions
* Function to check if the Earth is colliding with other objects
*************************************************************************/
size_t Collisions::checkEarthCollisions(
    Position& earthPosition,
        std::vector<Position>& allObjects,
        double threshold,
        std::vector<bool>& objectsToRemove
        ) {
            for (size_t i = 0; i < allObjects.size(); ++i) 
            {
                if (checkCollision(earthPosition, allObjects[i], threshold))
                {
                    // Mark projectile and object for removal
                    objectsToRemove[allObjects.size() - 1] = true; // Last index is projectile
                    objectsToRemove[i] = true;

                    // Return the index of the object hit
                    return i;
                }
            }

            // No collision
            return -1;
}