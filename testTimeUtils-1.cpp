/***********************************************************************
 * Header File:
 *    Test Time Utils : Test the Time Utils class
 * Authors:
 *    Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
 * Summary:
 *    All the unit tests for Time Utils
 ************************************************************************/
#pragma once

#include "time_utils.h"
#include "unitTest.h"

 /************************************************************************
 * TEST Time Utils
 * A friend class for Time Utils which contains the Time Utils unit tests
 ************************************************************************/
class TestTimeUtils : public UnitTest
{
public:
   void run()
   {
      // Tests for calculateTimeDilation
      test_calculateTimeDilation_default();
      test_calculateTimeDilation_custom();
      test_calculateTimeDilation_zero();

      // Tests for calculateTimePerFrame
      test_calculateTimePerFrame_standard();

      // Tests for calculateRotationPerFrame
      test_calculateRotationPerFrame_standard();

      report("TimeUtils");
   }

private:
   /*********************************************
    * name: DEFAULT
    * input: 24 hours, 60 minutes
    * output: 1440
    *********************************************/
   void test_calculateTimeDilation_default()
   {
      // Setup
      TimeUtils timeUtils;

      // Exercise
      double dilation = timeUtils.calculateTimeDilation();

      // Verify
      assertEquals(dilation, 1440.0); // 24 * 60
   }

   /*********************************************
    * name: CUSTOM INPUTS
    * input: 12 hours, 50 minutes
    * output: 600
    *********************************************/
   void test_calculateTimeDilation_custom()
   {
      // Setup
      TimeUtils timeUtils;

      // Exercise
      double dilation = timeUtils.calculateTimeDilation(12, 50);

      // Verify
      assertEquals(dilation, 600.0); // 12 * 50
   }

   /*********************************************
    * name: ZERO INPUTS
    * input: 0 hours, 60 minutes
    * output: 0
    *********************************************/
   void test_calculateTimeDilation_zero()
   {
      // Setup
      TimeUtils timeUtils;

      // Exercise
      double dilation = timeUtils.calculateTimeDilation(0, 60);

      // Verify
      assertEquals(dilation, 0.0);
   }

   /*********************************************
    * name: STANDARD INPUT
    * input: 1440 time dilation, 30 frame rate
    * output: 48.0
    *********************************************/
   void test_calculateTimePerFrame_standard()
   {
      // Setup
      TimeUtils timeUtils;

      // Exercise
      double timePerFrame = timeUtils.calculateTimePerFrame(1440.0, 30);

      // Verify
      assertEquals(timePerFrame, 48.0); // 1440 / 30
   }

   /*********************************************
    * name: STANDARD INPUT
    * input: 1440 time dilation, 30 frame rate, 86400 seconds in a day
    * output: -0.2618
    *********************************************/
   void test_calculateRotationPerFrame_standard()
   {
      // Setup
      TimeUtils timeUtils;

      // Exercise
      double rotation = timeUtils.calculateRotationPerFrame(1440.0, 30, 86400.0);

      // Verify
      double expected = -(2.0 * 3.14159 / 30) * (1440.0 / 86400.0);
      assertEqualsTolerance(rotation, expected, 0.0001);
   }
};

