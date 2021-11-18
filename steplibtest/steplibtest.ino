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
int servopos = 11;    // variable to store the servo position
Servo myservo;  // create servo object to control a servo


//
// create the stepper motor objects
//
SpeedyStepper stepperX;
SpeedyStepper stepperY;



void setup() 
{
  //
  // setup the LED pin and enable print statements
  //
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
}




void loop() 
{
  //
  // Note 1: It is assumed that you are using a stepper motor with a 
  // 1.8 degree step angle (which is 200 steps/revolution). This is the
  // most common type of stepper.
  //
  // Note 2: It is also assumed that your stepper driver board is  
  // configured for 1x microstepping.
  //
  // It is OK if these assumptions are not correct, your motor will just
  // turn less than a full rotation when commanded to. 
  //
  // Note 3: This example uses "relative" motions.  This means that each
  // command will move the number of steps given, starting from it's 
  // current position.
  //

  //
  // first show how to run just one stepper motor
  //
//  Serial.println("Running just the X stepper");
  runJustTheXStepper();

  //
  // now show how to run two stepper motors
  //
//  Serial.println("Running the X & Y steppers");
//  runBothXAndYSteppers();
}



void runJustTheXStepper() 
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  stepperX.setSpeedInStepsPerSecond(600);
  stepperX.setAccelerationInStepsPerSecondPerSecond(10000);

  stepperY.setSpeedInStepsPerSecond(600);
  stepperY.setAccelerationInStepsPerSecondPerSecond(10000);

  //
  // Rotate the motor in the forward direction one revolution (200 steps). 
  // This function call will not return until the motion is complete.
  //
  stepperX.moveRelativeInSteps(-2000);
  delay(1000);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  stepperY.moveRelativeInSteps(-8000);  
  delay(1000);
  stepperX.moveRelativeInSteps(2000);
  delay(1000);
  stepperY.moveRelativeInSteps(8000);  
  delay(1000);
  //
  // now that the rotation has finished, delay 1 second before starting 
  // the next move
  //
  delay(1000);

  //
  // rotate backward 1 rotation, then wait 1 second
  //
//  stepperX.moveRelativeInSteps(70);


//  //
//  // This time speedup the motor, turning 10 revolutions.  Note if you
//  // tell a stepper motor to go faster than it can, it just stops.
//  //
//  stepperX.setSpeedInStepsPerSecond(800);
//  stepperX.setAccelerationInStepsPerSecondPerSecond(800);
//  stepperX.moveRelativeInSteps(200);
//  delay(2000);
}



void runBothXAndYSteppers() 
{
  //
  // use the function below to move two motors with speed coordination
  // so that both stop at the same time, even if one moves farther than
  // the other
  //

  //
  // turn both motors 200 steps, but in opposite  directions
  //
  long stepsX = -200 * 1;
  long stepsY = 200 * 1;
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);

  //
  // turn one motor 5 revolutions, the other motor just 1
  //
  stepsX = -200 * 1;
  stepsY = 200 * 5;
  speedInStepsPerSecond = 500;
  accelerationInStepsPerSecondPerSecond = 500;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(3000);
}



//
// move both X & Y motors together in a coordinated way, such that they each 
// start and stop at the same time, even if one motor moves a greater distance
//
void moveXYWithCoordination(long stepsX, long stepsY, float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  long absStepsX;
  long absStepsY;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;


  //
  // determine how many steps each motor is moving
  //
  if (stepsX >= 0)
    absStepsX = stepsX;
  else
    absStepsX = -stepsX;
 
  if (stepsY >= 0)
    absStepsY = stepsY;
  else
    absStepsY = -stepsY;


  //
  // determine which motor is traveling the farthest, then slow down the
  // speed rates for the motor moving the shortest distance
  //
  if ((absStepsX > absStepsY) && (stepsX != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsY / (float) absStepsX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scaler;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scaler;
  }
  
  if ((absStepsY > absStepsX) && (stepsY != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsX / (float) absStepsY;
    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scaler;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scaler;
  }

  
  //
  // setup the motion for the X motor
  //
  stepperX.setSpeedInStepsPerSecond(speedInStepsPerSecond_X);
  stepperX.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_X);
  stepperX.setupRelativeMoveInSteps(stepsX);


  //
  // setup the motion for the Y motor
  //
  stepperY.setSpeedInStepsPerSecond(speedInStepsPerSecond_Y);
  stepperY.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Y);
  stepperY.setupRelativeMoveInSteps(stepsY);


  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
  }
}
