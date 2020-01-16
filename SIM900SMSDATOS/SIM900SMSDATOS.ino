//Pruebas SIM900 enviar y recibir datos
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7,8);
void setup() {
  // put your setup code here, to run once:
  SIM900.begin(19200);
  Serial.begin(19200);    
  //delay(1000);    
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
    SIM900.write(Serial.read());
  if(SIM900.available() > 0)
    Serial.write(SIM900.read());
  //delay(200);
}
