#include "Ubidots.h"

#define DEVICE  "esp-8266"  // nombre de equipo
#define TOKEN  "BBFF-oqUrcbCh39PxOUEKdrik9vLRhgj6tQ"  // token ubidots
#define VARIABLE  "leda"  // led variable 


#define WIFISSID "INVITADOS CFD" // Put here your Wi-Fi SSID
#define PASSWORD "CFD2021$" // Put here your Wi-Fi password

Ubidots client(TOKEN);
const byte  Pin_led = D4;

void setup() {
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW); 
}

void loop() 
{
    float Valor_Led = client.get(DEVICE, VARIABLE);
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);

     if (Valor_Led==1){      
      digitalWrite(Pin_led, HIGH);
      }else
      {
        digitalWrite(Pin_led, LOW);
      }
      
    }else{
      Serial.println(F("Error obteniendo Valor_Led"));
    }
   
    delay(500);
}
