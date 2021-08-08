void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // led no pino 8
}

void loop() {
  // put your main code here, to run repeatedly
  digitalWrite(8, HIGH); // liga
  delay(1000); //atraso em ms
  digitalWrite(8, LOW); // desliga
  delay(1000); // atraso em ms
}
