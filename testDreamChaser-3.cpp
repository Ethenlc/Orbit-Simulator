/***********************************************************************
 * Header File:
 *    Test Dream Chaser : Test the Hubble class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Dream Chaser ship
 ************************************************************************/
#pragma once

#include "dreamChaser.h"
#include "position.h"
#include "collisions.h"
#include "unitTest.h"

 /************************************************************************
  * TEST DreamChaser
  * A friend class for DreamChaser which contains its unit tests
  *************************************************************************/
class TestDreamChaser : public UnitTest
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
      test_rotateLeft();
      test_rotateRight();
      test_applyThrust();
      test_launchProjectile();
      test_updateProjectile();
      test_projectileCollision();
      report("Dream Chaser");
   }
private:
   /*************************************************************************
    * name: test_construct_default
    * input: none
    * output: metersX = 0.0, metersY = 0.0
    **************************************************************************/
   void test_construct_default()
   {
      // setup
      DreamChaser dreamChaser;
      Position pos;

      // exercise
      dreamChaser.setupOrbit(pos);
      // verify
      assertEquals(pos.getMetersX(), -450.0);
      assertEquals(pos.getMetersY(), 450.0);
   }

   /*************************************************************************
    * name: test_construct_nonDefault
    * input: x=120.0, y=360.0
    * output: pos=(120.0, 360.0)
    **************************************************************************/
   void test_construct_nonDefault()
   {
      // setup
      Position pos(120.0, 360.0);
      DreamChaser dreamChaser;

      // exercise
      dreamChaser.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), -450.0);
      assertEquals(pos.getMetersY(), 450.0);
   }

   /*************************************************************************
    * name: test_custom_orbit_setup
    * input: custom initial conditions
    * output: pos=(1000.0, 9000000.0), velocityX=-5000.0, velocityY=1000.0
    **************************************************************************/
   void test_custom_orbit_setup()
   {
      // setup
      DreamChaser dreamChaser;
      Position pos;
      pos.setMetersX(1000.0);
      pos.setMetersY(9000000.0);
      dreamChaser.setVelocity(-5000, 1000);

      // exercise
      dreamChaser.setupOrbit(pos);

      // verify
      assertEquals(pos.getMetersX(), -450.0);
      assertEquals(pos.getMetersY(), 450.0);
      assertEquals(dreamChaser.getSatelliteVelocityX(), 0.0);
      assertEquals(dreamChaser.getSatelliteVelocityY(), -2000.0);
   }

   /*************************************************************************
    * name: test_initial_velocity
    * input: none
    * output: velocityX=0.0, velocityY=0.0
    **************************************************************************/
   void test_initial_velocity()
   {
      // setup
      DreamChaser dreamChaser;
      Position pos;

      // exercise
      dreamChaser.setupOrbit(pos);

      // verify
      assertEquals(dreamChaser.getSatelliteVelocityX(), 0.0);
      assertEquals(dreamChaser.getSatelliteVelocityY(), -2000.0);
   }

   /*************************************************************************
    * name: test_update_velocity
    * input: timeInterval=10.0
    * output: velocityX and velocityY updated correctly
    **************************************************************************/
   void test_update_velocity()
   {
      // setup
      DreamChaser dreamChaser;
      Position pos;
      dreamChaser.setupOrbit(pos);
      double initialVelocityX = dreamChaser.getSatelliteVelocityX();
      double initialVelocityY = dreamChaser.getSatelliteVelocityY();

      // exercise
      dreamChaser.updateSatellite(pos, 10.0);

      // verify
      assertUnit(dreamChaser.getSatelliteVelocityX() > initialVelocityX);
      assertUnit(dreamChaser.getSatelliteVelocityY() < initialVelocityY);
   }

   /*************************************************************************
    * name: test_update_position
    * input: timeInterval=10.0
    * output: pos updated correctly
    **************************************************************************/
   void test_update_position()
   {
      // setup
      DreamChaser dreamChaser;
      Position pos;
      dreamChaser.setupOrbit(pos);

      // exercise
      dreamChaser.updateSatellite(pos, 10.0);

      // verify
      assertUnit(pos.getMetersX() < 0.0);
      assertUnit(pos.getMetersY() > 0.0);
   }

   /*************************************************************************
    * name: test_rotateLeft
    * input: none
    * output: angle = -0.1
    **************************************************************************/
   void test_rotateLeft()
   {
      // setup
      DreamChaser dreamChaser;
      double angle = dreamChaser.getAngle();

      // exercise
      dreamChaser.rotateLeft();

      // verify
      assertEquals(dreamChaser.getAngle(), angle - 0.1);
   }

   /*************************************************************************
    * name: test_rotateRight
    * input: none
    * output: angle = +0.1
    **************************************************************************/
   void test_rotateRight()
   {
      // setup
      DreamChaser dreamChaser;
      double angle = dreamChaser.getAngle();

      // exercise
      dreamChaser.rotateRight();

      // verify
      assertEquals(dreamChaser.getAngle(), angle + 0.1);
   }

   /*************************************************************************
    * name: test_applyThrust
    * input: 1.0 seconds
    * output: satelliteVelocityX = 0.0, satelliteVelocityY = -1998.0
    **************************************************************************/
   void test_applyThrust()
   {
      // setup
      DreamChaser dreamChaser;
      double satelliteVelocityX = dreamChaser.getPosX();
      double satelliteVelocityY = dreamChaser.getPosY();
      double timeFrame = 1.0;

      // exercise
      dreamChaser.applyThrust(timeFrame);

      // verify
      assertUnit(dreamChaser.getSatelliteVelocityX() == 0.0);
      assertUnit(dreamChaser.getSatelliteVelocityY() < 1998.0);
   }

   /*************************************************************************
    * name: test_launchProjectile
    * input: none
    * output: projectile launched correctly
    **************************************************************************/
   void test_launchProjectile()
   {
      // setup
      DreamChaser dreamChaser;
      dreamChaser.setPosition(1000.0, 1000.0);
      dreamChaser.setVelocity(0.0, 0.0);
      double initialAngle = dreamChaser.getAngle();

      // exercise
      dreamChaser.launchProjectile();
      
      // verify
      Position projectilePos = dreamChaser.getProjectilePos();
      assertUnit(projectilePos.getMetersX() == 1000.0);
      assertUnit(projectilePos.getMetersY() == 1000.0);
   }

   /*************************************************************************
    * name: test_updateProjectile
    * input: timeInterval=1.0
    * output: projectile position updated correctly
    **************************************************************************/
   void test_updateProjectile()
   {
      // setup
      DreamChaser dreamChaser;
      dreamChaser.setPosition(1000.0, 1000.0);
      dreamChaser.setVelocity(0.0, 0.0);
      dreamChaser.rotateRight(); // Set a non-zero angle
      dreamChaser.launchProjectile();
      Position initialPos = dreamChaser.getProjectilePos();

      // exercise
      dreamChaser.updateProjectile(1.0);

      // verify
      Position updatedPos = dreamChaser.getProjectilePos();
      assertUnit(updatedPos.getMetersX() != initialPos.getMetersX());
      assertUnit(updatedPos.getMetersY() != initialPos.getMetersY());
   }

   /*************************************************************************
    * name: TEST PROJECTILE COLLISION
    * input: projectile and object positions
    * output: collision detected correctly
    **************************************************************************/
   void test_projectileCollision()
   {
      // setup
      DreamChaser dreamChaser;
      Position projectilePos(0.0, 0.0);
      Position objectPos(1.0, 1.0);
      double threshold = 1.5;

      // exercise
      bool collision = Collisions::checkCollision(projectilePos, objectPos, threshold);

      // verify
      assertUnit(collision == true);
   }
};