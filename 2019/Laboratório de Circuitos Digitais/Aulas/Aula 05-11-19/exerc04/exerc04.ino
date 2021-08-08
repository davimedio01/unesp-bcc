float sensor_luz, aux;
const int led_claro = 13;
const int led_medio = 12;
const int led_escuro = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_claro, OUTPUT);
  pinMode(led_medio, OUTPUT);
  pinMode(led_escuro, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_luz = analogRead(A0);
  //aux = (1000.00/(sensor_luz+1020.00))*(1020.00);

  Serial.print("A luminosidade está: ");
  if(sensor_luz <= 950.00)
  {
    Serial.println("Escura");
    digitalWrite(led_escuro, HIGH); 
    digitalWrite(led_medio, LOW); 
    digitalWrite(led_claro, LOW); 
  }
  else if(sensor_luz > 1000.00)
  {
    Serial.println("Clara");
    digitalWrite(led_claro, HIGH); 
    digitalWrite(led_medio, LOW); 
    digitalWrite(led_escuro, LOW); 
  }
  else
  {
    Serial.println("Penumbra");
    digitalWrite(led_medio, HIGH); 
    digitalWrite(led_claro, LOW); 
    digitalWrite(led_escuro, LOW); 
  }
}
