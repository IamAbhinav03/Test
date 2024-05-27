#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32";
const char* password = "12345678";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_Root);
  server.on("/value", handle_Value);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_Root() {
  server.send(200, "text/plain", "Hello from ESP32!");
}

void handle_Value() {
  int randomNumber = random(0, 2);
  Serial.print("Random number: ");
  Serial.println(randomNumber);
  server.send(200, "text/plain", String(randomNumber));
}