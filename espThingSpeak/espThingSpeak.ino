#include<ESP8266WiFi.h>

const char* server = "api.thingspeak.com";
String apiKey ="Q8KUPY2CZRYGFMQ6";
const char* MY_SSID = "Akash"; 
const char* MY_PWD = "astr1x2096";

int value[8] = {45,60,22,55,81,75,12,54};
int sent = 0;

void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  sendValues(value);
  delay(15000);
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

void sendValues(int value[]) {
 WiFiClient client;
 if(client.connect(server, 80)) {
  Serial.println("Wifi Client Connected");

   String postStr = apiKey;
   for(int i = 0; i < 8; i++) {
    postStr += "&field"+String(i+1)+"=";
    postStr += String(value[i]);
   }
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(1000);
 }
 sent++;
 client.stop();
}

