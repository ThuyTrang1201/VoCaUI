#ifndef WIFI
#define WIFI
#define DEFAULT_APID "VOCAUI"
#define DEFAULT_APPASS "12345678"
#include "sysDefine.h"
#include "sysFunc.h"
#include "renderHtml.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
NTPClient timeClient(ntpUDP, "1.asia.pool.ntp.org", 3600 * 7);

bool gotTime = false;
void initWifi() {
  pinMode(LED_PIN, OUTPUT);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  if (checkKey("apid")
      && checkKey("appass")) {
    LOG(String("AP id: ") + getValue("apid"));
    LOG(String("AP pass: ") + getValue("appass"));
    WiFi.softAP(getValue("apid"), getValue("appass"));
  } else {

    LOG(F("not found AP info, use default value"));
    WiFi.softAP(String(DEFAULT_APID) + NAME_DEVICE, DEFAULT_APPASS);
  }

  if (checkKey("staid")
      && checkKey("stapass")) {
    LOG(String("STA id: ") + getValue("staid"));
    LOG(String("STA pass: ") + getValue("stapass"));
    WiFi.begin(getValue("staid"), getValue("stapass"));
  } else {
    LOG(F("not found STA info, can't begin it"));
  }

  server.on("/", []() {
    server.send(200, "text/html", getPage());
  });
  server.on("/script.js", []() {
    server.send(200, "text/html", java_script);
  });
  server.on("/style.css", []() {
    server.send(200, "text/html", menu_css);
  });
  server.on("/recv", []() {

    for (int i = 0; i < server.args(); ++i)
    {
      String key = server.argName(i);
      String value = server.arg(i);

      if (key == "rst")
        ESP.reset();
      if (key == "fmt") {
        clearRoot();
        SPIFFS.format();
      }
      if (key == "all") { // yeu cau gui du lieu
        setValue("", "");
      }
      setValue(key.c_str(), value.c_str());
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      LOG(key + ": " + value + " --wifi");
    }
    saveConfigFile();
    server.send(200, "text/html", "");
  });
  server.on("/trans", []() {

    if (setValueFlag == false) { // Chưa có dữ liệu mới
      server.send(504, "text/html", "");
      return;
    }
    String tmp = getRoot();
    server.send(200, "application/json", getRoot());
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    setValueFlag = false;
  });
  httpUpdater.setup(&server);
  server.begin();


  while (WiFi.status() != WL_CONNECTED && millis()<20000)
  {
    server.handleClient();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  }

  LOG(F("Got IP: "));
  LOG(WiFi.localIP());
  timeClient.begin();

  digitalWrite(LED_PIN, HIGH);
}

void wifiHandle() {
  server.handleClient();
  if (!gotTime) {
    gotTime = timeClient.update();
  }
}
#endif
