/*----------------------------------------------------------------------------*/
/*
    Module:       main.cpp                                                
    Authors:      Davis Tiegeler, Zachary Spiggle                                       
    Created:      18 Jan 2022                                               
    Description:  Main loop of the robot's program                             
*/
/*----------------------------------------------------------------------------*/


/* ---- START VEXCODE CONFIGURED DEVICES ----
Robot Configuration:
[Name]               [Type]        [Port(s)]
ML                   motor         14              
ML2                  motor         16  
MR                   motor         15
MR2                  motor         17  
ARM1                 motor         11
accel                inertial      -

AAM                  motor         20
AAM2                 motor         19

---- END VEXCODE CONFIGURED DEVICES ----*/

//Includes
#include "vex.h"
#include "DriverControls.h"
#include "ai.h"

using namespace vex;

competition comp;

//Main Loop
int main() {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  

  //Infinite loop until program is force stopped
  while (true)
  {
    // Main Loop
    if (comp.isEnabled())
    {
      if (comp.isAutonomous())
      {
        AI::AILoop();
      }
      if (comp.isDriverControl())
      {
        AI::section = 0;
        control::ControlBot();
      }
    }
    if (!comp.isEnabled())
    {
      //Reset our AI program counter
      AI::section = 0;
    }
  }
}
