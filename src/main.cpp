/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ferch                                                     */
/*    Created:      8/12/2026, 5:12:02 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain brain1 = brain();

controller controller1 = controller(primary);

//drivetrain (seen from top front is 1 back is 4)
motor motorLeft1 = motor(PORT1, ratio6_1, false);
motor motorLeft2 = motor(PORT2, ratio6_1, false);
motor motorLeft3 = motor(PORT3, ratio6_1, false);
motor motorLeft4 = motor(PORT4, ratio6_1, false);
motor_group driveTrainLeft = motor_group(motorLeft1, motorLeft2, motorLeft3, motorLeft4);

motor motorRight1 = motor(PORT9, ratio6_1, true);
motor motorRight2 = motor(PORT10, ratio6_1, true);
motor motorRight3 = motor(PORT11, ratio6_1, true);
motor motorRight4 = motor(PORT12, ratio6_1, true);
motor_group driveTrainRight = motor_group(motorRight1, motorRight2, motorRight3, motorRight4);

inertial inertiaSensor = inertial(PORT5);

smartdrive driveTrain = smartdrive(
  driveTrainLeft,
  driveTrainRight, 
  inertiaSensor,
  9.425, //wheel circumference
  10, //track width distance between left and right wheels
  10.5, //wheel base distance between fron and back wheels
  inches, //distance type
  1.0 // external gear ratio9
);

//motores Elevador
motor motorElevatorUp = motor(PORT16, ratio18_1, false); 
motor motorElevatorDown = motor(PORT17, ratio18_1, false);
motor_group elevatorMotors = motor_group(motorElevatorUp, motorElevatorDown);

void printHeading (){
  double headingValue = inertiaSensor.heading();
  brain1.Screen.setCursor(100, 100);
  brain1.Screen.clearLine();
  brain1.Screen.print(headingValue);
  }




/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  brain1.Screen.clearScreen();
  brain1.Screen.print("Calibrando");

  inertiaSensor.calibrate();

  while(inertiaSensor.isCalibrating()) {
    wait(20, msec);
  }

  brain1.Screen.clearScreen();
  brain1.Screen.print("Listo");

  brain1.Screen.drawCircle(100, 100, 50);
  brain1.Screen.print("Ferny");


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  driveTrain.driveFor(20, inches);
  driveTrain.turnFor(90, degrees);
  driveTrain.driveFor(15, inches);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

    controller1.ButtonX.pressed(printHeading);

  while(true){
    if (controller1.ButtonUp.pressing()) {
    elevatorMotors.spin(forward, 50, percent);
  } else if (controller1.ButtonDown.pressing()){
    elevatorMotors.spin(reverse, 50, percent);
  } else {
    elevatorMotors.stop();
  }
  wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
