#ifndef SYSFUNC
#define SYSFUNC
#include <ArduinoJson.h>
#include <string>
#include "FS.h"
#include "sysDefine.h"
#include <map>
StaticJsonDocument<SIZE_CONFIG_FILE> ConfigFileJson;
volatile bool isLoadConfigFile = false;
volatile bool setValueFlag = false;

typedef void(*onValueChange)(String val);
std::map < String, onValueChange > listFunc ;
std::map < String, bool > changeFlag ;

void clearNotImportantAttr(){

  for (JsonPair kv : ConfigFileJson.as<JsonObject>()) {
    String key = String(kv.key().c_str());
    if(key == "staid"
      || key == "stapass"
      || key == "mqttAddr"
      || key == "mqttPort"
      || key == "mqttUser"
      || key == "mqttPass")
      continue;
    ConfigFileJson.remove(kv.key().c_str());
  }
}
void loadConfigFile(bool clearNotImportant ) {
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
   LOG(String("Content config file: "));
   LOG(ConfigFileJson.as<String>());
  isLoadConfigFile = true;
  cfg_file.close();
  if(clearNotImportant){
    clearNotImportantAttr();
  }
}

void saveConfigFile() {

  if (!isLoadConfigFile){
    LOG(F("load config file first !!!"));
    return;
  }

  File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
  if(!cfg_file){
    LOG(F("Can't open config file !!!"));
    return;
  }
  serializeJson(ConfigFileJson, cfg_file);
  cfg_file.close();
}
void setValue(const String key, const String value, bool init = false){
  setValueFlag = true;
  if(changeFlag[key] == true)
    return;
  // LOG(String("set: ")+ key + ": "+value);
  if(!(value == ""))
  ConfigFileJson[key]=value;

  // nếu là không phải init thì bật cờ change để handle chạy
  if(!init)
    changeFlag[key] = true;
  // LOG(String("GET: ")+ key + ": "+ConfigFileJson[key].as<char*>());
}

#endif
