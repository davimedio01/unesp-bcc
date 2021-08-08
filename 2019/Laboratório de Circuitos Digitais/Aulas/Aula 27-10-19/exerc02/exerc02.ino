int led1 = 13, led2 = 12, led3 = 11, led4 = 10, controlador = 9;
int teste = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(controlador, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(controlador) == HIGH)
  {
    if(teste<=13 && teste>=10)
    {
      digitalWrite(teste, HIGH);
      delay(1000);
      digitalWrite(teste, LOW);
      teste--;
    }
    else
      teste = 13;
  }
  else if (digitalRead(controlador) == LOW)
  {
    if(teste<=13 && teste>=10)
    {
      digitalWrite(teste, HIGH);
      delay(1000);
      digitalWrite(teste, LOW);
      teste++;
    }
    else
      teste = 10;
  } 
  
}
