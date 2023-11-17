// Arduino DC motor speed and direction control
//docs
// https://www.ti.com/lit/ds/symlink/l293d.pdf?ts=1700135201050&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FL293D
//article with fritzing and code
// https://simple-circuit.com/arduino-dc-motor-speed-direction-control-l293d/
#define button   8
#define pot      0
#define pwm1     9
#define pwm2    10

boolean motor_dir = 0;
int motor_speed;

void setup() {
  Serial.begin(57600);
  pinMode(button, INPUT_PULLUP);
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);
}

void loop() {
  motor_speed = analogRead(pot) / 4;
  Serial.print("motorspeed is ");
  Serial.println(motor_speed);
  if(motor_dir)
    analogWrite(pwm1, motor_speed);
  else
    analogWrite(pwm2, motor_speed);
  if(!digitalRead(button)){                // If direction button is pressed
  Serial.println("BUTTON GET");
    while(!digitalRead(button));           // Wait until direction button released
    motor_dir = !motor_dir;                // Toggle direction variable
    if(motor_dir)
      digitalWrite(pwm2, 0);
    else
      digitalWrite(pwm1, 0);
  }else{
    Serial.println("NO BUTTON");
  }

}