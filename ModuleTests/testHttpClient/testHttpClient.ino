#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";

String apiKey = "";
String apiUrl = "";

String getGPTAnswer(String inputTest) {
  HTTPClient client;
  client.setTimeout(10000);
  client.begin(apiUrl);
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Authorization", String(apiKey));

  String messages = "\"messages\": [{\"role\": \"user\", \"content\": \"" + inputTest + "\"}]";
  String model = "\"model\": \"glm-4\"";
  String payload = "{" + model + "," + messages + "}";
  Serial.println(payload);

  int httpResponseCode = client.POST(payload);
  if (httpResponseCode == 200) {
    String response = client.getString();
    client.end();
    Serial.println(response);

    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, response);
    String outputText = jsonDoc["choices"][0]["message"]["content"];
    return outputText;
  } else {
    client.end();
    Serial.printf("Error %i \n", httpResponseCode);
    return "error";
  }
}

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

    Serial.println("read: " + inputText);

    String answer = getGPTAnswer(inputText);
    Serial.println("Answer: " + answer);
  }
}
