#include <TimerOne.h>

#define echoPin 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04

#define TIMER_US 50                                   // 50 uS timer duration 
#define TICK_COUNTS 4000                              // 200 mS worth of timer ticks


// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

//Left side motors
int in1Pin = 10; //positive=reverse negative=forward
int in2Pin = 9; //positive=forward negative=reverse
//Right side motors
int in3Pin = 5; //positive=reverse negative=forward
int in4Pin = 6; //positive=forward negative=reverse

//variable subject to change
volatile int distanceToObstical = 0;//or = distance

//prototypefunctions
void sonarScan();
void forward();
void reverse();

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  Timer1.initialize(TIMER_US);                        // Initialise timer 1
  attachInterrupt(echoPin,sonarScan, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
sonarScan();
if(distance <= 8){
  reverse();
}
else{
  forward();
}
}

void sonarScan(){
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
 /* Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/
}
void forward(){
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
}
void reverse(){
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(10);
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
}
