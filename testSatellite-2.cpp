/***********************************************************************
 * Header File:
 *    Test Satellite : Test the Satellite class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Satellite
 ************************************************************************/
#pragma once

#include "satellite.h"
#include "unitTest.h"
#include "collisions.h"

 /*******************************
  * TEST Satellite
  * A friend class for Satellite which contains the Satellite unit tests
  ********************************/

class TestSatellite : public UnitTest
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
      test_zeroPosition();
      test_highAltitude();
      test_collision();
      report("Satellite");
   }

private:

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   none
    * output:  satelliteVelocityX = 0.0
    *          satelliteVelocityY = 0.0
    *********************************************/
   void test_construct_default()
   {
      // setup
      Satellite satellite;

      // verify
      assertEquals(satellite.satelliteVelocityX, 0.0);
      assertEquals(satellite.satelliteVelocityY, 0.0);
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
      Satellite satellite;

      // exercise
      satellite.updateSatellite(pos, 0.0);

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
      Satellite satellite;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      satellite.satelliteVelocityX = -5000.0;
      satellite.satelliteVelocityY = 1000.0;

      // exercise
      satellite.updateSatellite(pos, 0.0);

      // verify
      assertEquals(pos.getMetersX(), 1000.0);
      assertEquals(pos.getMetersY(), 9000000.0);
      assertEquals(satellite.satelliteVelocityX, -5000.0);
      assertEquals(satellite.satelliteVelocityY, 1000.0);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   none
    * output:  velocityX=0.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      Satellite satellite;
      Position pos;

      // exercise
      satellite.updateSatellite(pos, 0.0);

      // verify
      assertEquals(satellite.satelliteVelocityX, 0.0);
      assertEquals(satellite.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      Satellite satellite;
      Position pos;
      satellite.updateSatellite(pos, 0.0);
      double initialVelocityX = satellite.satelliteVelocityX;
      double initialVelocityY = satellite.satelliteVelocityY;

      // exercise
      satellite.updateSatellite(pos, 10.0);

      // verify
      assertUnit(satellite.satelliteVelocityX < initialVelocityX);
      assertUnit(satellite.satelliteVelocityY < initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos updated correctly
    *********************************************/
   void test_update_position()
   {
      // setup
      Satellite satellite;
      Position pos;
      satellite.updateSatellite(pos, 0.0);

      // exercise
      satellite.updateSatellite(pos, 10.0);

      // verify
      assertUnit(pos.getMetersX() < 0.0);
      assertUnit(pos.getMetersY() < 0.0);
   }

   /*********************************************
    * name: ZERO POSITION
    * input:  pos = (0.0, 0.0), timePerFrame = 1.0
    * output:  pos moves away from center
    *********************************************/
   void test_zeroPosition()
   {
      // setup
      Satellite satellite;
      Position pos(0.0, 0.0); // Satellite at Earth's center
      satellite.satelliteVelocityX = 0.0;
      satellite.satelliteVelocityY = 0.0;
      double timePerFrame = 1.0;

      // exercise
      satellite.updateSatellite(pos, timePerFrame);

      // verify position
      assertUnit(pos.getMetersX() < 0.0); // Moves away from the center
      assertUnit(pos.getMetersY() < 0.0); // Moves away from the center
   }

   /*********************************************
    * name: HIGH ALTITUDE
    * input:  pos = (20000000.0, 20000000.0), timePerFrame = 1.0
    * output:  pos moves closer to Earth
    *********************************************/
   void test_highAltitude()
   {
      // setup
      Satellite satellite;
      Position pos(20000000.0, 20000000.0); // High altitude
      satellite.satelliteVelocityX = 0.0;
      satellite.satelliteVelocityY = 0.0;
      double timePerFrame = 1.0;

      // exercise
      satellite.updateSatellite(pos, timePerFrame);

      // verify position
      assertUnit(pos.getMetersX() < 20000000.0); // Moves closer to Earth
      assertUnit(pos.getMetersY() < 20000000.0); // Moves closer to Earth
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