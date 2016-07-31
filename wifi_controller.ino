// server
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);
const char* ssid = "";
const char* password = "";

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(600, PIN, NEO_RGB + NEO_KHZ400);

void setColour(int led, int r, int g, int b){
  strip.setPixelColor(led, strip.Color(r, g, b));
  strip.show();
}

int getArg(char* key){
  for (uint8_t i=0; i<server.args(); i++){
    if (server.argName(i) == key){
       return server.arg(i).toInt();
    }
  }
}

// root
void handleRoot() {  
  server.send(200, "text/plain", "get rekt!");
}

// set all
void handleSetAll(){
  server.send(200, "text/plain", "hi");
  for (int i=0; i <= 600; i++){
    setColour(i, getArg("r"), getArg("g"), getArg("b"));
  }
  server.send(200, "text/plain", "Done");
}

// set led
void handleSetLED(){
  server.send(200, "text/plain", "hi");
  setColour(getArg("led"), getArg("r"), getArg("g"), getArg("b"));
  server.send(200, "text/plain", "Done");
}


void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/setall", handleSetAll);
  server.on("/set", handleSetLED);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  // turn on led ring
  strip.begin();
  strip.show();
}

void loop(void){
  server.handleClient();
}
