#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "Config.h"

void setup()
{
  Serial.begin(115200);
  pinMode(SHUTTER_PIN, INPUT_PULLUP);
  // Connect to Camera
  WiFi.mode(WIFI_STA);
  bool connected = false;
  do {
    WiFi.begin(CAMERA_SSID, CAMERA_PASS);
    Serial.print("WiFi is connecting");
    uint16_t count = 0;
    while (count < 10)
    {
      if (WiFi.status() != WL_CONNECTED)
      {
        Serial.print(".");
        ++count;
        delay(1000);
      }
      else
      {
        Serial.print("!");
        connected = true;
        break;
      }
    }
    Serial.println();
  } while (!connected);
  Serial.println("WiFi is connected!");

  Serial.println("Switch mode: ");
  HTTPClient http;
  http.begin("http://192.168.0.10/switch_cammode.cgi?mode=shutter");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK);
  http.end();
}


void loop()
{
  //Serial.print("Button: ");
  //Serial.println(digitalRead(SHUTTER_PIN));
  if (digitalRead(SHUTTER_PIN) == LOW)
  {
    Serial.print("Take shot, ");
    {
      HTTPClient http;
      http.begin("http://192.168.0.10/exec_shutter.cgi?com=1st2ndpush");
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK);
      http.end();
    }
    //delay(300);
    Serial.println("release");
    {
      HTTPClient http;
      http.begin("http://192.168.0.10/exec_shutter.cgi?com=2nd1strelease");
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK);
      http.end();
    }
    //delay(300);
  }
}
