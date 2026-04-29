/***********************************************************************
 * Header File:
 *    Test Hubble : Test the Hubble class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Hubble
 ************************************************************************/
#pragma once

#include "hubble.h"
#include "unitTest.h"
#include "position.h"
#include "collisions.h"

 /*******************************
 * TEST Hubble
 * A friend class for Hubble which contains the Hubble unit tests
 ********************************/
class TestHubble : public UnitTest
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
      report("Hubble");
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
      Hubble hubble;
      Position pos;

      // exercise
      hubble.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -32164000.0);
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
      Hubble hubble;

      // exercise
      hubble.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -32164000.0);
   }

   /*********************************************
    * name:    CUSTOM ORBIT SETUP
    * input:   custom initial conditions
    * output:  pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    *********************************************/
   void test_custom_orbit_setup()
   {
      // setup
      Hubble hubble;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      hubble.satelliteVelocityX = -5000.0;
      hubble.satelliteVelocityY = 1000.0;

      // exercise
      hubble.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), -32164000.0);
      assertEquals(hubble.satelliteVelocityX, 3500.0);
      assertEquals(hubble.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   nothing
    * output:  velocityX=0.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      Hubble hubble;
      Position pos;

      // exercise
      hubble.setupOrbit(pos);

      // verify
      assertEquals(hubble.satelliteVelocityX, 3500.0);
      assertEquals(hubble.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      Hubble hubble;
      Position pos;
      hubble.setupOrbit(pos);
      double initialVelocityX = hubble.satelliteVelocityX;
      double initialVelocityY = hubble.satelliteVelocityY;

      // exercise
      hubble.updateSatellite(pos, 10.0);

      // verify
      assertUnit(hubble.satelliteVelocityX == initialVelocityX);
      assertUnit(hubble.satelliteVelocityY > initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos updated correctly
    *********************************************/
   void test_update_position()
   {
      // setup
      Hubble hubble;
      Position pos;
      hubble.setupOrbit(pos);

      // exercise
      hubble.updateSatellite(pos, 10.0);

      // verify
      assertEqualsTolerance(pos.getMetersX(), 35000.0, 1.0);
      assertEqualsTolerance(pos.getMetersY(), -32163942.2, 1.0);
   }

   /*************************************************************************
    * name: TEST COLLISION
    * input: projectile and object positions
    * output: collision detected correctly
    **************************************************************************/
   void test_collision()
   {
      // setup
      Hubble hubble;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};