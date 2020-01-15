/*#include <GSM.h>
/*#include <GSM3CircularBuffer.h>
#include <GSM3IO.h>
#include <GSM3MobileAccessProvider.h>
#include <GSM3MobileCellManagement.h>
#include <GSM3MobileClientProvider.h>
#include <GSM3MobileClientService.h>
#include <GSM3MobileDataNetworkProvider.h>
#include <GSM3MobileMockupProvider.h>
#include <GSM3MobileNetworkProvider.h>
#include <GSM3MobileNetworkRegistry.h>
#include <GSM3MobileServerProvider.h>
#include <GSM3MobileServerService.h>
#include <GSM3MobileSMSProvider.h>
#include <GSM3MobileVoiceProvider.h>
#include <GSM3ShieldV1.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1BandManagement.h>
#include <GSM3ShieldV1BaseProvider.h>
#include <GSM3ShieldV1CellManagement.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM3ShieldV1ModemCore.h>
#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3ShieldV1MultiClientProvider.h>
#include <GSM3ShieldV1MultiServerProvider.h>
#include <GSM3ShieldV1PinManagement.h>
#include <GSM3ShieldV1ScanNetworks.h>
#include <GSM3ShieldV1ServerProvider.h>
#include <GSM3ShieldV1SMSProvider.h>
#include <GSM3ShieldV1VoiceProvider.h>
#include <GSM3SMSService.h>
#include <GSM3SoftSerial.h>
#include <GSM3VoiceCallService.h>*/

/* Alarma de Gas upc
  Hecho por:
  Conecta el Arduino con el Sensor de Gas MQ4 y cuando el nivel de concentracion de gas metano
  Supera un limite se activa una alarma sonora, el nivel de gas metado se puede visualizar por
  el Monitor Serial.
  Conexiones:
  ARDUINO      MQ4      Zumbador
  5V           Vcc
  GND          GND
  A0           A0
  Pin 13        +
  GND         GND
*/

#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);//Configuración de los pines serial por software **checar los pines**
String Num_Movil[] = {"9211112377", "9211199457", "9212395682"}; // numeros moviles a quien se envia el mensaje el mensaje, poner el mismo en Cantidad_Movil
int Cantidad_Movil = 3; // las cantidades de numeros celular a enviar
String estado = "";
int x = 12;
int AnalogPin = 0;
int ResRead;

//se hizo declaracion de variables y librerias

int valor_limite = 250;                 // Fija el valor limite en el que se activa la alarma
// Fije el valor despues de visualizar el nivel con el Monitor Serial
void setup()
{
  SIM900.begin(19200); //arduino se comunica a esa velocidad bps
  Serial.begin(19200); //velocidad del puerto serial del arduino
  delay(20000);//tiempo para esperar señal
  pinMode(x,OUTPUT);
  SIM900.print("AT+CMGF=1\r"); comando para poner en modo sms
  delay(200);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");//config modulo para muestre los sms por puerto serie
  delay(200);
  
  
  Serial.begin(9600);                   // Activa el puerto Serial a 9600 Baudios
  pinMode(13, OUTPUT);                  // Configura el Pin 13 como salida para el Zumbador
}


void loop() {
  Serial.println(analogRead(A0));       // Envia al Serial el valor leido del Sensor MQ4

  if (analogRead(A0) > valor_limite)   // Si la medida de gas metano es mayor de valor limite
  {
    digitalWrite(13, HIGH);          // Enciende el Zumbador conectado al Pin 13
    enviar_SMS();                     //se manda a llamar la funsion de envio de mensajes
  }
  else {                               // Si es menor del valor limite apaga el Zumbador
    digitalWrite(13, LOW);
  }
  delay (300);                          // Espera 300ms para realizar la proxima medida
}



//funcion de envio de mensaje
void enviar_SMS() {
  for (int n = 0; n < Cantidad_Movil; n++) {
    delay(1000);
    SIM900.println("AT + CMGS = \"" + Num_Movil[n] + "\"");  // Envia mensaje
    delay(100);
    SIM900.print(" -- Alerta! Se detecto la presecia de GAS -- ");    // mensaje que se envía
    delay(100);
    SIM900.write((char)26); //ctrl+z
    delay(3000);
    Serial.println();
    Serial.print("Mensaje numero: ");
    Serial.print(n + 1);
    Serial.print("enviado");
  }
}