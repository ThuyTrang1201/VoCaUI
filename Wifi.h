#ifndef WIFI
#define WIFI
#define DEFAULT_APID "VOCAUI"
#define DEFAULT_APPASS "12345679"
#include "sysDefine.h"
#include "sysFunc.h"
#include "renderHtml.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
void initWifi(){
  pinMode(LED_PIN, OUTPUT);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  loadConfigFile();
  if(ConfigFileJson.containsKey("apid") 
    && ConfigFileJson.containsKey("appass")){
    LOG(String("AP id: ")+ConfigFileJson["apid"].as<String>());
    LOG(String("AP pass: ")+ConfigFileJson["appass"].as<String>());
    WiFi.softAP(ConfigFileJson["apid"].as<String>(), ConfigFileJson["appass"].as<String>());
  }else{
  
    LOG(F("not found AP info, use default value"));
    WiFi.softAP(DEFAULT_APID, DEFAULT_APPASS);
  }

 if(ConfigFileJson.containsKey("staid") 
    && ConfigFileJson.containsKey("stapass")){
    LOG(String("STA id: ")+ConfigFileJson["staid"].as<String>());
    LOG(String("STA pass: ")+ConfigFileJson["stapass"].as<String>());
    WiFi.begin(ConfigFileJson["staid"].as<String>(), ConfigFileJson["stapass"].as<String>());
  }else{
    LOG(F("not found STA info, cant begin it"));
  }

 server.on("/",[](){
  server.send(200, F("text/html"), getPage());
 });
 server.on("/script.js",[](){
  server.send(200, F("text/html"), java_script);
 });
 server.on("/style.css",[](){
  server.send(200, F("text/html"), menu_css);
 });
 server.on("/receiveData",[](){
  LOG("receiving Data");
  for (int i = 0; i < server.args(); ++i)
  {
    LOG(server.argName(i)+": "+ server.arg(i));
    if(server.argName(i) == "reset")
      ESP.reset();
    ConfigFileJson[server.argName(i)]=server.arg(i);
  }
  saveConfigFile();
  server.send(200, "text/html", "");
 });
 server.on("/transData",[](){
    server.send(200, "text/html", ConfigFileJson.as<String>());
 });
  httpUpdater.setup(&server);
  server.begin();


  while (WiFi.status() != WL_CONNECTED )
  {
    delay(100);
    server.handleClient();
    LOG(F("Got IP: "));
    LOG(WiFi.localIP());
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
  digitalWrite(LED_PIN, HIGH);
}
 
void wifiHandle(){
  server.handleClient();
}
#endif