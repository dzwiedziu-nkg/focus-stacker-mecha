//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>


int state = LOW;
int LED = LED_BUILTIN;
char ON = LOW;
char OFF = HIGH;
char RUN = HIGH;
char STOP = LOW;


AsyncWebServer server(80);

const char* ssid = "my_wifi";
const char* password = "********";

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {

    Serial.begin(9600);
  
    // init GPIO for control mecha and camera
    pinMode(LED, OUTPUT);
    pinMode(D0, OUTPUT); // Camera take photo 
    pinMode(D1, OUTPUT); // Camera AF
    pinMode(D2, OUTPUT); // motor IN1
    pinMode(D3, OUTPUT); // motor IN2
  
    digitalWrite(LED, OFF);
    digitalWrite(D0, OFF);
    digitalWrite(D1, OFF);
    digitalWrite(D2, STOP);
    digitalWrite(D3, STOP);
    // end of GPIO config

    // config WiFi connection
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // end of WiFi config

    // implement REST API for Web App backend
    /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });*/

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    // end of REST API config
  
    // config static files for WebApp Frontend
    SPIFFS.begin();
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.onNotFound(notFound);
    // end of config WebApp Fronent
    
    // run HTTP server
    server.begin();
}

void loop() {
  // Pause for stabilize camera
  delay(500); 

  // Camera AF
  digitalWrite(D0, OFF);
  digitalWrite(D1, ON);
  delay(500); // (1s for stabilize)
  
  // Camera take foto
  digitalWrite(D0, ON);
  digitalWrite(D1, ON);
  delay(1000);
  
  // Pause after take photo (max 2s exposure)
  digitalWrite(D0, OFF);
  digitalWrite(D1, OFF);
  delay(1000);
  
  // Run motor
  digitalWrite(LED, ON);
  digitalWrite(D2, RUN);
  digitalWrite(D3, STOP);
  delay(1000); // 1s  for motor running
  
  // Stop motor
  digitalWrite(LED, OFF);
  digitalWrite(D2, STOP);
  digitalWrite(D3, STOP);
}
