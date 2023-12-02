#include <L293.h>
#define use_standalone //declared if you want to use the first circuit layout provided in the examples in the gitHub for this library, comment out to use the two-wire version

const int speedPin = 2; //digital pin 2 to L293 pin 1, used to control the motor speed.
const int forwardPin = 9; //digital pin 9 to L293 pin 2, digitalWrite input used to control FORWARD signal
const int reversePin = 10; //digital pin 10 to L293 pin 7, digitalWrite input used to contorl BACKWARD signal

//Declare our L293 motor object, to be referred to later for control
//You basically shouldnt have to directly call on pins from now now, just use motor callbacks
L293 motor(speedPin, forwardPin, reversePin);

//Variables that you might want to change to control speed, length and whatnot
int SPEED = 510; //by default examples set this 255, controls speed
float timer = 0; //stores current timer value to control when to start and stop timer
float timerLength = 5000; //length of activation, modify this to change
float initTimer = 0; //set to millis() when you start a timer.

bool bounceBack = false; //if set to true, once the movement ends it will do the inverse of that movement. CURRENTLY DOESNT WORK TODO GOTTA FIXIT!!!!!
bool lastDir = false; //stores the last direction

void setup() {
  // put your setup code here, to run once:
  /*
  motor.forward(SPEED);
  delay(1000);
  motor.back(SPEED);
  delay(1000);
  motor.stop();*/
  Serial.begin(57600);
  motor.stop();
  delay(1000); //this is ncessary in order to avoid a weird quarter-turn that occurs every reset, probably due to speedPin feeding in some random value when the arduino is reset.
  
 // delay(1); //as to not trick off the timerControl's initTimer !=0 statement.
  setDir(true, true);
 // motor.back(SPEED);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(2, HIGH);
 // delay(1000);
  timerControl();
 //newTimerControl();
}


void newTimerControl(){
  bool buffer = false;//due to a technicality, everything here stops once you call motor.stop(), this is just a bool you use to make sure the bounceBackk code is ran after we call motor.stop()
  if(motor.isStopped() == false || buffer == true){
    timer = millis();
    if(timer >= initTimer + timerLength){
      buffer = true;
      motor.stop();
      if(bounceBack){
        if(lastDir){
          setDir(false, false);
        }else{
          setDir(true, false);
        }
      }
      buffer = false;
    }
  }
}

void timerControl(){
  Serial.print("timer: ");
  Serial.println(timer);
  Serial.print("initTimer: ");
  Serial.println(initTimer);
  if(initTimer != 0){
    Serial.println("RUNNING TIMERCONTROL");
      timer = millis();
      if(timer >= initTimer + timerLength){
      motor.stop();
      //timer = 0;
      
      if(bounceBack){
        if(lastDir){
          setDir(false, false);
        }else{
          setDir(true, false);
        }
      }

      initTimer = 0;
     }
  }
  
};

void setDir(bool direction, bool BB){
  if(motor.isStopped()){
    Serial.println("RUNNING SETDIR");
    lastDir = direction;
    bounceBack = BB;
    if(direction == true){//set to true for forward
      motor.forward(SPEED);
    }else{
      motor.back(SPEED);
    }

    initTimer = millis() + 0.0001f;
    timer = millis();
    
  }
  
}
