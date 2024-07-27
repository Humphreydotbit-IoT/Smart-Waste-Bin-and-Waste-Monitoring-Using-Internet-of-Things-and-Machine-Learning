#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "2GY13A";
const char* password = "he7REeRG";

// Replace with your MQTT Broker's IP address
const char* mqtt_server = "192.168.1.27";

// MQTT Broker's user and password
const char* mqtt_user = "TUN";
const char* mqtt_password = "123";
const char* waste_topic = "bin/wasteLevel";
const char* battery_topic = "bin/batteryLevel";

WiFiClient espClient;
PubSubClient client(espClient);

// Ultrasonic sensor pins
const int trigPin = 33; // Updated pin number
const int echoPin = 32; // Updated pin number

// Battery level pin
const int batteryPin = 34;

// Ultrasonic sensor range in cm
const float maxDistance = 400.0;
const float minDistance = 2.0;

// Sound speed in cm/uS
#define SOUND_SPEED 0.034

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1884);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(batteryPin, INPUT);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
        Serial.println("connected");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);
      }
    }
  }
  client.loop();

  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 50000);
  float distanceCm = duration * SOUND_SPEED/2;

  // Check if the distance is within the defined range
  if (distanceCm <= maxDistance && distanceCm >= minDistance) {
    float wasteLevel = (1 - ((distanceCm - minDistance) / (maxDistance - minDistance))) * 100.0;

    // Read battery level
    int sensorValue = analogRead(batteryPin);
    float batteryVoltage = sensorValue * (3.3 / 4095.0);
    float batteryLevel = (batteryVoltage / 4.2) * 100.0;

    // Convert float to string
    char wasteLevelStr[8];
    dtostrf(wasteLevel, 1, 2, wasteLevelStr);
    char batteryLevelStr[8];
    dtostrf(batteryLevel, 1, 2, batteryLevelStr);

    // Publish waste level and battery level to MQTT broker
    client.publish(waste_topic, wasteLevelStr);
    client.publish(battery_topic, batteryLevelStr);

    // Print the distance and levels to the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Waste Level (%): ");
    Serial.println(wasteLevelStr);
    Serial.print("Battery Level (%): ");
    Serial.println(batteryLevelStr);
  } else {
    Serial.println("Distance out of range.");
  }
  delay(1000); // Wait before sending the next data
}
