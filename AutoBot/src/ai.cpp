/*----------------------------------------------------------------------------*/
/*
    Module:       ai.cpp                                                
    Author:       Zachary Spiggle                               
    Created:      7 Feb 2022                                               
    Description:  Defines functionality for AI to control robot and make decisions                    
*/
/*----------------------------------------------------------------------------*/

//Include statements
#include "DriverControls.h"
#include "arm_controller.h"
#include "vex.h"



namespace AI{

  int section = 0;
  double tTime = 0;
  double lastTime = 0;

  //Control functions NEED BETTER DEFINITIONS AND MORE
  void aispin(int speed){
    MR.spin(directionType::fwd, -speed, velocityUnits::rpm);
    ML.spin(directionType::rev, speed, velocityUnits::rpm);
  }

  void goForward(int speed){
    MR.spin(directionType::fwd, -speed, velocityUnits::rpm);
    ML.spin(directionType::rev, -speed, velocityUnits::rpm);
  }

  void reverse(int speed){
    MR.spin(directionType::fwd, speed, velocityUnits::rpm);
    ML.spin(directionType::rev, speed, velocityUnits::rpm);
  }

  void openClaw(int speed){
    ARM1.spin(directionType::fwd, speed, velocityUnits::rpm);
  }

  void closeClaw(int speed){
    ARM1.spin(directionType::rev, speed, velocityUnits::rpm);
  }

  void raiseArm(int speed)
  {
    AAM.spin(directionType::rev, speed, velocityUnits::rpm);
    AAM2.spin(directionType::fwd, speed, velocityUnits::rpm);
  }
  
  void lowerArm(int speed)
  {
    AAM.spin(directionType::fwd, speed, velocityUnits::rpm);
    AAM2.spin(directionType::rev, speed, velocityUnits::rpm);
  }

  void aistop()
  {
    MR.stop();
    ML.stop();
    ARM1.stop();
    AAM.stop();
    AAM2.stop();
  }
  void stopMove()
  {
    MR.stop();
    ML.stop();
  }
  void stopArm()
  {
    AAM.stop();
    AAM2.stop();
  }
  void stopClaw()
  {
    ARM1.stop();
  }



  //Empty Pseudocode, may be scrapped
  int checkFrontCarry(){


    return 0;
  }

  int checkBackCarry(){

    
    return 0;
  }

  void doTime()
  {
    lastTime = vex::timer::system();
  }

  
  //MAIN AI LOOP
  void AILoop()
  {


    if (section == 0)
    {
      doTime();
      tTime = 200;
      section++;
    }

    //RAISE ARM
    if ((vex::timer::system() - lastTime < tTime) && section == 1)
    {
      raiseArm(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 1)
    {
      doTime();
      tTime = 200;
      stopArm();
      section++;
    }



    //OPEN CLAW
    if ((vex::timer::system() - lastTime < tTime) && section == 2)
    {
      openClaw(100);
      goForward(150);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 2)
    {
      doTime();
      tTime = 1700;
      //stopClaw();
      section++;
    }

    //GO FOWARD
    if ((vex::timer::system() - lastTime < tTime) && section == 3)
    {
      goForward(150);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 3)
    {
      doTime();
      tTime = 500;
      section++;
      aistop();

    }

    //CLOSE CLAW
    if ((vex::timer::system() - lastTime < tTime) && section == 4)
    {
      closeClaw(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 4)
    {
      doTime();
      tTime = 2000;
      section++;
    }

    // REVERSE WITH GOAL
    if ((vex::timer::system() - lastTime < tTime) && section == 5)
    {
      reverse(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 5)
    {
      doTime();
      tTime = 500;
      section++;
      stopMove();
    }

    //RELEASE GOAL
    if ((vex::timer::system() - lastTime < tTime) && section == 6)
    {
      openClaw(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 6)
    {
      doTime();
      tTime = 700;
      section++;
      aistop();
    }

    //REVERSE WITHOUT GOAL
    if ((vex::timer::system() - lastTime < tTime) && section == 7)
    {
      reverse(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 7)
    {
      doTime();
      tTime = 110;
      section++;
      aistop();
    }

    //TURN
    if ((vex::timer::system() - lastTime < tTime) && section == 8)
    {
      aispin(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 8)
    {
      doTime();
      tTime = 3300;
      section++;
      aistop();
    }

    //FORWARD
    if ((vex::timer::system() - lastTime < tTime) && section == 9)
    {
      goForward(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 9)
    {
      doTime();
      tTime = 200;
      section++;
      aistop();
    }

    //CLOSE CLAW
    if ((vex::timer::system() - lastTime < tTime) && section == 10)
    {
      closeClaw(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 10)
    {
      doTime();
      tTime = 2700;
      section++;
    }

    //REVERSE 
    if ((vex::timer::system() - lastTime < tTime) && section == 11)
    {
      reverse(100);
    }
    else if ((vex::timer::system() - lastTime > tTime) && section == 11)
    {
      doTime();
      tTime = 1000;
      section++;
      aistop();
    }

  }


}