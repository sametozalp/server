#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ozalp";
const char *password = "123456789";

//station
//access point
//bir de ikisinin de olduğu özellikleri var

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Ana Sayfa</h1><br><a href=''>LED Yak</a><br><a href=''>LED Sondur</a>");
}

void notFound() {
  server.send(200, "text/html", "<h1>Bulunamadi</h1>");
}

void led_yak(){
  digitalWrite(D7, HIGH);
}

void led_son(){
  digitalWrite(D7, LOW);
}

void setup() {
  pinMode(D7, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.print("erisim noktasi baslatiliyor..");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Sunucu IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
