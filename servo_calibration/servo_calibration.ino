/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/
#include <SpeedyStepper.h>


//
// pin assignments
//
const int LED_PIN = 13;
const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_Z_STEP_PIN = 4;
const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int MOTOR_Z_DIR_PIN = 7;
const int STEPPERS_ENABLE_PIN = 8;
const int LIMIT_SWITCH_X_PIN = 9;
const int LIMIT_SWITCH_Y_PIN = 10;
//const int LIMIT_SWITCH_Z_PIN = 11;
const int SPINDLE_ENABLE_PIN = 12;
const int SPINDLE_DIRECTION_PIN = 13;

#include <Servo.h>
int no_color = 90;
int blue_thresh = 28;
int red_thresh = 30;
int blue = blue_thresh + no_color;
int red = no_color - red_thresh;
int pos;
int servopos = 11;
int i = 1;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

SpeedyStepper stepperX;
SpeedyStepper stepperY;

void setup() {
  pinMode(LED_PIN, OUTPUT);   
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);       // be sure to do this
  Serial.begin(9600);
  myservo.attach(servopos);  // attaches the servo on pin 9 to the servo object

  //
  // connect and configure the stepper motor to there IO pins
  //
  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
  stepperY.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);


  //
  // enable the stepper motors
  //
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);     // be sure to do this
  stepperX.setSpeedInStepsPerSecond(50);
  stepperX.setAccelerationInStepsPerSecondPerSecond(8000);

  stepperY.setSpeedInStepsPerSecond(130);
  stepperY.setAccelerationInStepsPerSecondPerSecond(8000);
}

void loop() {


 
  delay(1000);

//  if (i % 4 == 0){
//     stepperX.moveRelativeInSteps(-2000);
//  }
//  if (i % 4 == 1){
//     stepperY.moveRelativeInSteps(8000);
//  }
//  if (i % 4 == 2){
//     stepperX.moveRelativeInSteps(2000);
//  }
//
//  if (i % 4 == 3){
//     stepperY.moveRelativeInSteps(-8000);
//  }
//  i++;

  for (pos = red; pos <= no_color; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(1000);

  for (pos = no_color; pos <= blue; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }


  for (pos = blue; pos >= no_color; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = no_color; pos >= red; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
