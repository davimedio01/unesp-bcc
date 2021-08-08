int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i=1; i<=255; i++)
  {
    analogWrite(11, i);
    delay(50);
  }
  /*for(i=255; i>=1; i--)
  {
    analogWrite(11, i);
    delay(10);
  }*/
}
