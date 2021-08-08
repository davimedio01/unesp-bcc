float sensor_temp, aux;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensor_temp = analogRead(A0);
  aux = (sensor_temp/2);

  //aux *= 5;
  Serial.print("A temperatura aproximada eh: ");
  Serial.print(aux);
  Serial.print("°C\n");
  delay(2000);
}
