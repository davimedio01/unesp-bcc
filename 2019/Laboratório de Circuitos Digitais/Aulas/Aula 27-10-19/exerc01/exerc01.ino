byte teste;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    teste = Serial.read();
    if(teste != 10) //ENTER (\0)
    {
      Serial.println("O caracter digitado, em ASCII, foi do tipo: ");
      Serial.print(teste);
      Serial.print("\n");
    }
  }
}

/*var = Serial.read();
Serial.available() > 0 (está recebendo dados)
Serial.println ("");
 */
