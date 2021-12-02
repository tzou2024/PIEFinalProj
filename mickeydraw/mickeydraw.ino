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
int no_color = 90;
int blue_thresh = 28;
int red_thresh = 30;
int blue = blue_thresh + no_color;
int red = no_color - red_thresh;
int pos;
int servopos = 11;
int i = 1;
int shift = 1;
#include <Servo.h>
Servo myservo;  // create servo object to control a servo


//
// create the stepper motor objects
//
SpeedyStepper stepperX;
SpeedyStepper stepperY;



void setup() 
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

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
  myservo.write(no_color);

  stepperX.setSpeedInStepsPerSecond(600);
  stepperX.setAccelerationInStepsPerSecondPerSecond(10000);

  stepperY.setSpeedInStepsPerSecond(600);
  stepperY.setAccelerationInStepsPerSecondPerSecond(10000);

}


void red_dot()
{
  delay(100);
  for (pos = no_color; pos >= red; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = red; pos <= no_color; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(100);
}

void move_up(int x){
   delay(100);
   stepperY.moveRelativeInSteps(-70 * x);
   delay(100);  
}

void right_shift(int y){
  stepperY.moveRelativeInSteps(70 * y);
  stepperX.moveRelativeInSteps(-70);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    // read the incoming byte:
    String bigstring = Serial.readString();
    int stringlength = bigstring.length();
    int imgheight = atoi(bigstring[(stringlength)]);
    for (int i = 1; i < stringlength; i++){
      if (bigstring[(i-1)] == '1'){
        red_dot();
        move_up(1);
        stepperX.moveRelativeInSteps(-70 * imgheight);
        shift ++;
        }
      
      else {
        move_up(1);
        shift ++;
      }
      
    }
  }

}
