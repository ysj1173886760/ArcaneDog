#include <WiFi.h>

const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  Serial.print("ssid: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.println(WiFi.localIP());

}

void loop() {
  if (Serial.available()) {
    String inputText = Serial.readStringUntil('\n');

    Serial.println("get: " + inputText);
  }
}
