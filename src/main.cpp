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
// Motor1               motor         1               
// Motor11              motor         11              
// Motor20              motor         20              
// Inertial3            inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#define PI 3.1415926

using namespace vex;

void initialize(){
  Inertial3.calibrate();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Initializing...");
  waitUntil(!Inertial3.isCalibrating());
  Controller1.Screen.clearScreen();

}

void print_logo(){
  Brain.Screen.print("   =^           *********         @^       ***** =@^     ");
  Brain.Screen.newLine();
  Brain.Screen.print("  @@@@@@@@@@.   @^     =@.        @^      *@^ @^ =@^    ");
  Brain.Screen.newLine();
  Brain.Screen.print("=@@@@@@@@@@.    @^     =@.        @^      *@^=@. =@^ ");
  Brain.Screen.newLine();
  Brain.Screen.print("  =@OOOOOO@.    @@@@@@@@@.    =@. @^ =^   *@^@^  =@^");
  Brain.Screen.newLine();
  Brain.Screen.print("  =@     =@.    @^     =@.    @^  @^ =@^  *@^=@. =@@ ");
  Brain.Screen.newLine();
  Brain.Screen.print("  ,[@/[[[[[.    @^     =@.   ,@.  @^  \@. *@^.@\ @/@` ");
  Brain.Screen.newLine();
  Brain.Screen.print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
  Brain.Screen.newLine();
  Brain.Screen.print("./@[\\..@/                   ,    @^   .  *@^@@`/^  \`  ");
  Brain.Screen.newLine();
  Brain.Screen.print("    .@@@\.    ]]]]]]]]]]]]]       @^      *@^ ./^   ,@\ ");
  Brain.Screen.newLine();
  Brain.Screen.print("=@@@/[  [[@@/ ,[[[[[[[[[[[[     ,@/.      *@^.\/     ,/. ");
  Brain.Screen.newLine();
}
void select_mode(int &mode){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Please Select Mode: ");
  Controller1.Screen.newLine();
  Controller1.Screen.print("L2. Traditionnal Mode");
  Controller1.Screen.newLine();
  Controller1.Screen.print("R2. Advanced Mode");
  waitUntil(!Controller1.ButtonL2.pressing()&&!Controller1.ButtonR2.pressing());
  waitUntil(Controller1.ButtonL2.pressing()||Controller1.ButtonR2.pressing());
  if(Controller1.ButtonL2.pressing()) mode=1;
  if(Controller1.ButtonR2.pressing()) mode=2;
  Controller1.Screen.clearScreen();
}
void print_v(motor m,int row){  //To monitor the motors
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
  m.spin(fwd,scale,pct); //a short cut to start the motor
}

double calculate_theta(int x,int y){//as its name
  if(x>0) return atan(double(y)/x);
  else if(x<0) return PI+atan(double(y)/x);
  else{//if you can't calculate the angle,rotatation won't take effect!
   if(y>0) return PI/2;
   if(y<0) return -PI/2;
   else return 0;
  }

}
void get_translation_scale(double angle_,double scale,double &scale_a,double &scale_b,double &scale_c){
  //calculate what it takes for each motor to translate
  scale_a=scale*sin(angle_);
  scale_b=scale*cos(angle_+PI/6);
  scale_c=-scale*cos(angle_-PI/6);
} 

double get_rotation_scale(double rotate,double scale){
  //calculate what it take for each motor to rotate
  return rotate*scale;
}

void movement(motor a,motor b,motor c,double scale_a,double scale_b,double scale_c,double ROTATION){
  //calculate the actual volocity(also referred to as scale in this code) needed for each motor
  run(a,scale_a+ROTATION);//top
  run(b,scale_b+ROTATION);//bottom left
  run(c,scale_c+ROTATION);//bottom right
}

/*
void sudden_break(){
  Motor1.stop();
  Motor11.stop();
  Motor20.stop();
}
*/

/*
        =^           *********         @^       ***** =@^     
       @@@@@@@@@@.   @^     =@.        @^      *@^ @^ =@^     
     =@@@@@@@@@@.    @^     =@.        @^      *@^=@. =@^     
       =@OOOOOO@.    @@@@@@@@@.    =@. @^ =^   *@^@^  =@^     
       =@     =@.    @^     =@.    @^  @^ =@^  *@^=@. =@@     
       ,[@/[[[[[.    @^     =@.   ,@.  @^  \@. *@^.@\ @/@`    
    =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
     ./@[\\..@/                   ,    @^   .  *@^@@`/^  \`   
         .@@@\.    ]]]]]]]]]]]]]       @^      *@^ ./^   ,@\  
     =@@@/[  [[@@/ ,[[[[[[[[[[[[     ,@/.      *@^.\/     ,/. 
*/
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Initialize the inertial censor 
  print_logo();
  int mode;
  while(1){
  select_mode(mode);
  if(mode==2) initialize();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Your choice: Mode %d",mode);
  Controller1.Screen.newLine();
  Controller1.Screen.print("Press L2/R2 to quit");
  while (1) {
    waitUntil(!Controller1.ButtonL2.pressing()&&!Controller1.ButtonR2.pressing());
    int y= Controller1.Axis3.position(pct);
    int x= Controller1.Axis4.position(pct);


    //the scale of translation --> controlled by the joystick
    double scale = Controller1.Axis4.position(pct)*Controller1.Axis4.position(pct)+Controller1.Axis3.position(pct)*Controller1.Axis3.position(pct);

    double point_angle;
    //the angle must be revise by the 
    if(mode==1) x=0; point_angle = calculate_theta(y,x); 
    if(mode==2) point_angle = calculate_theta(y,x)-Inertial3.rotation(degrees)/180*PI; 

    //get the translation volocity
    double scale_a,scale_b,scale_c;
    get_translation_scale(point_angle,scale/1000,scale_a,scale_b,scale_c);
    //get the rotation volocity
    double rotation_scale = get_rotation_scale(Controller1.Axis1.position(pct),0.1);

    //drive the motor!
    movement(Motor1,Motor11,Motor20,scale_a,scale_b,scale_c,rotation_scale);
    
    //print the message on the screen
    //print_v(Motor1,1);
    //print_v(Motor11,2);
    //print_v(Motor20,3);
    //if (Controller1.ButtonX.pressing()) {sudden_break();break;}
    wait(20, msec);
    if(Controller1.ButtonL2.pressing()) break;
    if(Controller1.ButtonR2.pressing()) break;
  }
  }
}
                                                              
                                                              
