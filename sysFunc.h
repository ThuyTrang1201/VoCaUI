#ifndef SYSFUNC
#define SYSFUNC
#include <ArduinoJson.h>
#include "FS.h"
#include "sysDefine.h"

StaticJsonDocument<SIZE_CONFIG_FILE> ConfigFileJson;
bool isLoadConfigFile = false;
void loadConfigFile() {
  if(isLoadConfigFile){
    LOG(F("Config file is loaded"));
    return;
  }
  if(!SPIFFS.begin()){
    LOG(F("Can't begin SPIFFS !!!"));
    return;
  }

  File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
 
  DeserializationError err = deserializeJson(ConfigFileJson, cfg_file.readString());
   if(err){
    LOG(F("ConfigFileJson error, reinitial empty file"));
    ConfigFileJson.to<JsonObject>();
   }
   LOG(String("Content config file: ") + ConfigFileJson.as<String>());
  isLoadConfigFile = true;
}
void saveConfigFile() {
  if (!isLoadConfigFile){
    LOG(F("load config file first !!!"));
    return;
  }
  if(!SPIFFS.begin()){
    LOG(F("Can't begin SPIFFS !!!"));
    return;
  }
  File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
  if(!cfg_file){
    LOG(F("Can't open config file !!!"));
  }
  serializeJson(ConfigFileJson, cfg_file);
  cfg_file.close();
}

#endif
