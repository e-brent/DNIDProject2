#include <Servo.h>

// Constant variables, won't change -- define where objects are connected to the Arduino board
const int BUTTON1_PIN = 13; // Arduino pin connected to first button - will open and close doors
const int BUTTON2_PIN = 12; // Arduino pin connected to second button - will reset count to restart presentation, will close doors if open
const int SERVO1_PIN = 9;   // Door for back of wardrobe (left or right???)
const int SERVO2_PIN = 10;  // Door for back of wardrobe (left or right???)
const int SERVO3_PIN = 7;   // Door for front of wardrobe (I think left???)
const int SERVO4_PIN = 6;   // Door for front of wardrobe (I think right???)
#define LED_PIN 11          // LED light 

Servo servo1; // Servo object for (left or right???) back door of wardrobe
Servo servo2; // Servo object for (left or right???) back door of wardrobe
Servo servo3; // Servo object for (left ???) front door of wardrobe
Servo servo4; // Servo object for (right???) front door of wardrobe

// Variables that will change:
  // Set the initial angles of the servo motors
int angle1 = 0;  
int angle2 = 180;
int angle3 = 0;  
int angle4 = 0; // This one is a different brand of servo motor, so it rotates in the opposite direction of the others -- have to set it opposite, so 3 and 4 actually end up moving between the same angles
int lastButton1State;    // The previous state of the first button
int currentButton1State; // The current state of the first button
int lastButton2State;    // The previous state of the second button
int currentButton2State; // The current state of the second button

int randnumber = 1; // After the first time opening, the back doors will open based on if this number is even or odd. Arbitrarily set to 1 just to have initial value
bool firstPress = true; //Boolean value that will be reset with the second button


void setup() {
  Serial.begin(9600);         // Initialize serial
  randomSeed(analogRead(0));  // Read noise from analog pin 0 for random number generator

  pinMode(BUTTON1_PIN, INPUT_PULLUP); // Set arduino pin to input pull-up mode for the first button
  pinMode(BUTTON2_PIN, INPUT_PULLUP); // Set arduino pin to input pull-up mode for the second button
  servo1.attach(SERVO1_PIN);  // Attaches the servo on pin 9 to the servo1 object
  servo2.attach(SERVO2_PIN);  // Attaches the servo on pin 10 to the servo2 object
  servo3.attach(SERVO3_PIN);  // Attaches the servo on pin 7 to the servo3 object
  servo4.attach(SERVO4_PIN);  // Attaches the servo on pin 6 to the servo4 object

  // Set the initial angles of the 4 servos, the buttons, and the LED
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  currentButton1State = digitalRead(BUTTON1_PIN);
  currentButton2State = digitalRead(BUTTON2_PIN);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  // Determine which button was pressed
  lastButton1State = currentButton1State;          // Save the last state of button1
  currentButton1State = digitalRead(BUTTON1_PIN);  // Read the new state of button1
  lastButton2State = currentButton2State;          // Save the last state of button2
  currentButton2State = digitalRead(BUTTON2_PIN);  // Read the new state of button2
  

  // Button1 pressed and it is the beginning of the simulation/presentation
  if(lastButton1State == HIGH && currentButton1State == LOW && firstPress == true) {
    firstPress = false; // Set the first press to false
    
    // Open the front doors of the wardrobe
    // Open the doors outwards 90 degrees (maybe more?); moving them slowly to avoid trying to draw too much power
    while(angle3 != 90 && angle4 != 90){
      angle3 += 1;
      angle4 += 1;
      servo3.write(angle3);
      servo4.write(angle4);
      delay(15);
    }

    // Open the back doors of the wardrobe
    // Open the doors 90 degrees into Narnia; follow same logic as above for why they are being incremented (but incremented faster)
    while(angle1 != 90 && angle2 != 90){
      angle1 += 1;
      angle2 -= 1;
      servo1.write(angle1);
      servo2.write(angle2);
      delay(10);
    }
    digitalWrite(LED_PIN, HIGH); //Turn on the LED light
  }


  // Button1 is pressed but it is not the first time 
  else if (lastButton1State == HIGH && currentButton1State == LOW && firstPress == false){

    // If the front doors are closed, then all the doors are closed
    // We want to open them
    if(angle3 == 0 && angle4 == 0){

      // Generate a random number to determine if we are going to open the back doors of the wardrobe
      randnumber = random(200); 
      
      // Open the front doors 
      while(angle3 != 90 && angle4 != 90){
        angle3 += 1;
        angle4 += 1;
        servo3.write(angle3);
        servo4.write(angle4);
        delay(15);
      }

      // If the random number was even, open the back doors and turn on the light
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


    // The doors are currently open; close them
    else {

      // Close the back doors (if they were open)
      while(angle1 != 0 && angle2 != 180){
        angle1 -= 1;
        angle2 += 1;
        servo1.write(angle1);
        servo2.write(angle2);
        delay(10);
      }
      // Turn off the LED, if it was on
      digitalWrite(LED_PIN, LOW);

      // Close the front doors of the wardrobe
      while(angle3 != 0 && angle4 != 0){
        angle3 -= 1;
        angle4 -= 1;
        servo3.write(angle3);
        servo4.write(angle4);
        delay(15);
      }
    }
  }


  // If the second button (the reset button is pressed)
  if(lastButton2State == HIGH && currentButton2State == LOW) {

    // If any of the doors are open or the light is on, close them following procedure above
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

    //Set boolean value back to true, next time button1 is pressed all the doors are guaranteed to open (resets project)
    firstPress = true;
  }

}
