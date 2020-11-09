#include <WiFi.h>
#define WLAN_SSID      "The Morty - est Morty"
#define WLAN_PASS       "Margaritarick" 

const char *ssid = "ESPecially not your network";
const char *password = "ilovemycactus";
 
void setup() {
  
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
 
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
 
}
 
void loop() {}
