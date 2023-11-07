/*#include <ESP8266WiFi.h>
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
}*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//****************
#define ADC_pin A0
int okunan_ADC=0;
float sicaklik=0.0;
//****************
const char *ag_adi = "ozalp";
const char *sifre = "123456789";

ESP8266WebServer sunucu(80);
//****************
void setup() 
{
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  Serial.println("Erisim Noktasi Baslatiliyor");

  WiFi.softAP(ag_adi, sifre);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Sunucu IP adresi: ");
  Serial.println(myIP);
  
  sunucu.on("/", anasayfa);
  sunucu.on("/iletisim",iletim);
  sunucu.on("/led_yak",led_yak_fonk);
  sunucu.on("/led_son",led_son_fonk);
  sunucu.onNotFound(sayfa_bulunamadi);
  sunucu.begin();
}
//*****************
void loop() 
{
  sunucu.handleClient();
}
//*****************
void anasayfa() {
  sicaklik_olc();
  String sayfa="<html>";
  sayfa+="<body>";
  sayfa+="<h1>Baglandiniz</h1>";
  sayfa+="<p>Bu bir paragraf</p>";
  sayfa+="<p>Oda sicakligi: </p>"+String(sicaklik);
  sayfa+="<a href='/iletisim'> Iletisim </a>";
  sayfa+="<a href='/led_yak'> LED'i yak </a>";
  sayfa+="<a href='/led_son'> LED'i sondur</a>";
  sayfa+="</body>";
  sayfa+="</html>";
  
  sunucu.send(200, "text/html", sayfa);
}
//*****************
void iletim() {
  sunucu.send(200, "text/html", "<h1>2742252525</h1>");
}
//****************
void led_yak_fonk() {
  String sayfa="";
  sayfa="<h1>LED yaniyor</h1>";
  sayfa+="<a href='/led_son'> LED'i sondur</a>";
  sunucu.send(200, "text/html", sayfa);
  digitalWrite(D7,HIGH);
}
//****************
void led_son_fonk() {
  String sayfa="";
  sayfa="<h1>LED sondu</h1>";
  sayfa+="<a href='/led_yak'> LED'i yak</a>"; 
  sunucu.send(200, "text/html", sayfa);
  digitalWrite(D7,LOW);
}
//*****************
void sayfa_bulunamadi() {
  sunucu.send(400, "text/html", "<h1>Sayfa Bulunamiyor</h1>");
}
//***************
void sicaklik_olc()
{
  sicaklik=((analogRead(ADC_pin)*1000)/1023.0)/10.0;
}
