/***********************************************************************
 * Header File:
 *    Test Direction : Test the Direction class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Direction
 ************************************************************************/
#pragma once

#include "direction.h"
#include "unitTest.h"
#include <cmath>

 /*******************************
  * TEST DIRECTION
  * Unit tests for the Direction class
  ********************************/
class TestDirection : public UnitTest {
public:
   void run() {
      test_calculateGravityDirection_zero();
      test_calculateGravityDirection_positive();
      test_calculateGravityDirection_negative();
      test_calculateGravityDirection_mixed();
      test_calculateGravityDirection_large();
      report("Direction");
   }

private:
   /*********************************************
    * name:    TEST CALCULATE GRAVITY DIRECTION ZERO
    * input:   xs = 0.0, ys = 0.0
    * output:  direction = atan2(0.0, 0.0)
    *********************************************/
   void test_calculateGravityDirection_zero() {
      // setup
      Direction direction;
      double xs = 0.0;
      double ys = 0.0;

      // exercise
      double result = direction.calculateGravityDirection(xs, ys);

      // verify
      double expected = atan2(-xs, -ys);
      assertEquals(result, expected);
   }

   /*********************************************
    * name:    TEST CALCULATE GRAVITY DIRECTION POSITIVE
    * input:   xs = 10.0, ys = 20.0
    * output:  direction = atan2(-10.0, -20.0)
    *********************************************/
   void test_calculateGravityDirection_positive() {
      // setup
      Direction direction;
      double xs = 10.0;
      double ys = 20.0;

      // exercise
      double result = direction.calculateGravityDirection(xs, ys);

      // verify
      double expected = atan2(-xs, -ys);
      assertEquals(result, expected);
   }

   /*********************************************
    * name:    TEST CALCULATE GRAVITY DIRECTION NEGATIVE
    * input:   xs = -10.0, ys = -20.0
    * output:  direction = atan2(10.0, 20.0)
    *********************************************/
   void test_calculateGravityDirection_negative() {
      // setup
      Direction direction;
      double xs = -10.0;
      double ys = -20.0;

      // exercise
      double result = direction.calculateGravityDirection(xs, ys);

      // verify
      double expected = atan2(-xs, -ys);
      assertEquals(result, expected);
   }

   /*********************************************
    * name:    TEST CALCULATE GRAVITY DIRECTION MIXED
    * input:   xs = 10.0, ys = -20.0
    * output:  direction = atan2(-10.0, 20.0)
    *********************************************/
   void test_calculateGravityDirection_mixed() {
      // setup
      Direction direction;
      double xs = 10.0;
      double ys = -20.0;

      // exercise
      double result = direction.calculateGravityDirection(xs, ys);

      // verify
      double expected = atan2(-xs, -ys);
      assertEquals(result, expected);
   }

   /*********************************************
    * name:    TEST CALCULATE GRAVITY DIRECTION LARGE
    * input:   xs = 1e6, ys = 1e6
    * output:  direction = atan2(-1e6, -1e6)
    *********************************************/
   void test_calculateGravityDirection_large() {
      // setup
      Direction direction;
      double xs = 1e6;
      double ys = 1e6;

      // exercise
      double result = direction.calculateGravityDirection(xs, ys);

      // verify
      double expected = atan2(-xs, -ys);
      assertEquals(result, expected);
   }
};