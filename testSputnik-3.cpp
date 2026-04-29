/***********************************************************************
 * Header File:
 *    Test Sputnik : Test the Sputnik class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Sputnik
 ************************************************************************/
#pragma once

#include "sputnik.h"
#include "unitTest.h"
#include "position.h"
#include "collisions.h"

 /*******************************
 * TEST Sputnik
 * A friend class for Sputnik which contains the Sputnik unit tests
 ********************************/
class TestSputnik : public UnitTest
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
      report("Sputnik");
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
      Sputnik sputnik;
      Position pos;

      // exercise
      sputnik.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), -36515095.13);
      assertEquals(pos.getMetersY(), 21082000.0);
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
      Sputnik sputnik;

      // exercise
      sputnik.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), -36515095.13);
      assertEquals(pos.getMetersY(), 21082000.0);
   }

   /*********************************************
    * name:    CUSTOM ORBIT SETUP
    * input:   custom initial conditions
    * output:  pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    *********************************************/
   void test_custom_orbit_setup()
   {
      // setup
      Sputnik sputnik;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      sputnik.satelliteVelocityX = -5000.0;
      sputnik.satelliteVelocityY = 1000.0;

      // exercise
      sputnik.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), -36515095.13);
      assertEquals(pos.getMetersY(), 21082000.0);
      assertEquals(sputnik.satelliteVelocityX, 1750.0);
      assertEquals(sputnik.satelliteVelocityY, 2384.68);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   nothing
    * output:  velocityX=0.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      Sputnik sputnik;
      Position pos;

      // exercise
      sputnik.setupOrbit(pos);

      // verify
      assertEquals(sputnik.satelliteVelocityX, 1750.0);
      assertEquals(sputnik.satelliteVelocityY, 2384.68);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      Sputnik sputnik;
      Position pos;
      sputnik.setupOrbit(pos);
      double initialVelocityX = sputnik.satelliteVelocityX;
      double initialVelocityY = sputnik.satelliteVelocityY;

      // exercise
      sputnik.updateSatellite(pos, 10.0);

      // verify
      assertUnit(sputnik.satelliteVelocityX > initialVelocityX);
      assertUnit(sputnik.satelliteVelocityY < initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos updated correctly
    *********************************************/
   void test_update_position()
   {
      // setup
      Sputnik sputnik;
      Position pos;
      sputnik.setupOrbit(pos);

      // exercise
      sputnik.updateSatellite(pos, 10.0);
      
      // verify
      assertEqualsTolerance(pos.getMetersX(), -36497566.0, 1.0);
      assertEqualsTolerance(pos.getMetersY(), 21105830.0, 1.0);
   }

   /*************************************************************************
    * name: TEST COLLISION
    * input: projectile and object positions
    * output: collision detected correctly
    **************************************************************************/
   void test_collision()
   {
      // setup
      Sputnik sputnik;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};