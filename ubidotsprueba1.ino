
#include <ESP8266WiFi.h>   
#include "Ubidots.h"

#define DEVICE  "esp-8266"  // nombre de equipo
#define TOKEN  "BBFF-oqUrcbCh39PxOUEKdrik9vLRhgj6tQ"  // token ubidots
#define VARIABLE  "leda"  // led variable 
#define led2   "ledb"  //variable 2 
/*#define led3   "ledc" */

#define WIFISSID "Red1" // wifi
#define PASSWORD "12345frank" // pass
Ubidots client(TOKEN);
const byte  Pin_led = D4;

const byte  Pin_leds= D2;

/*const byte  Pin_ledss= D0;*/

      

void setup() {
     
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW); 
    
    pinMode(Pin_leds, OUTPUT);
    digitalWrite(Pin_leds, LOW);


  /*  pinMode(Pin_ledss, OUTPUT);
    digitalWrite(Pin_ledss, LOW);*/
}

void loop() 
{
    float Valor_Led= client.get(DEVICE, VARIABLE);
    float Valor_Leds= client.get(DEVICE, led2);
   /* float Valor_Ledss= client.get(DEVICE, led3);*/
Serial.println(Valor_Led);
Serial.println(Valor_Leds);
/*Serial.println(Valor_Ledss);*/
    
    
   
     if (Valor_Led==1){      
      digitalWrite(Pin_led, HIGH);
      }
      
      else      {
        digitalWrite(Pin_led, LOW);
      } 
      
      if (Valor_Leds==1){      
      digitalWrite(Pin_leds, HIGH);
      }
      else      {
        digitalWrite(Pin_leds, LOW);
      }
  
 /*     if (Valor_Ledss==1){      
      digitalWrite(Pin_ledss, HIGH);
      }
      else      {
        digitalWrite(Pin_ledss, LOW);
      }
  */
       
  
    
   
    delay(2000);
}
