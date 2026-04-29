/***********************************************************************
 * Header File:
 *    Test Crew Dragon : Test the Crew Dragon class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Crew Dragon
 ************************************************************************/
#pragma once

#include "crewDragon.h"
#include "unitTest.h"
#include "position.h"
#include "collisions.h"

 /*******************************
 * TEST Starlink
 * A friend class for Starlink which contains the Starlink unit tests
 ********************************/
class TestCrewDragon : public UnitTest
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
      report("Crew Dragon");
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
      CrewDragon crewDragon;
      Position pos;

      // exercise
      crewDragon.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), 16000000.0);
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
      CrewDragon crewDragon;

      // exercise
      crewDragon.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), 16000000.0);
   }

   /*********************************************
    * name:    CUSTOM ORBIT SETUP
    * input:   custom initial conditions
    * output:  pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    *********************************************/
   void test_custom_orbit_setup()
   {
      // setup
      CrewDragon crewDragon;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      crewDragon.satelliteVelocityX = -5000.0;
      crewDragon.satelliteVelocityY = 1000.0;

      // exercise
      crewDragon.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), 0.0);
      assertEquals(pos.getMetersY(), 16000000.0);
      assertEquals(crewDragon.satelliteVelocityX, -5120.0);
      assertEquals(crewDragon.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    INITIAL VELOCITY
    * input:   nothing
    * output:  velocityX=-7120.0, velocityY=0.0
    *********************************************/
   void test_initial_velocity()
   {
      // setup
      CrewDragon crewDragon;
      Position pos;

      // exercise
      crewDragon.setupOrbit(pos);

      // verify
      assertEquals(crewDragon.satelliteVelocityX, -5120.0);
      assertEquals(crewDragon.satelliteVelocityY, 0.0);
   }

   /*********************************************
    * name:    UPDATE VELOCITY
    * input:   timeInterval=10.0
    * output:  velocityX and velocityY updated correctly
    *********************************************/
   void test_update_velocity()
   {
      // setup
      CrewDragon crewDragon;
      Position pos;
      crewDragon.setupOrbit(pos);
      double initialVelocityX = crewDragon.satelliteVelocityX;
      double initialVelocityY = crewDragon.satelliteVelocityY;

      // exercise
      crewDragon.updateSatellite(pos, 10.0);

      // verify
      assertUnit(crewDragon.satelliteVelocityX == initialVelocityX);
      assertUnit(crewDragon.satelliteVelocityY != initialVelocityY);
   }

   /*********************************************
    * name:    UPDATE POSITION
    * input:   timeInterval=10.0
    * output:  pos=(-51200.0, 15999766.3)
    *********************************************/
   void test_update_position()
   {
      // setup
      CrewDragon crewDragon;
      Position pos;
      crewDragon.setupOrbit(pos);

      // exercise
      crewDragon.updateSatellite(pos, 10.0);
		
      // verify
      assertEqualsTolerance(pos.getMetersX(), -51200.0, 1.0);
      assertEqualsTolerance(pos.getMetersY(), 15999766.3, 1.0);
   }

   /*************************************************************************
    * name: TEST COLLISION
    * input: projectile and object positions
    * output: collision detected correctly
    **************************************************************************/
   void test_collision()
   {
      // setup
      CrewDragon crewDragon;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};