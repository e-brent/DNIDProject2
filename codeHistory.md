# Project Code History and Hurdles

While we didn't keep track of our code through commits to this repository, we did keep a backup file of differrent iterations of our code in a spearate file as a back up incase certain changes didn't work and we needed to go back. In this file, we'll go through the big changes and hurdles we faced while developing the code for this project. 

## The original code
Because neither of us had prior experience using Arduino, we started by finding an open source tutorial with one of the basic actions we knew we wanted to use in our project to provide a starting framework to build off of. [The tutorial we used from Arduino Get Started](https://arduinogetstarted.com/tutorials/arduino-button-servo-motor) moved a servo motor when a button was pushed.

```
/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-servo-motor
 */

#include <Servo.h>

// constants won't change
const int BUTTON_PIN = 7; // Arduino pin connected to button's pin
const int SERVO_PIN  = 9; // Arduino pin connected to servo motor's pin

Servo servo; // create servo object to control a servo

// variables will change:
int angle = 0;          // the current angle of servo motor
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  servo.attach(SERVO_PIN);           // attaches the servo on pin 9 to the servo object

  servo.write(angle);
  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");

    // change angle of servo motor
    if(angle == 0)
      angle = 90;
    else
    if(angle == 90)
      angle = 0;

    // control servo motor arccoding to the angle
    servo.write(angle);
  }
}
```

## Adding a second servo motor
We knew that we were going to be working with sets of doors, so the first step was to adapt this this code ot include a second servo motor. This was a relatively simple change that was mostly just duplicating some variables and changing their names, so that part went smoothly. 

```
#include <Servo.h>

// constants won't change
const int BUTTON1_PIN = 13; // Arduino pin connected to button's pin
const int BUTTON2_PIN = 12;
const int SERVO1_PIN = 9; // Arduino pin connected to servo motor's pin
const int SERVO2_PIN = 10;

Servo servo1; // create servo object to control a servo
Servo servo2;

// variables will change:
int angle1 = 0;  
int angle2 = 180;        // the current angle of servo motor

void setup() {
  Serial.begin(9600);                // initialize serial
  randomSeed(analogRead(0));

  pinMode(BUTTON1_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  servo1.attach(SERVO1_PIN);           // attaches the servo on pin 9 to the servo object
  servo2.attach(SERVO2_PIN);
  
  servo1.write(angle1);
  servo2.write(angle2);
   currentButton1State = digitalRead(BUTTON1_PIN);
}

void loop() {
  lastButton1State = currentButton1State;      // save the last state
  currentButton1State = digitalRead(BUTTON1_PIN); // read new state
  
  if(lastButton1State == HIGH && currentButton1State == LOW){
     Serial.println("The button 1 is pressed");
     Serial.println(randnumber);
     
     // change angle of servo motor
    if(angle1 == 0)
      angle1 = 90;
    else
    if(angle1 == 90)
      angle1 = 0;
      
     // change angle of servo motor
    if(angle2 == 180)
      angle2 = 90;
    else
    if(angle2 == 90)
      angle2 = 180;

    // control servo motor arccoding to the angle
    servo1.write(angle1);
    servo2.write(angle2);
```

## Randomizing the doors opening
We knew that we wanted to have the back doors to Narnia open inconsistently when the button was pressed, so to simulate this we decided to have them open based on a random number generator. The general concept we knew we wanted to use was that if the random number was even, then the doors would open, and if it was odd, then they wouldn't. 

Since we had never built a random number generator, we used [this tutorial from Tutorials Point](https://www.tutorialspoint.com/arduino/arduino_random_numbers.htm) to get us started. We added an integer variable `randnumber` to store the generated value. Under setup(), we added `randomSeed(anaglogRead(0))` to reset the generator to a random value based on noise from the unused analog pin. Under loop(), each time the button was pressed we would generate a random number between 0 and 200 using `randnumber = random(200)`. Then, to determine whether we should open the doors or not we made an if-statement with the condition `randnumber % 2 == 0`, inside of which were the controls to open the doors. The code to close the doors was still outside of that if-statement, so that code would run consistently.
