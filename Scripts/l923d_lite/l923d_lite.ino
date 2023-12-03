//updateEncoder stuff comes from https://electricdiylab.com/controlling-n20-encoder-micro-gear-motor-with-arduino/
//An attempt at making a lighter version of a script that operates electromagnetic motors using the L293D motor driver with a library that operates it
//It also uses the RotaryEncoder library to take advantage of motors we purchased that come with an encoder soldered on.
//Can't remember if this works or not, one of the known issues was that it was incapable of turning specific distances reapeadtly without error.
//Its also sort of overcomplicated for what we wanted to do.
#include <L293.h>
#include <RotaryEncoder.h>
#define use_standalone

const int speedPin = 5;
const int forwardPin = 9;
const int reversePin = 10;

L293 motor(speedPin, forwardPin, reversePin);

int SPEED = 255;


const int outputA = 2; //encoder output as digital
const int outputB = 3;
volatile int lastEncoded = 0; // Here updated value of encoder store.
volatile long encoderValue = 0; // Raw encoder value

#define AoutputA A5
#define AoutputB A4

//RotaryEncoder encoder(AoutputA, AoutputB, RotaryEncoder::LatchMode::FOUR3);
RotaryEncoder encoder(outputA, outputB, RotaryEncoder::LatchMode::TWO03);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.print("SETUP COMPLETE");
  motor.forward(SPEED);
 // motor.back(SPEED);
  motor.stop();
  pinMode(outputA, INPUT_PULLUP);
  pinMode(outputB, INPUT_PULLUP);
  digitalWrite(outputA, HIGH); //turn pullup resistor on
  digitalWrite(outputB, HIGH); //turn pullup resistor on

   //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
 // encoder.setPosition(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("LOOP!");
  /*
  Serial.print("output C1: ");
  Serial.println(digitalRead(outputA));
  Serial.print("output C2: ");
  Serial.println(digitalRead(outputB));
  encoder.tick();
  float pos = encoder.getPosition();*/
 // Serial.println(pos);
  Serial.println(encoderValue);
}

void updateEncoder(){
  int MSB = digitalRead(outputA); //MSB = most significant bit
  int LSB = digitalRead(outputB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; //store this value for next time

}
