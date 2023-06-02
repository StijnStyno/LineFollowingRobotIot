#include <WiFi.h>
#include <PubSubClient.h>

//network credentials
const char* ssid = "embed";
const char* password = "weareincontrol";
//topics
const char* power_topic = "home/signal/power";
//mqtt broker credentials
const char* mqttServer = "192.168.1.68";
const int mqttPort = 1883;
const char* mqttUser = "stijn";
const char* mqttPassword = "admin";
const char* clientID = "robotstijn"; // MQTT client ID
// motor A pins
const int motorA1 = 13;
const int motorA2 = 12;
const int motorAE = 14; //enable pin for first motor
// motor B pins
const int motorB1 = 27;
const int motorB2 = 26;
const int motorBE = 25; //enable pin for second motor
//sensors
const int irP1 = 33; //infrared sensor right
const int irP2 = 35; //infrared sensor middle
const int irP3 = 34; //infrared sensor left
const int trigPin = 22; 
const int echoPin = 23;
//leds
const int ledPinR = 15;
const int ledPinY = 2;
const int ledPinG = 4;
//button
const int btnPin = 15;
//etc
const int mSpeed = 300;
int p = 100;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  //set pinmode
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorAE,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  pinMode(motorBE,OUTPUT);
  pinMode(irP1,INPUT);
  pinMode(irP2,INPUT);
  pinMode(irP3,INPUT);
  pinMode(ledPinR,OUTPUT);
  pinMode(ledPinY,OUTPUT);
  pinMode(ledPinG,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(btnPin,INPUT);
  //start serial and wifi
  Serial.begin(115200);
  Serial.println("started serial");
  //set enable pins on motor driver
  digitalWrite(motorAE,1);
  digitalWrite(motorBE,1);
  
}

void loop() {
  int irA = digitalRead(irP1);
  int irB = digitalRead(irP2);
  int irC = digitalRead(irP3);
  int distance = distanceRead(); //read the distance of an object infront of the robot.
  if(irA == 1 && irB == 1 && distance >10){driveForward();}
  if(irA == 0 && irC == 1 && distance >10){driveRight();}
  if(irA == 1 && irC == 0 && distance >10){driveLeft();}
  if((irA == 0 && irC == 0) || distance<=10){stop();}
}

void driveLeft(){
  digitalWrite(motorA1,0);
  digitalWrite(motorA2,0);
  digitalWrite(motorB1,0);
  analogWrite(motorB2,mSpeed);
}

void driveRight(){
  digitalWrite(motorA1,0);
  analogWrite(motorA2,mSpeed);
  digitalWrite(motorB1,0);
  digitalWrite(motorB2,0);
}

void driveForward(){
  digitalWrite(motorA1,0);
  analogWrite(motorA2,mSpeed);
  digitalWrite(motorB1,0);
  analogWrite(motorB2,mSpeed);
}

void stop(){
  digitalWrite(motorA1,0);
  digitalWrite(motorA2,0);
  digitalWrite(motorB1,0);
  digitalWrite(motorB2,0); 
}

int distanceRead()
{
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}