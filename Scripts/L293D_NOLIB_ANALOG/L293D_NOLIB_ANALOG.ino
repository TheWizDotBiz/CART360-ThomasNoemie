//An attempt at using the electromagnetic motors  with soldered encoders without using the rotaryEncoder library
//This uses the output cables on the encoder (which switch between HIGH and LOW when the motor turns) to track distance/position
//This functions using attachInterrupt, identically to L23D_NOLIB.ino but we use analog input pins for the encoder output instead of digital input pins. As we thought it might be the reason we were having precision issues with the motors
//It was not the issue and it still never moves the same distance forward and backward 
#include <L293.h>

#define pinFwd A4
#define pinBck A5
#define output1 2
#define output2 3

int ticks;
int tickLimit = 4000;
bool isBackward = false;

//timer control //THIS IS NOT USED TO CONTROL DISTANCE, ONLY THE RATE AT WHICH THE MOTOR PINS WRITE //THIS CURRENTLY DOESNT WORK IT FTHROWS OFF THE TICK SYSTEM FOR CALCULATING DISTANCE
//NTS TO DEACTIVE TIMER, JUST DECOMMENT THE DIGITALWRITE IN dirSwap() AND COMMENT CALLABCKS TO toggleMotor()
//WITHOUT timer, there seems to be no issue with distance, its consistent, i think.
//a possible solution: control the voltage/power that is put out by the inputPins?
//try replacing pinFwd and pinBck with analog output pins and trying various values
//float timer = 0;
long initTimer = 0;//store Micros() in this variable when you starta  new timer
long timerLimit = 10;
bool motorOn = false;

int analogSpeed = 200; //analogWrite value, goes from 0 to 255

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  delay(1000);
  //setup encoder output pins
  pinMode(output1, INPUT_PULLUP);
  pinMode(output2, INPUT_PULLUP);
  digitalWrite(output1, HIGH);
  digitalWrite(output2, HIGH);
  attachInterrupt(0, updateTicks, CHANGE);
  attachInterrupt(1, updateTicksBck, CHANGE);

  //setup motor pins
  pinMode(pinFwd, OUTPUT);
  pinMode(pinBck, OUTPUT);

  dirSwap();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("TICKS: ");
  Serial.println(ticks);

  //manage timer
  //Serial.print("TIMER: ");
  //Serial.println(micros());
 // Serial.print("TIMER LIMIT: ");
  //Serial.println(initTimer + timerLimit);
  /*
  if(millis() >= initTimer + timerLimit){
    toggleMotor();
    if(motorOn){
      initTimer = millis() + (timerLimit * 0.9);
    }else{
      initTimer = millis();
    }
    
  }*/
}

void dirSwap(){
  if(isBackward == true){
   // digitalWrite(pinFwd, HIGH);
   // digitalWrite(pinBck, LOW);
    analogWrite(pinFwd, analogSpeed);
    analogWrite(pinBck, LOW);
    isBackward = false; 
  }else{
   // digitalWrite(pinBck, HIGH);
   // digitalWrite(pinFwd, LOW);
    analogWrite(pinFwd, LOW);
    analogWrite(pinBck, analogSpeed);
    isBackward = true;
  }
}

//if analog input works this is deprecated
void toggleMotor(){
  Serial.println("RUNNING TOGGLEMOTOR");
  if(isBackward == true){
    if(motorOn == true){
      digitalWrite(pinFwd, LOW);
      digitalWrite(pinBck, LOW);
      motorOn = false; 
    }else{
      digitalWrite(pinFwd, LOW);
      digitalWrite(pinBck, HIGH);
      motorOn = true;
    }
    
  }else{
    if(motorOn == true){
      digitalWrite(pinBck, LOW);
      digitalWrite(pinFwd, LOW);
      motorOn = false;
    }else{
      digitalWrite(pinBck, LOW);
      digitalWrite(pinFwd, HIGH);
      motorOn = true;
    }
  }

 // initTimer = millis();
}

void updateTicks(){
  if(!isBackward){
    ticks++;
  if(ticks >= tickLimit){
    dirSwap();
   // toggleMotor();
    ticks = 0;
  }
  }
  
}

void updateTicksBck(){
  if(isBackward){
    ticks++;
    if(ticks >= tickLimit){
      dirSwap();
      ticks = 0;
    }
  }
}

void startTimer(){
  initTimer = millis();
 // timer = micros();
}
