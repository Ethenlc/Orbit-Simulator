/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testSatellite.cpp"
#include "testHubble.cpp"
#include "testGps.cpp"
#include "testSputnik.cpp"
#include "testStarlink.cpp"
#include "testCrewDragon.cpp"
#include "testDreamChaser.cpp"
#include "testDirection.cpp"
#include "testAcceleration.cpp"
#include "testTimeUtils.cpp"
#include "testCollisions.cpp"

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
   AllocConsole();
   FILE* stream;
   errno_t err;
   err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

   TestPosition().run();
	TestSatellite().run();
	TestAcceleration().run();
	TestDirection().run();
	TestHubble().run();
	TestGPS().run();
	TestSputnik().run();
	TestStarlink().run();
	TestCrewDragon().run();
	TestDreamChaser().run();
	TestTimeUtils().run();
	TestCollisions().run();
}
