#include <ESP8266WiFi.h>   
                
String ssid     = ""; //NOMBRE Red1
String password = "";
 
WiFiServer server(80);                   
 
int pinLed =16;                  
int estado = 0;                         
 
byte cont = 0;
byte max_intentos = 50;

void setup() {
   // Inicia Serial
  Serial.begin(115200);//MONITOR SERIAL
  Serial.println("\n");

  pinMode(pinLed,OUTPUT);

  // Conexión WIFI
  WiFi.mode(WIFI_STA);//
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }
  if (cont < max_intentos) {
  Serial.println("");
  Serial.println("********************************************");
  Serial.print("Conectado a la red WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("macAdress: ");
  Serial.println(WiFi.macAddress());
  Serial.println("*********************************************");
  }
  else { //no se conecto
 Serial.println("------------------------------------");
      Serial.println("Error de conexion");
      Serial.println("------------------------------------");
      Serial.print("0 WIFI PROCESO ESTADO 1 ERROR SSID 2 CONEXION EXITOSA 3 CONTRASEÑA ES INCORRECTA  6 MODULO ESTACION NO CONFIGURADO CORRECTAMENTE");
      Serial.println("\n");
       Serial.println("Error numero");
      Serial.println(WiFi.status());
      
  }


 
  server.begin(); //begin() levantamos el servidor EL QUE SE INICIO ARRIBA
  digitalWrite(pinLed, 0);
 
}

 
void loop()
{

    WiFiClient client = server.available();  //objeto CLASE CLIENTES ()DETECTA NUEVO CLIENTE AVALAIBLE () DETECTA EL NUEVO OBJETO CLASE CLIENTE
  //()DETECTA UN CLIENTE NUEVO DEL OBJETO CLASE WIFISERVER
  if (!client) {
    return;
  }
 

  Serial.println("nuevo cliente");
  while(!client.available()){ //ESPERA A UN CLIENTE DISPONIBLE
    delay(1);
  }
 

  String peticion = client.readStringUntil('\r'); //LEE LA PETICION DEL CLIENTE
  Serial.println(peticion);
client.flush(); //limpia la peticion del cliente

  if(peticion.indexOf("LED=ON") != -1)
  {
    estado=1;
  }
  if(peticion.indexOf("LED=OFF") != -1)
  {
    estado=0;
  }

  digitalWrite(pinLed, estado);

  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println("");

    //INICIA LA PAGINA

client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>");
client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
client.println("<title>CS</title></head>");
client.println("<body style='font-family: Century gothic; width: 800;'><center>");
client.println("<div style='box-shadow: 0px 0px 20px 8px rgba(0,0,0,0.22); padding: 20px; width: 300px; display: inline-block; margin: 30px;'> ");
client.println("<h1>LED PRUEBA</h1>");

if(estado==1)
  client.println("<h2>El led esta ENCENDIDO</h2>");
else
  client.println("<h2>El led esta APAGADO</h2>");
        
client.println("<button style='background-color:red;  color:white; border-radius: 10px; border-color: rgb(255, 0, 0);' ");
client.println("type='button' onClick=location.href='/LED=OFF'><h2>Apagar</h2>");
client.println("</button> <button style='background-color:green; color:white; border-radius: 10px; border-color: rgb(25, 255, 4);' ");
client.println("type='button' onClick=location.href='/LED=ON'><h2>Encender</h2>");
client.println("</button></div></center></body></html>");

    //FIN DE LA PAGINA

  delay(10);
  Serial.println("Peticion finalizada");
  Serial.println("");  
}
