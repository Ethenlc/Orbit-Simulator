/***********************************************************************
 * Header File:
 *    Test GPS : Test the GPS class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for GPS
 ************************************************************************/
#pragma once

#include "gps.h"
#include "unitTest.h"
#include "position.h"
#include "collisions.h"

 /*******************************
 * TEST GPS
 * A friend class for GPS which contains the GPS unit tests
 ********************************/
class TestGPS : public UnitTest
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
      report("GPS");
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
      GPS gps;
      Position pos;
      double startX = 0.0;
      double startY = 0.0;
      double velocityX = 0.0;
      double velocityY = 0.0;

      // exercise
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), 0.0);
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
      GPS gps;
      double startX = 120.0;
      double startY = 360.0;
      double velocityX = 0.0;
      double velocityY = 0.0;

      // exercise
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);

      // verify
      assertEquals(pos.getMetersX(), 120.0);
      assertEquals(pos.getMetersY(), 360.0);
   }

   /*********************************************
    * name:    CUSTOM ORBIT SETUP
    * input:   custom initial conditions
    * output:  pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    *********************************************/
   void test_custom_orbit_setup()
   {
      // setup
      GPS gps;
      Position pos;
      double startX = 1000.0;
      double startY = 9000000.0;
      double velocityX = -5000.0;
      double velocityY = 1000.0;

      // exercise
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);

      // verify
      assertEquals(pos.getMetersX(), 1000.0);
      assertEquals(pos.getMetersY(), 9000000.0);
      assertEquals(gps.satelliteVelocityX, -5000.0);
      assertEquals(gps.satelliteVelocityY, 1000.0);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   nothing
    * output:  velocityX=0.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      GPS gps;
      Position pos;
      double startX = 0.0;
      double startY = 0.0;
      double velocityX = 0.0;
      double velocityY = 0.0;

      // exercise
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);

      // verify
      assertEquals(gps.satelliteVelocityX, 0.0);
      assertEquals(gps.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      GPS gps;
      Position pos;
      double startX = 0.0;
      double startY = 0.0;
      double velocityX = 0.0;
      double velocityY = 0.0;
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);
      double initialVelocityX = gps.satelliteVelocityX;
      double initialVelocityY = gps.satelliteVelocityY;

      // exercise
      gps.updateSatellite(pos, 10.0);

      // verify
      assertUnit(gps.satelliteVelocityX != initialVelocityX);
      assertUnit(gps.satelliteVelocityY != initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos updated correctly
    *********************************************/
   void test_update_position()
   {
      // setup
      GPS gps;
      Position pos;
      double startX = 120.0;
      double startY = 360.0;
      double velocityX = 0.0;
      double velocityY = 0.0;
      gps.setupOrbit(pos, startX, startY, velocityX, velocityY);

      // exercise
      gps.updateSatellite(pos, 10.0);

      // verify
      assertUnit(pos.getMetersX() < startX);
      assertUnit(pos.getMetersY() < startY);
   }

   /*************************************************************************
    * name: TEST COLLISION
    * input: projectile and object positions
    * output: collision detected correctly
    **************************************************************************/
   void test_collision()
   {
      // setup
      Satellite satellite;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};