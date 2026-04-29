/***********************************************************************
 * Header File:
 *    Test Sputnik : Test the Sputnik class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Collisions
 ************************************************************************/
#pragma once

#include "collisions.h"
#include "unitTest.h"
#include "position.h"

 /*******************************
 * TEST Collisions
 * A friend class for Collisions which contains the Collision unit tests
 ********************************/
class TestCollisions : public UnitTest
{
public:
	void run()
	{
		test_calculateDistance();
		test_checkCollision();
		test_checkEarthCollisions();
		test_checkProjectileCollisions();
		report("Collisions");
	}

private:

   /*********************************************
    * name:    CALCULATE DISTANCE
    * input:   p1=(0, 0), p2=(3, 4)
    * output:  distance=5.0
    *********************************************/
   void test_calculateDistance()
   {
      // setup
      Position p1(0, 0);
      Position p2(3, 4);

      // exercise
      double distance = Collisions::calculateDistance(p1, p2);

      // verify
      assertEquals(distance, 5.0);
   }

   /*********************************************
    * name:    CHECK COLLISION
    * input:   p1=(0, 0), p2=(1, 1), threshold=1.5
    * output:  collision=true
    *********************************************/
   void test_checkCollision()
   {
      // setup
      Position p1(0, 0);
      Position p2(1, 1);

      // exercise
      bool collision = Collisions::checkCollision(p1, p2, 1.5);

      // verify
      assertUnit(collision == true);
   }

   /*********************************************
    * name:    CHECK EARTH COLLISIONS
    * input:   earth=(0, 0), objects=[(1, 1), (2, 2)]
    * output:  collision=true
    *********************************************/
   void test_checkEarthCollisions()
   {
      // setup
      Position earth(0, 0);
      std::vector<Position> objects = { Position(1, 1), Position(2, 2) };
      std::vector<bool> objectsToRemove(objects.size(), false);

      // exercise
      size_t collisionIndex = Collisions::checkEarthCollisions(earth, objects, 1.5, objectsToRemove);

      // verify
      assertUnit(collisionIndex == 0);
      assertUnit(objectsToRemove[0] == true);
   }

   /*********************************************
    * name:    CHECK PROJECTILE COLLISIONS
    * input:   projectile=(0, 0), objects=[(1, 1), (2, 2)], threshold=1.5
    * output:  collision=true
    *********************************************/
   void test_checkProjectileCollisions()
   {
      // setup
      Position projectile(0, 0);
      std::vector<Position> objects = { Position(1, 1), Position(2, 2) };
      std::vector<bool> objectsToRemove(objects.size() + 1, false); // +1 for the projectile

      // exercise
      size_t collisionIndex = Collisions::checkProjectileCollisions(projectile, objects, 1.5, objectsToRemove);

      // verify
      assertUnit(collisionIndex == 0);
      assertUnit(objectsToRemove[0] == true);
      assertUnit(objectsToRemove[objects.size()] == false); // Last index is projectile
   }
};