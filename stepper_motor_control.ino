/*
This program is used to control the stepper motor for the coupler drive. Two
push buttons (with two limit switches used for travel protection) are installed
for the coupler traveling IN and OUT.  

Author: G. Chen
*/

// Define pins
int ENA = 2; 
int DIR = 3; 
int PUL = 4; 

int forward_button = 8;
int backward_button = 9;
int forward_LED = A0;
int backward_LED = A1;

int LM_in = 11;
int LM_out = 12;

bool pulse = LOW; 

int motor_delay = 5000;  // The lower the delay, the faster the motor runs.

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  pinMode(forward_button, INPUT_PULLUP);
  pinMode(backward_button, INPUT_PULLUP);

  pinMode(forward_LED, OUTPUT);
  pinMode(backward_LED, OUTPUT);

  pinMode(LM_in, INPUT_PULLUP);
  pinMode(LM_out, INPUT_PULLUP);
  
  digitalWrite(ENA, HIGH);      // LOW- MOTOR ON; HIGH- MOTOR OFF
  digitalWrite(PUL, pulse);
}

void moveForward(int Delay) {
  pulse = !pulse; 
  digitalWrite(ENA, LOW);
  digitalWrite(DIR, LOW);       // LOW- CW (FORWARD); HIGH- CCW (BACKWARD);
  digitalWrite(PUL, pulse);
  delayMicroseconds(Delay);
}

void moveBackward(int Delay) {
  pulse = !pulse; 
  digitalWrite(ENA, LOW);
  digitalWrite(DIR, HIGH);      // LOW- CW (FORWARD); HIGH- CCW (BACKWARD);
  digitalWrite(PUL, pulse);
  delayMicroseconds(Delay);
}

void forwardLEDBlink() {
  digitalWrite(forward_LED, LOW);
  delay(100);   // unit: [ms]
  digitalWrite(forward_LED, HIGH);
  delay(100);
}

void backwardLEDBlink() {
  digitalWrite(backward_LED, LOW);
  delay(100);
  digitalWrite(backward_LED, HIGH);
  delay(100);
}

void warningLEDBlink() {
  digitalWrite(backward_LED, LOW);
  digitalWrite(forward_LED, LOW);
  delay(100);
  digitalWrite(backward_LED, HIGH);
  digitalWrite(forward_LED, HIGH);
  delay(100);
}

void loop() {
  int forward = digitalRead(forward_button);
  int backward = digitalRead(backward_button);
  int limitswitch_forward = digitalRead(LM_in);
  int limitswitch_backward = digitalRead(LM_out);

  digitalWrite(forward_LED, LOW);
  digitalWrite(backward_LED, LOW);

  if (forward == LOW && backward == HIGH && limitswitch_forward == HIGH && limitswitch_backward == HIGH) {
    digitalWrite(forward_LED, HIGH);
    moveForward(motor_delay);
  }

  if (backward == LOW && forward == HIGH && limitswitch_forward == HIGH && limitswitch_backward == HIGH) {
    digitalWrite(backward_LED, HIGH);
    moveBackward(motor_delay);
  }

  while (limitswitch_forward == LOW && limitswitch_backward == HIGH) {
    forwardLEDBlink();
    int i = 0;
    while (i < 200 && backward == LOW && forward == HIGH) {
      digitalWrite(backward_LED, HIGH);
      moveBackward(motor_delay);
      i += 1;
    }
    break;
  }

  while (limitswitch_backward == LOW && limitswitch_forward == HIGH) {
    backwardLEDBlink();
    int i = 0;
    while (i < 200 && forward == LOW && backward == HIGH) {
      digitalWrite(forward_LED, HIGH);
      moveForward(motor_delay);
      i += 1;
    }
    break;
  }

  if (limitswitch_backward == LOW && limitswitch_forward == LOW) {
    warningLEDBlink();
  }

  else {
    digitalWrite(PUL, pulse);
    digitalWrite(ENA, HIGH); 
  }
}
