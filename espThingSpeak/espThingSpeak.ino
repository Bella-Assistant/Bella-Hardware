#include<ESP8266WiFi.h>

const char* server = "api.thingspeak.com";
String apiKey ="Q8KUPY2CZRYGFMQ6";
const char* MY_SSID = "Akash"; 
const char* MY_PWD = "astr1x2096";

int value[7] = {45,82,76,55,81,54,12};
int sent = 0;

void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  main();
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
   for(int i = 0; i < 7; i++) {
    postStr += "&field"+String(i+1)+"=";
    postStr += String(value[i]);
   }
   postStr += "&field8=";
   postStr += "S235";
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(15000);
 }
 sent++;
 client.stop();
}

int matrix[25][25], visited_cities[10], limit, cost = 0;
 
int tsp(int c) {
 int count, nearest_city = 999;
 int minimum = 999, temp;
 for(count = 0; count < limit; count++) {
  if((matrix[c][count] != 0) && (visited_cities[count] == 0)) {
    if(matrix[c][count] < minimum) {
      minimum = matrix[count][0] + matrix[c][count];
    }
    temp = matrix[c][count];
    nearest_city = count;
  }
 }
 if(minimum != 999) {
  cost = cost + temp;
  }
  return nearest_city;
}
 
void minimum_cost(int city) {
 int nearest_city;
 visited_cities[city] = 1;
 Serial.println(city);
 nearest_city = tsp(city);
 if(nearest_city == 999) {
  nearest_city = 0;
  Serial.println(nearest_city);
  cost = cost + matrix[city][nearest_city];
  return;
 }
 minimum_cost(nearest_city);
}
 
int main() { 
 // Doesn't do shit!
 return 0;
 Serial.println("Path");
 minimum_cost(0);
 Serial.println("Minimum Cost");
 Serial.println(cost);
 return 0;
}
