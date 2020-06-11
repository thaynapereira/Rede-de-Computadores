#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// config:
const char *ssid = "RedesComputadores";
const char *pw = "";
IPAddress ip(192, 168, 0, 1);
IPAddress netmask(255, 255, 255, 0);
const int port = 1234;

WiFiServer server(port);
WiFiClient client;

void setup() {
  
  pinMode(BUILTIN_LED,OUTPUT);
    
  Serial.begin(115200);

  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, pw);

  server.begin();

  Serial.println("ESP8266 RC receiver 1.1 powered by RoboRemo");
  Serial.println((String)"SSID: " + ssid + "  PASS: " + pw);
  Serial.println((String)"RoboRemo app must connect to " + ip.toString() + ":" + port);
}

void loop() {
  if(!client.connected()) {
    client = server.available();
    return;
  }

  // If client connected 
  if(client.available()) {
    Serial.println("connect client with code:");
    char c = (char)client.read();
    Serial.println(c);
    
    if (c == 'A'){ digitalWrite(LED_BUILTIN,HIGH); }
    
    if (c == 'B'){ digitalWrite(LED_BUILTIN,LOW); }
    
    if (c == 'C'){
      int intensidade = 0;
      do{
        analogWrite(LED_BUILTIN, intensidade);
        delay(30);
        intensidade +=5;
      }while(intensidade <= 1000);
      intensidade = 1000;
      do{
        analogWrite(LED_BUILTIN, intensidade);
        delay(30);
        intensidade -= 5;
      }while(intensidade >= 0);
    }
    
    if (c == 'D') {
    for(int i = 0; i < 5; i++){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN,LOW);
      delay(1000); }
  }
}
}
