/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-servo-motor
 */

#include <Servo.h>

// constants won't change
const int BUTTON1_PIN = 13; // Arduino pin connected to button's pin
const int BUTTON2_PIN = 12;
const int SERVO1_PIN = 9; // Arduino pin connected to servo motor's pin
const int SERVO2_PIN = 10;
const int SERVO3_PIN = 7;
const int SERVO4_PIN = 6;
#define LED_PIN 11

Servo servo1; // create servo object to control a servo
Servo servo2;
Servo servo3;
Servo servo4;

// variables will change:
int angle1 = 0;  
int angle2 = 180;        // the current angle of servo motor
int angle3 = 0;  
int angle4 = 0;
int lastButton1State;    // the previous state of button
int currentButton1State; // the current state of button
int lastButton2State;    // the previous state of button
int currentButton2State;
int randnumber = 1;
bool firstPress = true;


void setup() {
  Serial.begin(9600);                // initialize serial
  randomSeed(analogRead(0));

  pinMode(BUTTON1_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  servo1.attach(SERVO1_PIN);           // attaches the servo on pin 9 to the servo object
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);
  currentButton1State = digitalRead(BUTTON1_PIN);
  currentButton2State = digitalRead(BUTTON2_PIN);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  lastButton1State = currentButton1State;      // save the last state
  currentButton1State = digitalRead(BUTTON1_PIN); // read new state
  lastButton2State = currentButton2State;      // save the last state
  currentButton2State = digitalRead(BUTTON2_PIN); // read new state
  //randnumber = random(200); 

  if(lastButton1State == HIGH && currentButton1State == LOW && firstPress == true) {
    firstPress = false;
    Serial.println("The button 1 is pressed");
    Serial.println(randnumber);
    
    while(angle3 != 90 && angle4 != 90){
      angle3 += 1;
      angle4 += 1;
      servo3.write(angle3);
      servo4.write(angle4);
      delay(15);
    }
      while(angle1 != 90 && angle2 != 90){
      angle1 += 1;
      angle2 -= 1;
      servo1.write(angle1);
      servo2.write(angle2);
      delay(10);
    }
    digitalWrite(LED_PIN, HIGH);
  }
  else if (lastButton1State == HIGH && currentButton1State == LOW && firstPress == false){
    if(angle3 == 0 && angle4 == 0){

      randnumber = random(200); 

      Serial.println("The button 1 is pressed");
      Serial.println(randnumber);
      
      while(angle3 != 90 && angle4 != 90){
        angle3 += 1;
        angle4 += 1;
        servo3.write(angle3);
        servo4.write(angle4);
        delay(15);
      }

      if(randnumber % 2 == 0){
        while(angle1 != 90 && angle2 != 90){
        angle1 += 1;
        angle2 -= 1;
        servo1.write(angle1);
        servo2.write(angle2);
        delay(10);
        }

        digitalWrite(LED_PIN, HIGH);
      }
    }
    else {
      Serial.println("The button 1 is pressed");
      Serial.println(randnumber);
          
      // control servo motor according to the angle
      while(angle1 != 0 && angle2 != 180){
        angle1 -= 1;
        angle2 += 1;
        servo1.write(angle1);
        servo2.write(angle2);
        delay(10);
      }
      digitalWrite(LED_PIN, LOW);

      while(angle3 != 0 && angle4 != 0){
        angle3 -= 1;
        angle4 -= 1;
        servo3.write(angle3);
        servo4.write(angle4);
        delay(15);
      }
    }
  }

  if(lastButton2State == HIGH && currentButton2State == LOW) {
    Serial.println("The button 2 is pressed");
    Serial.println(randnumber);
        
    // control servo motor according to the angle
    while(angle1 != 0 && angle2 != 180){
      angle1 -= 1;
      angle2 += 1;
      servo1.write(angle1);
      servo2.write(angle2);
      delay(10);
    }
    digitalWrite(LED_PIN, LOW);

    while(angle3 != 0 && angle4 != 0){
      angle3 -= 1;
      angle4 -= 1;
      servo3.write(angle3);
      servo4.write(angle4);
      delay(15);
    }

    firstPress == true;
  }

}
