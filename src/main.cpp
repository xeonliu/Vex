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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void print_v(motor m){
  //Brain Output
  Brain.Screen.printAt(100, 120, "100%%Vmax = %3.1f rpm ",m.velocity(rpm));
  //Cntroller Output
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("%3.1f rpm",m.velocity(rpm));
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
while (1) {
Motor5.spin(fwd,Controller1.Axis3.value(),rpm);
print_v(Motor5);
wait(200, msec);
}
Motor5.stop();
}