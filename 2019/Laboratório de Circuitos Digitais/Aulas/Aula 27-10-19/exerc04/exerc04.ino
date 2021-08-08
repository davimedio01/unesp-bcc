int verifica, aux;
void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    verifica = Serial.read();
    if(verifica != 10)
      aux = verifica; 
  }

  analogWrite(11, aux);
}
