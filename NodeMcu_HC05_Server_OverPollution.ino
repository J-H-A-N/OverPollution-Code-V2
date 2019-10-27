String Cont1="";
String Cont2="";
String Ap="";
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ARRIS-0DA2";                 //Network name
const char* password = "BB39D6DC937F314E";       //Network password
const char* mqtt_server = "broker.hivemq.com";   //Mqtt Free broker
WiFiClient espclient;

void callback(char* topic, byte* payload, unsigned int length1){       //Callback publish MQTT Server 
  
  Serial.print("Message arrived[");
  Serial.print(topic);
  Serial.println("]");
                                                           
  for (int i=0;i<length1;i++){
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
   _reconnect();
}

PubSubClient client(mqtt_server,1883,callback,espclient);   //Publish, Subscribe Method Client


void setup() {
  Serial.begin(9600);
   Serial.print("connecting");
  WiFi.begin(ssid,password); 
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
   Serial.println();
  _reconnect();
}
void _reconnect(){                      //reconnection to the server and subscription to the server
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  while(!client.connected()){
    if(client.connect("OverPollutionESP")){
      Serial.println("connected");
      Serial.println(ssid);
      client.subscribe("Contaminacion1");
      client.subscribe("Contaminacion2");
      client.subscribe("AirePurificado");
    } else {
      Serial.print("falied, rc = ");
      Serial.println(client.state());
      delay(500);
    }
  }
}

void Datos(){                 //  Data collection from bluetooth and sending data to the server
  
  if (Serial.available()>0){                        
   String texto = Serial.readString();
   
    if(texto.indexOf("A")>0){
       Cont1=texto;
      char Conta1 [15];
       Cont1.toCharArray(Conta1,15);                          
       client.publish("Contaminacion1", Conta1); 
    }
    else if(texto.indexOf("B")>0){
        Cont2=texto;
      char Conta2 [15];
      Cont2.toCharArray(Conta2,15);
       client.publish("Contaminacion2", Conta2); 
     
    }
    else if(texto.indexOf("C")>0){
       Ap=texto;
       char AirP [15];
      Ap.toCharArray(AirP,15);
      client.publish("AirePurificado",AirP); 
     
    }
   
   }

  
}

void loop(){
  Datos();
 
  if(!client.connected()){
    _reconnect();
  }

  client.loop();
  
  }
  
 
