/*************************************************************
* 1. Name:
*      Amelia Tuttle, Ema Guillen de Reyes, Ethan Campbell
* 2. Assignment Name:
*      Lab 07: Orbit Simulator
* 3. Assignment Description:
*      Simulate satellites orbiting the earth
* 4. What was the hardest part? Be as specific as possible.
*      Creating the function to update the satellite's position every frame
* 5. How long did it take for you to complete the assignment?
*      3.5 hrs
*****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "test.h"
#include "satellite.h"
#include "time_utils.h"
#include "direction.h"
#include "acceleration.h"
#include "hubble.h"
#include "gps.h"
#include "crewDragon.h"
#include "starlink.h"
#include "sputnik.h"
#include "dreamChaser.h"
#include "collisions.h"
#include "fragment.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    // Constants
    const int MAX_FRAGMENTS = 20;
    const int numStars = 200;

    // Constructor
    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight)
    {
        // Initialize satellite positions randomly within the screen
        ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        // Initialize stars with random positions and phases
        for (int i = 0; i < numStars; i++)
        {
            Position ptStar;
            ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
            ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
            stars.push_back(ptStar);
            phases.push_back(rand() % 255);
        }

        // Initialize angles and positions
        angleShip = 0.0;
        angleEarth = 0.0;
        phaseStar = 0;
        gpsAngle = 0.0;

        // Setup specific satellite orbits
        hubble.setupOrbit(ptHubble);
        gps1.setupOrbit(ptGPS1, 0.0, 26560000.0, -3880.0, 0.0);
        gps2.setupOrbit(ptGPS2, 23001634.72, 13280000.0, -1940.00, 3360.18);
        gps3.setupOrbit(ptGPS3, 23001634.72, -13280000.0, 1940.0, 3360.18);
        gps4.setupOrbit(ptGPS4, 0.0, -26560000.0, 3880.0, 0.0);
        gps5.setupOrbit(ptGPS5, -23001634.72, -13280000.0, 1940.0, -3360.18);
        gps6.setupOrbit(ptGPS6, -23001634.72, 13280000, -1940.0, -3360.18);
        crewDragon.setupOrbit(ptCrewDragon);
        sputnik.setupOrbit(ptSputnik);
        starlink.setupOrbit(ptStarlink);
    }

    // Fragment generation method
    void generateFragments(const Position& collisionPos) {
        // Remove inactive fragments first
        fragments.erase(
            std::remove_if(fragments.begin(), fragments.end(),
                [](const Fragment& f) { return !f.isActive(); }),
            fragments.end()
        );

        // Add new fragments
        int numFragments = std::min(MAX_FRAGMENTS, 10); // Limit fragment count
        for (int i = 0; i < numFragments; ++i) {
            if (fragments.size() < MAX_FRAGMENTS) {
                Fragment fragment;
                // Spread fragments evenly in a circle
                double angle = (2 * M_PI * i) / numFragments;
                fragment.initialize(collisionPos, angle);
                fragments.push_back(fragment);
            }
        }
    }

    // Fragment update and drawing method
    void updateAndDrawFragments(ogstream& gout, double timePerFrame) {
        for (auto& fragment : fragments) {
            if (fragment.isActive()) {
                fragment.update(timePerFrame);
                gout.drawFragment(fragment.getPosition(), angleShip);
            }
        }
    }

    // Projectile collision check method
    void checkProjectileCollisions(Position& projectile, std::vector<bool>& objectsToRemove) {
        std::vector<Position> allObjects = {
            ptCrewDragon, ptHubble, ptSputnik, ptStarlink,
            ptGPS1, ptGPS2, ptGPS3, ptGPS4, ptGPS5, ptGPS6,
             ptStar // Including potential collision targets
        };

        double collisionThreshold = 10.0;
        size_t collisionIndex = Collisions::checkProjectileCollisions(
            projectile,
            allObjects,
            collisionThreshold,
            objectsToRemove
        );

        // If a collision occurred, generate fragments
        if (collisionIndex != -1) {
            generateFragments(allObjects[collisionIndex]);
        }
    }

    // Earth collision check method
    void checkEarthCollisions() {
        std::vector<Position> satellitePositions = {
            ptCrewDragon, ptHubble, ptSputnik, ptStarlink,
            ptGPS1, ptGPS2, ptGPS3, ptGPS4, ptGPS5, ptGPS6, ptShip
        };

        // Earth's position and collision threshold
        Position earthCenter(0.0, 0.0); // Earth's center is at (0,0)
        double collisionThreshold = 6500000.0; // Earth's radius in meters

        // Track satellites to remove
        std::vector<bool> objectsToRemove(satellitePositions.size(), false);

        for (size_t i = 0; i < satellitePositions.size(); ++i) {
            double distance = sqrt(
                pow(satellitePositions[i].getMetersX(), 2) +
                pow(satellitePositions[i].getMetersY(), 2)
            );

            if (distance <= collisionThreshold) {
                // Collision detected
                objectsToRemove[i] = true;

                // Generate fragments at collision position
                generateFragments(satellitePositions[i]);
            }
        }

        // Remove collided satellites
        for (size_t i = 0; i < objectsToRemove.size(); ++i) {
            if (objectsToRemove[i]) {
                // Move satellite off-screen (inactive state)
                satellitePositions[i].setPixelsX(-9999);
                satellitePositions[i].setPixelsY(-9999);

                // Update corresponding satellite position
                switch (i) {
                case 0: ptCrewDragon = satellitePositions[i]; break;
                case 1: ptHubble = satellitePositions[i]; break;
                case 2: ptSputnik = satellitePositions[i]; break;
                case 3: ptStarlink = satellitePositions[i]; break;
                case 4: ptGPS1 = satellitePositions[i]; break;
                case 5: ptGPS2 = satellitePositions[i]; break;
                case 6: ptGPS3 = satellitePositions[i]; break;
                case 7: ptGPS4 = satellitePositions[i]; break;
                case 8: ptGPS5 = satellitePositions[i]; break;
                case 9: ptGPS6 = satellitePositions[i]; break;
                }
            }
        }
    }

    // Satellite collision check method
    void checkSatelliteCollisions() {
        vector<Position> satellitePositions = {
            ptCrewDragon, ptHubble, ptSputnik, ptStarlink,
            ptGPS1, ptGPS2, ptGPS3, ptGPS4, ptGPS5, ptGPS6, ptShip
        };

        double collisionThreshold = 25.0;
        Collisions::checkSatelliteCollisions(satellitePositions, collisionThreshold);
    }

    // Member variables
    Satellite satellite;
    Hubble hubble;
    GPS gps1, gps2, gps3, gps4, gps5, gps6;
    CrewDragon crewDragon;
    Sputnik sputnik;
    Starlink starlink;
    DreamChaser dreamChaser;
    TimeUtils timeutils;
    Acceleration acceleration;
    Direction direction;
    Fragment fragment;

    // Position tracking
    Position ptHubble;
    Position ptSputnik;
    Position ptStarlink;
    Position ptCrewDragon;
    Position ptShip;
    Position projectile;
    Position ptGPS1, ptGPS2, ptGPS3, ptGPS4, ptGPS5, ptGPS6;
    Position ptStar;
    Position ptUpperRight;
    Position pt;

    // Star-related vectors
    std::vector<Position> stars;
    std::vector<unsigned char> phases;

    // Fragment vector
    std::vector<Fragment> fragments;

    // Angle tracking
    unsigned char phaseStar;
    double angleShip;
    double angleEarth;
    double gpsAngle;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Demo* pDemo = (Demo*)p;

    // Define constants based on assignment instructions
    int hoursDay = 24;
    int minutesHour = 60;
    int frameRate = 30;

    // Calculate time dilation and time per frame
    double timeDilation = pDemo->timeutils.calculateTimeDilation(hoursDay, minutesHour);
    double timePerFrame = pDemo->timeutils.calculateTimePerFrame(timeDilation, frameRate);

    // Maybe start rotating
    pDemo->hubble.maybeStartRotating();
    pDemo->crewDragon.maybeStartRotating();
    pDemo->sputnik.maybeStartRotating();
    pDemo->starlink.maybeStartRotating();
    pDemo->gps1.maybeStartRotating();
    pDemo->gps2.maybeStartRotating();
    pDemo->gps3.maybeStartRotating();
    pDemo->gps4.maybeStartRotating();
    pDemo->gps5.maybeStartRotating();
    pDemo->gps6.maybeStartRotating();

    // Update rotation angles
    pDemo->hubble.updateRotation(timePerFrame);
    pDemo->crewDragon.updateRotation(timePerFrame);
    pDemo->sputnik.updateRotation(timePerFrame);
    pDemo->starlink.updateRotation(timePerFrame);
    pDemo->gps1.updateRotation(timePerFrame);
    pDemo->gps2.updateRotation(timePerFrame);
    pDemo->gps3.updateRotation(timePerFrame);
    pDemo->gps4.updateRotation(timePerFrame);
    pDemo->gps5.updateRotation(timePerFrame);
    pDemo->gps6.updateRotation(timePerFrame);

    // Update the satellites' positions and velocities
    pDemo->gps1.updateSatellite(pDemo->ptGPS1, timePerFrame);
    pDemo->gps2.updateSatellite(pDemo->ptGPS2, timePerFrame);
    pDemo->gps3.updateSatellite(pDemo->ptGPS3, timePerFrame);
    pDemo->gps4.updateSatellite(pDemo->ptGPS4, timePerFrame);
    pDemo->gps5.updateSatellite(pDemo->ptGPS5, timePerFrame);
    pDemo->gps6.updateSatellite(pDemo->ptGPS6, timePerFrame);
    pDemo->hubble.updateSatellite(pDemo->ptHubble, timePerFrame);
    pDemo->crewDragon.updateSatellite(pDemo->ptCrewDragon, timePerFrame);
    pDemo->sputnik.updateSatellite(pDemo->ptSputnik, timePerFrame);
    pDemo->starlink.updateSatellite(pDemo->ptStarlink, timePerFrame);
    pDemo->dreamChaser.updateSatellite(pDemo->ptShip, timePerFrame);
    pDemo->dreamChaser.updateProjectile(timePerFrame);

    // Sync pDemo->ptShip with DreamChaser's internal position
    pDemo->ptShip.setMetersX(pDemo->dreamChaser.getPosX());
    pDemo->ptShip.setMetersY(pDemo->dreamChaser.getPosY());

    // Sync projectile position
    pDemo->projectile.setMetersX(pDemo->dreamChaser.getProjectilePos().getMetersX());
    pDemo->projectile.setMetersY(pDemo->dreamChaser.getProjectilePos().getMetersY());

    // Create a vector to track which objects should be removed
    std::vector<bool> objectsToRemove(13, false); // 12 satellites + 1 projectile
    double collisionThreshold = 10.0;
    pDemo->checkProjectileCollisions(pDemo->projectile, objectsToRemove);

    // Modify collision checks to use the new parameter
    pDemo->checkProjectileCollisions(pDemo->projectile, objectsToRemove);
    pDemo->checkEarthCollisions();

    // Remove marked objects
    if (objectsToRemove[0]) pDemo->ptCrewDragon.setPixelsX(-9999);
    if (objectsToRemove[1]) pDemo->ptHubble.setPixelsX(-9999);
    if (objectsToRemove[2]) pDemo->ptSputnik.setPixelsX(-9999);
    if (objectsToRemove[3]) pDemo->ptStarlink.setPixelsX(-9999);
    if (objectsToRemove[4]) pDemo->ptGPS1.setPixelsX(-9999);
    if (objectsToRemove[5]) pDemo->ptGPS2.setPixelsX(-9999);
    if (objectsToRemove[6]) pDemo->ptGPS3.setPixelsX(-9999);
    if (objectsToRemove[7]) pDemo->ptGPS4.setPixelsX(-9999);
    if (objectsToRemove[8]) pDemo->ptGPS5.setPixelsX(-9999);
    if (objectsToRemove[9]) pDemo->ptGPS6.setPixelsX(-9999);

    // Remove projectile
    if (objectsToRemove[10]) {
        pDemo->projectile.setPixelsX(-9999);
        pDemo->projectile.setPixelsY(-9999);
    }

    // Check for satellite and Earth collisions
    pDemo->checkSatelliteCollisions();
    pDemo->checkEarthCollisions();

    //
    // accept input
    //

    // move by a little
    if (pUI->isUp())
    {
        pDemo->dreamChaser.setThrustAcceleration(2.0); // Set thrust when up key is pressed
        pDemo->dreamChaser.applyThrust(timePerFrame);
    }
    if (pUI->isLeft())
        pDemo->dreamChaser.rotateLeft();
    if (pUI->isRight())
        pDemo->dreamChaser.rotateRight();
    if (pUI->isSpace())
        pDemo->dreamChaser.launchProjectile();

    //
    // perform all the game logic
    //

    // rotate the earth
    // new way uses RotationPerFrame instead of manual rotation
    pDemo->angleEarth += pDemo->timeutils.calculateRotationPerFrame(timeDilation, frameRate, 86400.0);
    pDemo->phaseStar++;

    //
    // draw everything
    //

    Position pt;
    ogstream gout(pt);

    // draw satellites
    gout.drawCrewDragon(pDemo->ptCrewDragon, pDemo->crewDragon.getRotationAngle());
    gout.drawHubble(pDemo->ptHubble, pDemo->hubble.getRotationAngle());
    gout.drawSputnik(pDemo->ptSputnik, pDemo->sputnik.getRotationAngle());
    gout.drawStarlink(pDemo->ptStarlink, pDemo->starlink.getRotationAngle());
    gout.drawShip(pDemo->ptShip, pDemo->dreamChaser.getAngle(), pUI->isUp());
    gout.drawGPS(pDemo->ptGPS1, pDemo->gps1.getRotationAngle());
    gout.drawGPS(pDemo->ptGPS2, pDemo->gps2.getRotationAngle());
    gout.drawGPS(pDemo->ptGPS3, pDemo->gps3.getRotationAngle());
    gout.drawGPS(pDemo->ptGPS4, pDemo->gps4.getRotationAngle());
    gout.drawGPS(pDemo->ptGPS5, pDemo->gps5.getRotationAngle());
    gout.drawGPS(pDemo->ptGPS6, pDemo->gps6.getRotationAngle());
    gout.drawProjectile(pDemo->projectile);

    //// draw parts
    //pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
    //gout.drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
    //gout.drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptGPS1.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptGPS1.getPixelsY() + 20);
    //gout.drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
    //gout.drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set

    // draw fragments
    pDemo->updateAndDrawFragments(gout, timePerFrame);

   // draw a single star
   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // Draw stars with independent twinkling phases
   for (int i = 0; i < pDemo->numStars; i++)
   {
      gout.drawStar(pDemo->stars[i], pDemo->phases[i]);
      pDemo->phases[i]++;
   }

   // Draw the earth
   pt.setMeters(0.0, 0.0);
   gout.drawEarth(pt, pDemo->angleEarth);
}

double Position::metersFromPixels = 1.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
