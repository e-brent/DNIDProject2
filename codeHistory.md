# Project Code History and Hurdles

While we didn't keep track of our code through commits to this repository, we did keep a backup file of differrent iterations of our code in a spearate file incase certain changes didn't work and we needed to go back. In this file, I'll go through the big changes and hurdles we faced while developing the code for this project. 

## The original code
Because neither of us had prior experience using Arduino, we started by finding a tutorial with one of the basic actions we knew we wanted to use in our project- moving a servo motor with a button- to provide a starting framework to build off of. The tutorial we used was this open source one from [Arduino Get Started](https://arduinogetstarted.com/tutorials/arduino-button-servo-motor):

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
We knew that we were going to be working with sets of doors, so the first step was to adapt this code to include a second servo motor. This was a relatively simple change that was mostly just duplicating some variables and changing their names, so that part went smoothly. 

```
#include <Servo.h>

// constants won't change
const int BUTTON1_PIN = 6; // Arduino pin connected to button's pin
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
  }
}
```

## Randomizing the doors opening
We knew that we wanted to have the back doors to Narnia open inconsistently when the button was pressed, so to simulate this we decided to have them open based on a random number generator. The general concept we wanted to use was that if the random number was even, then the doors would open, and if it was odd, then they wouldn't. 

Since we had never built a random number generator in arduino, we used [this tutorial](https://www.tutorialspoint.com/arduino/arduino_random_numbers.htm) from Tutorials Point to get us started. We added an integer variable `randnumber` to store the generated value. Under setup(), we added `randomSeed(anaglogRead(0))` to reset the generator to a random value based on noise from the unused analog pin. Under loop(), each time the button was pressed we would generate a random number between 0 and 200 using `randnumber = random(200)`. Then, to determine whether we should open the doors or not we made an if-statement with the condition `randnumber % 2 == 0`, inside of which were the controls to open the doors. The code to close the doors was still outside of that if-statement, so that code would run consistently.

## Adding an LED light
Once two servo motors were added and working, we knew adding the other two would be pretty easy since it would follow a similar process, so we moved our attention to the other equipment we were going to use: an LED. It was surprisingly difficult to find a diagram with an LED wired to a breadboard in a way that we knew would be necessary for when we moved the LED farther from the breadboard on extension wires, but eventually I found the [Arduino LED - Complete Tutorial](https://roboticsbackend.com/arduino-led-complete-tutorial/) on The Robotics Back-End, and the code ended up being fairly simple: 
* With the rest of our constants defined at the top of our file, we included `#define LED_PIN 11` 
* In setup(), we added `pinMode(LED_PIN, OUTPUT)`
* In loop(), when the button is pressed we added a couple lines so that the LED would turn off after a delay because we were really just looking for proof of concept that we had wired it correctly. The code we added was as follows: 
```
digitalWrite(LED_PIN, HIGH);
delay(2000)
digitalWrite(LED_PIN, LOW);
```

## Adding the second button
We knew that our final product would have at least two buttons (there was a time when we considered three, but there didn't end up being enough space for that), and that the buttons would have a big effect on the structure of the code, so that was the next thing we added. At this time we made the function of the two buttons so that one would open the doors and turn on the light, and the other would close the doors and turn off the light. The random number generator was still being used under the "open" button, so when it was pressed, sometimes the code would run and sometimes it wouldn't. 

```
#include <Servo.h>

// constants won't change
const int BUTTON1_PIN = 13; // Arduino pin connected to button's pin
const int BUTTON2_PIN = 12;
const int SERVO1_PIN = 9; // Arduino pin connected to servo motor's pin
const int SERVO2_PIN = 10;
#define LED_PIN 11

Servo servo1; // create servo object to control a servo
Servo servo2;

// variables will change:
int angle1 = 0;  
int angle2 = 180;        // the current angle of servo motor
int lastButton1State;    // the previous state of button
int currentButton1State; // the current state of button
int lastButton2State;    // the previous state of button
int currentButton2State;
int randnumber = 1;

void setup() {
  Serial.begin(9600);                // initialize serial
  randomSeed(analogRead(0));

  pinMode(BUTTON1_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  servo1.attach(SERVO1_PIN);           // attaches the servo on pin 9 to the servo object
  servo2.attach(SERVO2_PIN);
  
  servo1.write(angle1);
  servo2.write(angle2);
  
  currentButton1State = digitalRead(BUTTON1_PIN);
  currentButton2State = digitalRead(BUTTON2_PIN);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  lastButton1State = currentButton1State;      // save the last state
  currentButton1State = digitalRead(BUTTON1_PIN); // read new state
  lastButton2State = currentButton2State;      // save the last state
  currentButton2State = digitalRead(BUTTON2_PIN); // read new state
  
  if(lastButton1State == HIGH && currentButton1State == LOW){
     Serial.println("The button 1 is pressed");
     Serial.println(randnumber);
     
     randnumber = random(200); 
     
    if(randnumber % 2 == 0){
      // change angle of servo motor
      if(angle1 == 0)
        angle1 = 90;
      if(angle2 == 180)
        angle2 = 90;
        
      servo1.write(angle1);
      servo2.write(angle2);
        
      digitalWrite(LED_PIN, HIGH);
    }
  }
  
  if(lastButton2State == HIGH && currentButton2State == LOW) {
    Serial.println("The button 2 is pressed");
    Serial.println(randnumber);
    
    if(angle1 == 90)
      angle1 = 0;
    if(angle2 == 90)
      angle2 = 180;
    
    servo1.write(angle1);
    servo2.write(angle2);
      
    digitalWrite(LED_PIN, LOW);
  }
}
```

## Adding the second set of doors
The last things that needed to be wired were the servo motors for the second set of doors, and after that we theoretically could be finished. So, we decided to add them and finish the wiring, which would let us properly test and fully debug the program. Due to the order we added the servo motors, though slightly counterintuitive, servo3 and servo4 are the front doors of the wardrobe, and servo1 and servo2 are the back doors.

```
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
int angle4 = 180;
int lastButton1State;    // the previous state of button
int currentButton1State; // the current state of button
int lastButton2State;    // the previous state of button
int currentButton2State;
int randnumber = 1;

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
  
  if(lastButton1State == HIGH && currentButton1State == LOW){
    Serial.println("The button 1 is pressed");
    Serial.println(randnumber);
     
    randnumber = random(200); 
    
    // change angle of servo motor
    if(angle3 == 0)
      angle3 = 90;
    if(angle4 == 180)
      angle4 = 90;
        
    servo3.write(angle3);
    servo4.write(angle4);
     
    if(randnumber % 2 == 0){
      // change angle of servo motor
      if(angle1 == 0)
        angle1 = 90;
      if(angle2 == 180)
        angle2 = 90;
      
      servo1.write(angle1);
      servo2.write(angle2);
  
      digitalWrite(LED_PIN, HIGH);
    }
  }
  
  if(lastButton2State == HIGH && currentButton2State == LOW) {
    Serial.println("The button 2 is pressed");
    Serial.println(randnumber);
    
    if(angle3 == 90)
      angle3 = 0;
    if(angle4 == 90)
      angle4 = 180;
      
    if(angle1 == 90)
      angle1 = 0;
    if(angle2 == 90)
      angle2 = 180;
    
    servo1.write(angle1);
    servo2.write(angle2);
    servo3.write(angle3);
    servo4.write(angle4);
      
    digitalWrite(LED_PIN, LOW);
  }
}
```

## Major hurdle: the servos weren't working
At this point, we were purely debugging, so I'm going to just be including the snippets of code that were changed instead of copying the whole program now, as it was getting pretty long at this point. 

After adding the fourth servo motor, we hit our first (and really only) major hurdle with Arduino. Though the set up and code was theoretically correct, the servo motors- especially the second set- sometimes just wouldn't work. They would twitch, so you could tell that they were supposed to move, but they wouldn't smoothly open the doors. We thought it might be because with four servo motors, there just wasn't enough power to move all of them at the same time. At first, we just tried to add a small delay between the opening/closing of the front and back doors of the wardrobe by including `delay(500)` between writing the angles for each set of doors. However, this wasn't sufficient.

In conjunction with trying to solve this, we were also looking into how to slow down the servo motors, because at their default speed we thought the doors would be opening too aggressivley for our intended scene. In the end, the fix for these ended up being the same code: we could slow down the motors by changing the angle one degree at a time and adding in a small delay, and this was also enough to not be drawing too much power at once. I found this solution in [this Arduino forum](https://forum.arduino.cc/t/slowing-down-servos-how-to-write-it-into-the-program/142423/3), though I didn't end up using any of the exact solutions posted. To code this, each spot where we had:
```
if(angle1 == 0)
  angle1 = 90;
if(angle2 == 180)
  angle2 = 90;

servo1.write(angle1);
servo2.write(angle2);
```
We replaced it with: 
```
while(angle1 != 90 && angle2 != 90){
  angle1 += 1;
  angle2 -= 1;
  servo1.write(angle1);
  servo2.write(angle2);
  delay(10);
}
```
For both sets of servo motors. 

## A quick aside: temporarily removing the randomized element
Though this change didn't make it into our final project, nor was it ever really part of the plan, we did temporarily remove the random number generator from our code, instead having the back doors open every other time the open button was pressed. This change was largely made for demonstration and proof-of-concept purposes for our project update in class, and we quickly switched back to the randomized value for our actual work because we thought that it provided more interest and engagement for the user. Though this change doesn't have any continued presence in our final code, it was an iteration of the project that briefly existed. 

## The reset button
The final change was to switch the buttons from being an open button and a close button to an open/close button and a close/reset button. While we considered adding the third button to be the reset button, it didn't end up being feasible within the physical scale of our project and we wanted to minimize the additional wires added. We also faced some small hurdles here because I wasn't paying close attention while I was doing the coding, and ended up putting in some double equals instead of single when I was trying to change a value. Luckily, once I noticed this mistake it was a quick fix. 

The most important addition to the code to make this change was a boolean value called `firstPress`. We needed to keep track of whether it was the first time the open/close button was pressed because in that case, we had to guarantee that both sets of doors would open, rather than the second set being randomized. `firstPress` was initialized to true in the beginning, and when the first button was pressed, it would open all the doors and `firstPress` would be set to false. After that, each time the open/close button was pressed, the random number generator would be used to determine which doors would be opened, or if they were opened it would close them. The most important function of the reset button was to set `firstPress` back to true, but we also included the code to close the doors so that the scene could be physically, not just logically, reset if needed.

After this, the only changes made were to clean up the code slightly and update the comments to reflect the final version. In hindsight, I do see places where the code could have been condensed and more efficiently written, but during our iterative process of writing it, we wanted it to be as expanded as possible because we were testing changes at different points throughout. To see the final version of the code in full, check out [finalCode](finalCode/finalCode.ino).
