#include <WiFi.h>

const char* ssid = "**********";
const char* password = "**********;

// Example using Serial2 on GPIO17 (TX), GPIO16 (RX)
void setup() {
  Serial.begin(9600);               // USB Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  Serial.println("ESP32 ready");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP:");
  Serial.println(WiFi.localIP());  
}

void loop() {
  WiFiClient client;
   if(!client.connect(IPAddress(192,168,1,4), 10000)){      
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }

  Serial.println(client.readString());
  if (client.readStringUntil('\n')=="pressed1") {
    Serial.println(client.readString());
    Serial2.println("pressed1");
  }

  if (client.readStringUntil('\n')=="pressed2") {
    Serial.println(client.readString());
    Serial2.println("pressed2");
  }


  client.stop();
  delay(1000);
}
