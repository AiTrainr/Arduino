#define _GNU_SOURCE
#include <stdlib.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Replace with your network credentials
const char* ssid = "Timmons";
const char* password = "oddmango278";

// Data wire is plugged into GPIO4 on the ESP32
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Set the temperature sensor address
DeviceAddress insideThermometer = { 0x28, 0xFF, 0x27, 0x3B, 0x8C, 0x16, 0x02, 0x91 };

// Create an instance of the WiFiServer library
WiFiServer server(80);

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Start the OneWire and DallasTemperature libraries
  sensors.begin();

  // Set the resolution to 10-bit (good enough for most purposes)
  sensors.setResolution(insideThermometer, 10);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // If connected, print the IP address of the ESP32
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Send the temperature data to the client
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempC(insideThermometer);
  float temperatureF = (temperatureC * 1.8) + 32.0;
  String temperatureString = String(temperatureF);
  client.println(temperatureString);

  // Close the connection
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
