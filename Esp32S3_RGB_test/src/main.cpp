#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#define LED_PIN    48
#define NUM_LEDS   1

const char* ssid = "Belkin_N+_34E59E";
const char* password = "";

WebServer server(80);  // Web server on port 80

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void handleRoot() {
  String page = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head><title>ESP32 LED Control</title></head>
    <body>
      <h1>ESP32 LED Control</h1>
      <p><a href="/on"><button>Turn ON</button></a></p>
      <p><a href="/off"><button>Turn OFF</button></a></p>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", page);
}

void handleOn() {
   // Red
  strip.setPixelColor(0, strip.Color(10, 0, 2));
  strip.show();
    // Off
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
  server.sendHeader("Location", "/");
  server.send(303);
}

// put function declarations here:
int myFunction(int, int);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup Web Server Routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  
  server.begin();
  Serial.println("HTTP server started");


  int result = myFunction(2, 3);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // put your setup code here, to run once:
 // Red
  strip.setPixelColor(0, strip.Color(0, 0, 1));
  strip.show();
  delay(1200);
    // Off
  
}

void loop() {
  // put your main code here, to run repeatedly:

  server.handleClient();


}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}