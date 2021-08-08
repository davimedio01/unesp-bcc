byte controle;
int led1 = 13, led2 = 12, led3 = 11, led4 = 10, aux_leds = 13, velocidade = 1000, aux_sentido = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0)
  {
    controle = Serial.read();
    if(controle==49)
      aux_sentido=1;
    else if(controle==50)
      aux_sentido=0;
    else if(controle==51)
      velocidade = 500;
    else if(controle==52)
      velocidade = 300;
    else if(controle==53)
      velocidade = 150;
  }

  
  if(aux_sentido)
  {
    if(aux_leds<=13 && aux_leds>=10)
      {
        digitalWrite(aux_leds, HIGH);
        delay(velocidade);
        digitalWrite(aux_leds, LOW);
        aux_leds--;
      }
      else
        aux_leds = 13; 
  }
  else if(!aux_sentido)
  {
    if(aux_leds<=13 && aux_leds>=10)
      {
        digitalWrite(aux_leds, HIGH);
        delay(velocidade);
        digitalWrite(aux_leds, LOW);
        aux_leds++;
      }
      else
        aux_leds = 10; 
  }
  
}
