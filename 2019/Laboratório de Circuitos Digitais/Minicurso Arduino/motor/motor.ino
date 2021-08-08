int pinMotor = 3;
int valPot = 0;
int valMotor;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinMotor, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valPot = analogRead(A0);
  valMotor = map(valPot, 0, 1023, 0, 255);
  analogWrite(pinMotor, valMotor);
}
