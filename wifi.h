#ifndef WIFI
#define WIFI
#define DEFAULT_APID "VOCAUI"
#define DEFAULT_APPASS "12345679"
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
NTPClient timeClient(ntpUDP, "1.asia.pool.ntp.org",3600*7);

bool gotTime = false;

void initWifi(){
  pinMode(LED_PIN, OUTPUT);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  if(ConfigFileJson.containsKey("apid") 
    && ConfigFileJson.containsKey("appass")){
    LOG(String("AP id: ")+ConfigFileJson["apid"].as<char *>());
    LOG(String("AP pass: ")+ConfigFileJson["appass"].as<char *>());
    WiFi.softAP(ConfigFileJson["apid"].as<char *>(), ConfigFileJson["appass"].as<char *>());
  }else{
  
    LOG(F("not found AP info, use default value"));
    WiFi.softAP(String(DEFAULT_APID)+NAME_DEVICE, DEFAULT_APPASS);
  }

 if(ConfigFileJson.containsKey("staid") 
    && ConfigFileJson.containsKey("stapass")){
    LOG(String("STA id: ")+ConfigFileJson["staid"].as<char *>());
    LOG(String("STA pass: ")+ConfigFileJson["stapass"].as<char *>());
    WiFi.begin(ConfigFileJson["staid"].as<char *>(), ConfigFileJson["stapass"].as<char *>());
  }else{
    LOG(F("not found STA info, can't begin it"));
  }

 server.on("/",[](){
  server.send(200, "text/html", getPage());
 });
 server.on("/script.js",[](){
  server.send(200, F("text/html"), java_script);
 });
 server.on("/style.css",[](){
  server.send(200, F("text/html"), menu_css);
 });
 server.on("/receiveData",[](){
 
  for (int i = 0; i < server.args(); ++i)
  {
    String key = server.argName(i);
    String value = server.arg(i);

    if(key == "reset")
      ESP.reset();
    if(key == "format"){
      ConfigFileJson.to<JsonObject>().clear();
      SPIFFS.format();
    }
    if(key == "all"){ // yeu cau gui du lieu
      setValue("","");
    }
    setValue(key.c_str(),value.c_str());
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
  saveConfigFile();
  server.send(200, "text/html", "");
 });
 server.on("/transData",[](){
  if(!setValueFlag){
    server.send(504, "text/html", "");
    return;
  }
    server.send(200, "text/html", ConfigFileJson.as<String>());
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    setValueFlag=false;
 });
  httpUpdater.setup(&server);
  server.begin();


  while (WiFi.status() != WL_CONNECTED )
  {
    delay(200);
    server.handleClient();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
         digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
         digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
         digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
         digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(50);
  }
      LOG(F("Got IP: "));
    LOG(WiFi.localIP());
  timeClient.begin();

  digitalWrite(LED_PIN, HIGH);
}
 
void wifiHandle(){

      server.handleClient();
      if(!gotTime)
        gotTime = timeClient.update();



ConfigFileJson["time"]=timeClient.getEpochTime();
}
#endif