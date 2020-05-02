#ifndef SYSFUNC
#define SYSFUNC

#include "FS.h"
#include "sysDefine.h"
#include <map>

volatile bool isLoadConfigFile = false;
volatile bool setValueFlag = false;

typedef void(*onValueChange)(String val);
std::map < String, onValueChange > listFunc;
std::map < String, bool > changeFlag ;
std::map < String, String > ConfigContent;

char bufContent[10000];
void setValue(String key, String value, bool init = false);
const char* getRoot();
void config2Json() {
  String ret = "{";
  for (std::pair < String, String > e : ConfigContent) {
    String k = e.first;
    String v = e.second;
    String s = "\"" + k + "\":\"" + v + "\"";
    ret += s + ",";
  }
  ret[ret.length() - 1] = '}';
  return ret.toCharArray(bufContent,ret.length()+1);
}
void json2Map(String json) {
  ConfigContent.clear();
  if (json.startsWith("{")
      && json.endsWith("}")) {
    json.replace("{", "");
    json.replace("}", "");
    while (json.length() > 0) {
      String key;
      String value;
      int32_t idx = json.lastIndexOf(",");
      String sub ;
      if (idx >= 0) {
        sub = json.substring(idx + 1, json.length());
        json.remove(idx, json.length());


      } else {
        sub = json;

        json.remove(0, json.length());
      }
      sub.replace("\"", "");
      key = sub.substring(0, sub.indexOf(":"));
      value = sub.substring(sub.indexOf(":") + 1, sub.length());
      setValue(key,value,true);
    }
  }
  config2Json();
}
void clearNotImportantAttr(){
  for (std::pair < String, String > e : ConfigContent) { 
    String key = e.first;
    if(key == "staid"
      || key == "stapass"
      || key == "mqttAddr"
      || key == "mqttPort"
      || key == "mqttUser"
      || key == "mqttPass")
      continue;
    ConfigContent.erase(key);
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
  String tmp = cfg_file.readString();
    json2Map(tmp);

   LOG(String("Content config file: "));
   LOG(tmp);
   LOG(String("Content root file: "));
   LOG(getRoot());
  isLoadConfigFile = true;
  cfg_file.close();
  if(clearNotImportant){
    clearNotImportantAttr();
  }
}

void saveConfigFile() {
  config2Json();
   LOG(F("saveConfigFile: "));
   LOG(bufContent);
  if (!isLoadConfigFile){
    LOG(F("load config file first !!!"));
    return;
  }

  File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
  if(!cfg_file){
    LOG(F("Can't open config file !!!"));
    return;
  }
  cfg_file.print(String(bufContent));
  cfg_file.close();
}

void setValue(String key, String value, bool init) {
   setValueFlag = true;
   if(changeFlag[key] == true)
    return;
  if(!(value == "")){
    ConfigContent[key] = value;
    config2Json();
  }

    // if(!init) // nếu không phải là khởi tạo
    //           thì bật cờ change lên cho handle chạy
    //   changeFlag[key] = true;
    // else  
    //   changeFlag[key] = false;
    // Viết gọn là thế này
      changeFlag[key] = !init;
}
const char* getValue(String key) {
  return ConfigContent[key].c_str();
}
const char* getRoot(){
 return bufContent;
}
void clearRoot() {
  ConfigContent.clear();
}
bool checkKey(const char* key) {

  if (ConfigContent.find(key) != ConfigContent.end())
  {
    return true;
  }
  return false;
}

#endif
