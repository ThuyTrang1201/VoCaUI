#ifndef WIFI
#define WIFI
#define COUNT_CHECK_INTERNET 5
#define DEFAULT_APID "VOCAUI"
#define DEFAULT_APPASS "12345678"
#include "sysDefine.h"
#include "sysFunc.h"
#include "renderHtml.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#ifdef ETHERNET
#include <SPI.h>
#include <Ethernet2.h>
#define CLIENT EthernetClient
#else
#define CLIENT WiFiClient
#endif
CLIENT vocaClient;
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
bool gotTime = false;
uint8_t checkInternet = 0;
void initWifi() {
  server.on("/", []() {
    server.send(200, "text/html", getPage());
  });
  server.on("/script.js", []() {
    server.send(200, "text/javascript", java_script);
  });
  server.on("/style.css", []() {
    server.send(200, "text/css", menu_css);
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
    }
    saveConfigFile();


    server.send(200, "text/html", "");
  });
  server.on("/trans", []() { // server truyền dữ liệu




    String key = server.argName(0);
    String value = server.arg(0);
    uint32_t cToken = 0;
    if (key == "tokn") {
      cToken = value.toInt();
    }
    server.sendHeader("tokn", String(countSetValue));

    if (cToken == countSetValue) { // Chưa có dữ liệu mới
      server.send(504, "text/html", "");
      return;
    }
    String tmp = getRoot();

    server.send(200, "application/json", getRoot());
  });
  httpUpdater.setup(&server);
  server.begin();

  randomSeed(String(getValue("uptime")).toInt());
  uint8_t macAddr[6];
  for (uint8_t i = 0; i < 6; ++i) {
    macAddr[i] = random(0xFB, 0xff);
  }
  macAddr[0] = 0xDE;
  macAddr[1] = 0xAD;
  macAddr[2] = 0xBE;
  macAddr[3] = 0xEF;
  macAddr[4] = 0xFE;
  //  macAddr[5]=0xED;

  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP_STA);
  if (checkKey("apid")
      && checkKey("appass")) {
    WiFi.softAP(getValue("apid"), getValue("appass"));
  } else {
    WiFi.softAP(String(DEFAULT_APID) + NAME_DEVICE, DEFAULT_APPASS);
  }

#ifndef ETHERNET
  WiFi.hostname(NAME_DEVICE);
  WiFi.macAddress(macAddr);
  if (checkKey("staid")
      && checkKey("stapass")) {
    WiFi.begin(getValue("staid"), getValue("stapass"));
  }
#else
  SPI.begin();
  Ethernet.init(D4);
  Ethernet.begin(macAddr);
  Serial.print("  DHCP assigned IP ");
  Serial.println(Ethernet.localIP());
#endif

}
uint32_t getEpochTime() {
  vocaClient.stop();
  if (vocaClient.connect("www.ngoinhaiot.com", 80)) {

    vocaClient.println("GET /user/sysTime HTTP/1.1");

    vocaClient.println(String("Name: ") + getValue("user"));
    vocaClient.println(String("Password: ") + getValue("pass"));
    vocaClient.println();
    vocaClient.flush();
  }
  else {
    return 0;
  }
  delay(1000);
  String response = vocaClient.readString();
  uint32_t resLen = response.length();
  uint32_t idxCL = response.indexOf("Content-Length: ") + 16;
  uint32_t contentLength = response.substring(idxCL, response.indexOf("\n", idxCL)).toInt();
  String data = response.substring(resLen - contentLength);
  vocaClient.stop();
  return data.toInt();
}
uint32_t calcEpochTime() {

  // int32_t delta = (millis() - epochTimeTmp);
  // if(!gotTime)
  //   return 0;
  // if(delta<0){
  //   epochTime+=(4294967295-epochTimeTmp+millis())/1000;
  // }else{
  //     epochTime+=delta/1000;
  //   }
  // epochTimeTmp=millis();
  // epochTime = (millis() - epochTimeTmp)/1000;
  return epochTime +  (millis() - epochTimeTmp) / 1000 + 3600 * 7;
}
uint32_t pingTimer = millis();
void wifiHandle() {
  server.handleClient();
  if (millis() - pingTimer > 10000) {
    pingTimer = millis();
    epochTime = getEpochTime();
    if (epochTime > 0) {
      gotTime = true;
      checkInternet = 0;
      epochTimeTmp = millis();
    } else {
      if (++checkInternet > COUNT_CHECK_INTERNET)
        ESP.reset();


    }
  }

}

#endif