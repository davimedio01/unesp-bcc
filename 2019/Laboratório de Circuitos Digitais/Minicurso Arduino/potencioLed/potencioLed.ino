int pinLed  = 3;
int valPot = 0;
int valLed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valPot = analogRead(A0);
  delay(30);
  valLed = map(valPot, 0, 1023, 0, 255);
  analogWrite(pinLed, valLed);
  delay(30);
}
