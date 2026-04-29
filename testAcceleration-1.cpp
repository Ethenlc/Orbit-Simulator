/***********************************************************************
* Header File:
*    Test Acceleration : Test the Acceleration class
* Authors:
*    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* Summary:
*    All the unit tests for Acceleration
************************************************************************/
#pragma once

#include "acceleration.h"
#include "unitTest.h"

/************************************************************************
* TEST Acceleration
* A friend class for Acceleration which contains the Acceleration unit tests
*************************************************************************/

class TestAcceleration : public UnitTest {
public:
   void run() {
      test_calculateAltitude_values();
      test_calculateGravity_1000Meters();
      test_calculateHorizontalAcceleration_values();
      test_calculateVerticalAcceleration_values();
      report("Acceleration");
   }

private:
   /*************************************************************************
   * name: CALCULATE ALTITUDE
   * input: x = 1000; y = 2000
   * output: sqrt(x * x + y * y) - 6378000.0
   *************************************************************************/
   void test_calculateAltitude_values() {
      // setup
      Acceleration a;
      double x = 1000.0;
      double y = 2000.0;

      // exercise
      double result = a.calculateAltitude(x, y);

      // verify
      double expected = sqrt(x * x + y * y) - 6378000.0;
      assertEquals(result, expected);
   }

   /****************************************************************************
   * name: CALCULATE GRAVITY
   * input: altitude = 1000
   * output: 9.80665 * pow(6378000.0 / (6378000.0 + altitude), 2)
   *****************************************************************************/
   void test_calculateGravity_1000Meters() {
      // setup
      Acceleration a;
      double altitude = 1000.0;

      // exercise
      double result = a.calculateGravity(altitude);

      // verify
      double expected = 9.80665 * pow(6378000.0 / (6378000.0 + altitude), 2);
      assertEquals(result, expected);
   }

   /****************************************************************************
   * name: HORIZONTAL ACCELERATION
   * input: acceleration = 9.8 angle = 30.0
   * output: acceleration * sin(angle)
   *****************************************************************************/
   void test_calculateHorizontalAcceleration_values() {
      // setup
      Acceleration a;
      double acceleration = 9.8;
      double angle = 30.0;

      // exercise
      double result = a.calculateHorizontalAcceleration(acceleration, angle);

      // verify
      double expected = acceleration * sin(angle);
      assertEquals(result, expected);
   }

   /****************************************************************************
   * name: VERTICAL ACCELERATION
   * input: acceleration = 9.8 angle = 30.0
   * output: acceleration * cos(angle)
   *****************************************************************************/
   void test_calculateVerticalAcceleration_values()
   {
      // setup
      Acceleration a;
      double acceleration = 9.8;
      double angle = 30.0;

      // exercise
      double result = a.calculateVerticalAcceleration(acceleration, angle);

      // verify
      double expected = acceleration * cos(angle);
      assertEquals(result, expected);
   }
};

