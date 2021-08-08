int led = 9;
int brilho = 0;
int variacao = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, brilho);

  brilho += variacao;

  if(brilho <= 0 || brilho >= 255){
    variacao = -variacao;
  }

  delay(1);
}
