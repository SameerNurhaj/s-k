#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Sameer !";
const char* password = "MDsameer@786";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  String phoneNumber = "+9779807277110";
  String message = "Gas leakage detected in the kitchen! Please take necessary action.";

  String url = "https://api.twilio.com/2010-04-01/Accounts/ACd588dc72344fffad4962e1707d1a3961/Messages.json";
  url += "?To=whatsapp%3A%2B" + phoneNumber;
  url += "&From=whatsapp%3A%2B+14155238886";
  url += "&Body=" + message;

  HTTPClient http;
  http.begin(url);
  http.setAuthorization("ACd588dc72344fffad4962e1707d1a3961", "c705343bc13a9ae54646045b34a4cd52");

  int httpResponseCode = http.POST("");
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error on sending message. Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

}