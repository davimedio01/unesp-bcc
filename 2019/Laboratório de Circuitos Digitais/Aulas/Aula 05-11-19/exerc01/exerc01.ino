int potenciometro;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
}

void loop() {
  // put your main code here, to run repeatedly:
  potenciometro = analogRead(A0);
  Serial.println(potenciometro);
}
