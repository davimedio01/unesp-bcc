int ledPino = 8;
int botaoPino = 2;
int botao = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPino, OUTPUT);
  pinMode(botaoPino, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  botao = digitalRead(botaoPino);

  if(botao == HIGH){
    digitalWrite(ledPino, HIGH);
  }
  else{
    digitalWrite(ledPino, LOW);
  }
}
