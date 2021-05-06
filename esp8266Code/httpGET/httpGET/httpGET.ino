
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifipassword.h" 


#define USE_SERIAL Serial



const char* ssid = "Picky_ASUS_00_2G";
const char* pass = WIFI_PASSWORD;


void setup() {
  USE_SERIAL.begin(115200);
  
  int numberOfNetworks = WiFi.scanNetworks();
 
  for(int i =0; i<numberOfNetworks; i++){
 
    USE_SERIAL.print("Network name: ");
    USE_SERIAL.println(WiFi.SSID(i));
    USE_SERIAL.print("Signal strength: ");
    USE_SERIAL.println(WiFi.RSSI(i));
    USE_SERIAL.println("-----------------------");
 
  }

  
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { 
    USE_SERIAL.println("."); 
    delay(500);
  } 

  USE_SERIAL.println(""); 
  USE_SERIAL.println("Wi-Fi connected"); 
  USE_SERIAL.print("IP Address : ");
  USE_SERIAL.println(WiFi.localIP()); 

  httpPOST();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void httpGet(){
  HTTPClient http;

  char *url = "http://192.168.2.66:8080/";

  http.begin(url);
  int resCode = http.GET();

  USE_SERIAL.println(resCode);
  
  String res = http.getString();
  USE_SERIAL.println(res);

  parserMessage(res);

  http.end();
}


void httpsGet(){
  HTTPClient http;

  char *url = "https://swapi.dev/api/people/1/";

  String fingerprints = "62 62 6D 05 ......";
  
  http.begin(url, fingerprints);
  int resCode = http.GET();

  USE_SERIAL.println(resCode);
  
  String res = http.getString();
  USE_SERIAL.println(res);

  parserMessage(res);

  http.end();
}


void httpPOST(){
  HTTPClient http;
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");

  DynamicJsonDocument postMessage(2048);
  postMessage["Arduino"] = "Hi I'm ESP8266";
  
  String jsonBody;
  serializeJson(postMessage, jsonBody);
  
  char *url = "http://192.168.2.66:8080/";

  http.begin(url);
  int resCode = http.POST(jsonBody);

  USE_SERIAL.println(resCode);
  
  String res = http.getString();
  USE_SERIAL.println(res);

  parserMessage(res);

  http.end();
}


void parserMessage(String res){
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, res);
  const char* _message = doc["message"];
  const char* _name = doc["name"];
  USE_SERIAL.print("message: ");
  USE_SERIAL.println(_message);

  USE_SERIAL.print("name: ");
  USE_SERIAL.println(_name);
}
