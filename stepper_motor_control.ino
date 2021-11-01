/*
This program is used to control the stepper motor for the coupler drive. Two push buttons are installed for the coupler traveling IN and OUT.  

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

bool limit_in_switch = LOW;
bool limit_out_switch = LOW;

bool pulse = LOW; 

int Delay = 500;  // The lower the delay, the faster the motor runs.

void setup()
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  pinMode(forward_button, INPUT_PULLUP);
  pinMode(backward_button, INPUT_PULLUP);

  pinMode(forward_LED, OUTPUT);
  pinMode(backward_LED, OUTPUT);

  pinMode(LM_in, INPUT);
  pinMode(LM_out, INPUT);
  
  digitalWrite(ENA, HIGH);      // LOW- MOTOR ON; HIGH- MOTOR OFF
  digitalWrite(PUL, pulse);
}

void loop()
{
  int forward = digitalRead(forward_button);
  int backward = digitalRead(backward_button);
  int lm_in = digitalRead(LM_in);
  int lm_out = digitalRead(LM_out);

  digitalWrite(forward_LED, LOW);
  digitalWrite(backward_LED, LOW);

  if (forward == LOW && backward == HIGH)
  {
    digitalWrite(forward_LED, HIGH);
    pulse = !pulse; 
    digitalWrite(ENA, LOW);
    digitalWrite(DIR, LOW);  // LOW- CW (FORWARD); HIGH- CCW (BACKWARD);
    digitalWrite(PUL, pulse);
    delayMicroseconds(Delay);
    // if (lm_in == HIGH || LM_out ==HIGH)
    // {
    //   digitalWrite(ENA, HIGH);
    // }
  }

  if (backward == LOW && forward == HIGH)
  {
    digitalWrite(backward_LED, HIGH);
    pulse = !pulse; 
    digitalWrite(ENA, LOW);
    digitalWrite(DIR, HIGH);  // LOW- CW (FORWARD); HIGH- CCW (BACKWARD);
    digitalWrite(PUL, pulse);
    delayMicroseconds(Delay); 
    // if (lm_in == HIGH || LM_out ==HIGH)
    // {
    //   digitalWrite(ENA, HIGH);
    // }
  }

  else {
    digitalWrite(PUL, pulse);
    digitalWrite(ENA, HIGH); 
  }
}