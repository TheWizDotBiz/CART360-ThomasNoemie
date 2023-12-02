

//This code is a demonstration of the pulse sensor moving a servo motor at every beginning of beat.


#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>

//for servo
#include <Servo.h>
const int servoPin = 2;
//for motor stuff
bool MOTORSTATE = false;
int lastServoVal = 0;
Servo servo;
int servoAngle = 0;
int servoIncrement = 10;


const int inputPin = A0;
const int ledPin = 7;
const int buttonPin = 9; //we use this button and a 10k ohm resistor before returning it to GND to toggle on and off the blinkOnPulse
const int threshold = 512; //neutral should be around 512 but it tends to skid around that
const int offset = 20; //an offset value we use to filter noise

bool ACTIVATED = false;
int lastButtonVal;



//const int sampleArrayLength = 10;
//int[sampleArrayLength] sampleArray;

PulseSensorPlayground pulseSensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //recommended for this sensor
  
  servo.attach(servoPin);
  servo.write(0);
  pinMode(9, INPUT);

  pulseSensor.analogInput(inputPin);
  pulseSensor.blinkOnPulse(ledPin); //kinda dinky, for more accuracy, run an if statement on pulseSensor.SawStartOfBeat() and check if above threshold, then manually run digitalWrite shit.
  pulseSensor.setSerial(Serial);
  pulseSensor.setThreshold(threshold);

  pulseSensor.pause();
}

void loop() {
  if(pulseSensor.sawNewSample()){
    //Serial.println("Saw new sample!");
   // pulseSensor.outputSample();
  }

  if(pulseSensor.sawStartOfBeat()){
  //  Serial.println("Saw start of beat!");
   // pulseSensor.outputBeat();
  }

int buttonval = digitalRead(buttonPin);
 //Serial.println(digitalRead(buttonval));
 if(buttonval != lastButtonVal){
    if(lastButtonVal == 0){
      toggle();
      
    }
    lastButtonVal = buttonval;
 }
 // Serial.println(analogRead(inputPin));

 //Serial.println(digitalRead(ledPin));
 int servoVal = digitalRead(ledPin);
 if(servoVal != lastServoVal){
  if(lastServoVal == 0){
  //moveMotor();
  newMoveMotor();
  }

  lastServoVal = servoVal;
 }
}

void toggle(){ //triggered by button presses linked to pin 9, pauses and unpauses the pulseSensor, so when you dont wear it/dont want it to get pulse readings off of random shit you can turn it off. ish.
  if(ACTIVATED){
    Serial.println("PULSESENSOR PAUSED");
    pulseSensor.pause();
    ACTIVATED = false;
  }else{
    Serial.println("PAUSESENSOR RESUMED");
    pulseSensor.resume();
    ACTIVATED = true;
  }
}

void moveMotor(){ //this makes the servo make 180 rotations from left to right 
  if(MOTORSTATE){
    servo.write(0);
    MOTORSTATE = false;
  }else{
    servo.write(180);
    MOTORSTATE = true;
  }
}

void newMoveMotor(){ //this makes the servo move in small increments, and alternates direction when reaching one of the extremities (180 degrees)
  servoAngle += servoIncrement;
  if(servoAngle >= 180){
    servoAngle = 180;
    servoIncrement *= -1;
  }

  if(servoAngle <= 0){
    servoAngle = 0;
    servoIncrement *= -1;
  }
  servo.write(servoAngle);
}
