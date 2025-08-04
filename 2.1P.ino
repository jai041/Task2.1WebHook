#include <DHT.h>
#include <WiFiNINA.h>
#include "ThingSpeak.h"

// DHT22 sensor settings
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid = "Jai's iPhone";
const char* password = "Gladiator@1983";

// ThingSpeak configuration
const long channelID = 3025302;
const char* writeAPIKey = "V8OKF76LX8LM29MQ";
WiFiClient client;

void setup() {
Serial.begin(9600);
dht.begin();

// Connect to WiFi
Serial.print("Connecting to WiFi...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("\nConnected to WiFi");

// Start ThingSpeak
ThingSpeak.begin(client);
}

void loop() {
float temperature = dht.readTemperature(); // Celsius

// Check if reading failed
if (isnan(temperature)) {
Serial.println("Failed to read temperature from DHT sensor!");
delay(2000);
return;
}

// Print to Serial Monitor
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.println(" °C");

// Upload to ThingSpeak
ThingSpeak.setField(1, temperature); // Field 1: Temperature
int response = ThingSpeak.writeFields(channelID, writeAPIKey);

if (response == 200) {
Serial.println("Data sent to ThingSpeak successfully.");
} else {
Serial.print("Error sending data. HTTP code: ");
Serial.println(response);
}

delay(15000); // Wait 15 seconds before next reading
}