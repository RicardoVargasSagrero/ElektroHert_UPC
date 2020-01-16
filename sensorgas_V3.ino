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
String Num_Movil[]={"9211112377"}; // numeros a los que se envia el mensaje el mensaje, poner el mismo en Cantidad_Movil
int Cantidad_Movil=1; // depende de cuantos numeros tienes agregados
String estado="";
int x=12;
int AnalogPin=0;
int ResRead;

//se hizo declaracion de variables y librerias 

int valor_limite= 130;                  // Fiaja el valor limite en el que se activa la alarma    
                                        // Fije el valor despues de visualizar el nivel con el Monitor Serial
void setup() 
{ 
  Serial.begin(9600);                   // Activa el puerto Serial a 9600 Baudios
  pinMode(13,OUTPUT);  
  
  // Configura el Pin 13 como salida para el Zumbador
  SIM900.begin(19200);//Arduino se comunica con el SIM900 a una velocidad de 19200bps
   Serial.begin(19200);//Velocidad del puerto serial de arduino 
   delay(25000);//Tiempo prudencial para el escudo inicie sesión de red con tu operador
   pinMode(x,OUTPUT);
  SIM900.print("AT+CMGF=1\r");// comando AT para configurar el SIM900 en modo texto
  delay(200);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");//Configuramos el módulo para que muestre los SMS por el puerto serie.
  delay(200);
}



void loop() { 
  Serial.println(analogRead(A0));       // Envia al Serial el valor leido del Sensor MQ4 
 
  if(analogRead(A0) > valor_limite)    // Si la medida de gas metano es mayor de valor limite
   {   
      digitalWrite(13, HIGH);          // Enciende el Zumbador conectado al Pin 13
      Envio_SMS_Destinos();    
   }
   else{                                // Si es menor del valor limite apaga el Zumbador
      digitalWrite(13, LOW); 
   }
  delay (200);                          // Espera 300ms para realizar la proxima medida
}



//funsion de envio de mensaje
void Envio_SMS_Destinos() {                                                           
  for (int n = 1; n < Cantidad_Movil; n++) {                                            
    delay(1000);                                                                     
    SIM900.println("AT + CMGS = \"9211112377\"");  // Envia mensaje  
    delay(100);                                                                     
    SIM900.print("ALERTA TU ALARMA DE GAS SE ACTIVO");    // mensaje que se envía                              
    delay(100);                                                          
    SIM900.write((char)26); //ctrl+z                                               
    delay(3000);   
    Serial.println(); 
    Serial.print("Mensaje numero: ");   
    Serial.print(n+1);         
    Serial.print(" enviado"); 
  }
}
