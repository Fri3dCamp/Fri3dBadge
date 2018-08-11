#include <Arduino.h>
#include <WiFi.h>
#include <Fri3dMatrix.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


char* ssid     = "fri3d-badge";
char* password = "fri3d-badge";

 
#define NTP_OFFSET 2 * 60 * 60 // Time offset to GMT in seconds
#define NTP_INTERVAL 120 * 1000 // Time in between server calls in milliseconds
#define NTP_ADDRESS "0.pool.ntp.org"
 
Fri3dMatrix matrix = Fri3dMatrix();
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
}
 
void loop()
{
  matrix.clear(0);
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  Serial.println(formattedTime); 
  //Draw the time on the screen
  matrix.drawCharacter(0,formattedTime[0]);
  matrix.drawCharacter(4,formattedTime[1]);
  matrix.drawCharacter(7,formattedTime[3]);
  matrix.drawCharacter(11,formattedTime[4]);
  delay(500);
}


