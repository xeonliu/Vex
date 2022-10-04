/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Liu                                              */
/*    Created:      Mon Oct 03 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor5               motor         5               
// Motor6               motor         6               
// Motor7               motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void print_v(motor m,int row){
  //Brain Output
  Brain.Screen.setCursor(row,1);
  Brain.Screen.clearLine();
  Brain.Screen.print("Motor: V = %3.1f rpm ",m.velocity(rpm));
  //Cntroller Output
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(row,1);
  Controller1.Screen.print("%3.1f rpm",m.velocity(rpm));
}

void run(motor m,int scale){
  m.spin(fwd,scale,rpm);
}

void movement(motor a,motor b,motor c,int FORWARD,int ROTATION){
  run(a,FORWARD+ROTATION);
  run(b,ROTATION-FORWARD);
  run(c,ROTATION);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
while (1) {
  movement(Motor5,Motor6,Motor7,Controller1.Axis3.value(),Controller1.Axis1.value());
  print_v(Motor5,1);
  print_v(Motor6,2);
  print_v(Motor7,3);
  //rotate(Motor5,Motor6,Motor7,Controller1.Axis1.value());
  wait(200, msec);
}
Motor5.stop();
}