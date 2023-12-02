#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>

//for servos
#include <Servo.h>
const int servoPin = 2;
const int servoPin2 = 3;
const int crownServoPin = 4;
//const int crownServoPin2 = 5;
Servo servo;
Servo servo2;
Servo crownServo;
//Servo crownServo2;
int servoAngle = 0;
int servoIncrement = 90; //modify this to change speed!
int servoLimit = 90;
int crownServoAngle = 90;
int crownServoIncrement = 5;
int crownServoLimit = 90;

//sensor
#define inputPin A0//for heart pulse sensor, itd be a bitch to rename this so whatever
const int threshold = 512; //neutral should be around 512 but it tends to skid around that, for heart pulse sensor
bool inHeartbeat = false;
#define muscleSensorPin A1 //for the muscle sensor.


//const int ledPin = 7; //there was a led on this thing at some point? likely a holdover from the prototype
const int buttonPin = 7; //test button, tap to make the sensors go!

const int offset = 20; //an offset value we use to filter noise

bool ACTIVATED = false; //keep for pausing/resuming purposes if you want to have a panic button
int lastButtonVal = false; //used for button control if there is one

const int secondButtonPin = 8;
int lastSecondButtonVal = false;



//const int sampleArrayLength = 10;
//int[sampleArrayLength] sampleArray;

PulseSensorPlayground pulseSensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //recommended for this sensor
  
  servo.attach(servoPin);
  servo2.attach(servoPin2);
  servo.write(0);
  servo2.write(servoLimit);
  crownServo.attach(crownServoPin);
  crownServo.write(crownServoLimit);
  //crownServo2.attach(crownServoPin2);
  //crownServo2.write(0);


  pulseSensor.analogInput(inputPin);
 // pulseSensor.blinkOnPulse(ledPin); //kinda dinky, for more accuracy, run an if statement on pulseSensor.SawStartOfBeat() and check if above threshold, then manually run digitalWrite shit.
  pulseSensor.setSerial(Serial);
  pulseSensor.setThreshold(threshold);

 // pinMode(muscleSensorPin, INPUT);
  //pulseSensor.pause();
  pinMode(buttonPin, INPUT);
  pinMode(secondButtonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // start of beat failsafe, done by manually checking heart pulse sensor input
  /*
  if(analogRead(inputPin) >= threshold){
    if(!inHeartbeat){
      operateMotor();
      inHeartbeat = true;
    }
  }else{
    inHeartbeat = false;
  }
  */
  if(pulseSensor.sawNewSample()){
    Serial.print("im here so i dont shit myself"); //hes not lying, the script WILL shit itself if we dont call sawNewSample() for some reason.
  }
  
  if(pulseSensor.sawStartOfBeat()){
    Serial.println("Saw start of beat!");
   // pulseSensor.outputBeat();
   operateMotor();
  }
  
  if(digitalRead(secondButtonPin) == HIGH){
    if(lastSecondButtonVal == false){
      operateMotor();
      lastSecondButtonVal = true;
    }
  }else{
    lastSecondButtonVal = false;
  }

  //int analogValTest = analogRead(inputPin);
  //Serial.println(analogValTest);
  int analogVal = analogRead(muscleSensorPin);
  Serial.println(analogVal);
  if(analogVal >= 1000 || digitalRead(buttonPin) == HIGH){
    operateCrownMotors(true);
  }else{
    operateCrownMotors(false);
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

//these are important and are actually used in the final product
void operateMotor(){
  servoAngle += servoIncrement;
  if(servoAngle >= servoLimit){
    servoAngle = servoLimit;
    servoIncrement *= -1;
  }

  if(servoAngle <= 0){
    servoAngle = 0;
    servoIncrement *= -1;
  }

  servo.write(servoAngle);
  servo2.write(180 - servoAngle);
}

void operateCrownMotors(bool sensorActive){
  if(sensorActive){
    crownServoAngle -= crownServoIncrement;
    if(crownServoAngle <= 0){
      crownServoAngle = 0;
    }
  }else if(crownServoAngle != crownServoLimit){
    crownServoAngle += crownServoIncrement;
    if(crownServoAngle >= crownServoLimit){
      crownServoAngle = crownServoLimit;
    }
  }

  crownServo.write(crownServoAngle);
  //crownServo2.write(180 - crownServoAngle);
}
