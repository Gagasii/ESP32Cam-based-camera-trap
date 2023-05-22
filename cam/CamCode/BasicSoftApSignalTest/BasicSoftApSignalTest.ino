#include <WiFi.h>

const char* ssid = "JulianCam";
const char* password = "123";


void setup() {
  Serial.begin(9600);

  // Set up softAP with SSID "JulianCam" and password "123"
  WiFi.softAP(ssid, password);

  // Print the softAP IP address so you can connect to it from another device
  Serial.print("SoftAP 'JulianCam' IP address: ");
  Serial.println(WiFi.softAPIP());


}

void loop() {

}
