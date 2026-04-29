/***********************************************************************
 * Header File:
 *    Test Starlink : Test the Starlink class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Starlink
 ************************************************************************/
#pragma once

#include "starlink.h"
#include "unitTest.h"
#include "position.h"
#include "collisions.h"

 /*******************************
 * TEST Starlink
 * A friend class for Starlink which contains the Starlink unit tests
 ********************************/
class TestStarlink : public UnitTest
{
public:
   void run()
   {
      test_construct_default();
      test_construct_nonDefault();
      test_custom_orbit_setup();
      test_initial_velocity();
      test_update_velocity();
      test_update_position();
      test_collision();
      report("Starlink");
   }

private:

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  pos=(0, 0)
    *********************************************/
   void test_construct_default()
   {
      // setup
      Starlink starlink;
      Position pos;

      // exercise
      starlink.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -13020000.0);
   }

   /*********************************************
    * name:    NON-DEFAULT CONSTRUCTOR
    * input:   x=120.0, y=360.0
    * output:  pos=(120.0, 360.0)
    *********************************************/
   void test_construct_nonDefault()
   {
      // setup
      Position pos(120.0, 360.0);
      Starlink starlink;

      // exercise
      starlink.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -13020000.0);
   }

   /*********************************************
    * name:    CUSTOM ORBIT SETUP
    * input:   custom initial conditions
    * output:  pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    *********************************************/
   void test_custom_orbit_setup()
   {
      // setup
      Starlink starlink;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      starlink.satelliteVelocityX = -5000.0;
      starlink.satelliteVelocityY = 1000.0;

      // exercise
      starlink.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -13020000.0);
      assertEquals(starlink.satelliteVelocityX, 5800.0);
      assertEquals(starlink.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   nothing
    * output:  velocityX=0.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      Starlink starlink;
      Position pos;

      // exercise
      starlink.setupOrbit(pos);

      // verify
      assertEquals(starlink.satelliteVelocityX, 5800.0);
      assertEquals(starlink.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      Starlink starlink;
      Position pos;
      starlink.setupOrbit(pos);
      double initialVelocityX = starlink.satelliteVelocityX;
      double initialVelocityY = starlink.satelliteVelocityY;

      // exercise
      starlink.updateSatellite(pos, 10.0);

      // verify
      assertUnit(starlink.satelliteVelocityX == initialVelocityX);
      assertUnit(starlink.satelliteVelocityY > initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos updated correctly
    *********************************************/
   void test_update_position()
   {
      // setup
      Starlink starlink;
      Position pos;
      starlink.setupOrbit(pos);

      // exercise
      starlink.updateSatellite(pos, 10.0);

      // verify
      assertEqualsTolerance(pos.getMetersX(), 58000.0, 1.0);
      assertEqualsTolerance(pos.getMetersY(), -13019647.0, 1.0);
   }

   /*************************************************************************
   * name: TEST COLLISION
   * input: projectile and object positions
   * output: collision detected correctly
   **************************************************************************/
   void test_collision()
   {
      // setup
      Starlink starlink;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};