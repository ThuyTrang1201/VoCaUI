#ifndef MQTT_CONNECTION
#define MQTT_CONNECTION

#include <ArduinoMqttClient.h>
#include "html/sourceHtml.h"
#include "sysFunc.h"
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
StaticJsonDocument<SIZE_CONFIG_FILE> inComeData;
void publicMqtt(String data, String topic){
	mqttClient.beginMessage(topic, data.length(), true, 1, false);
    mqttClient.print(data);
    mqttClient.endMessage();
}
void initMqttConnection(){

	mqttClient.setUsernamePassword(ConfigFileJson["mqttUser"].as<char *>(), ConfigFileJson["mqttPass"].as<char *>());
	mqttClient.connect(ConfigFileJson["mqttAddr"].as<char *>(), String(ConfigFileJson["mqttPort"].as<char *>()).toInt());
  
 


    mqttClient.onMessage([](int messageSize){
inComeData.to<JsonObject>();
  DeserializationError err;
  while (mqttClient.available()) {
    err = deserializeJson(inComeData, mqttClient);

  }

   if(!err){
   	setValue(inComeData["id"].as<char *>(),inComeData["value"].as<char *>());
   	if(inComeData["id"].as<String>() == "all"){
   		publicMqtt(String(ConfigFileJson.as<String>()),String(ConfigFileJson["mqttUser"].as<char *>()) +"/"+NAME_DEVICE+ "/tx");
   	}else if (inComeData["id"].as<String>() == "ui"){
      publicMqtt(getPage(),String(ConfigFileJson["mqttUser"].as<char *>()) +"/"+NAME_DEVICE+ "/dashboard");

    }
   }

  });


  mqttClient.subscribe(String(ConfigFileJson["mqttUser"].as<char *>()) +"/"+NAME_DEVICE+ "/rx/#", 1);
  
  publicMqtt(getPage(),String(ConfigFileJson["mqttUser"].as<char *>()) +"/"+NAME_DEVICE+ "/dashboard");
}
void mqttHandle(){
  if(!mqttClient.connected()){
    initMqttConnection();
    }

    mqttClient.poll();
}


#endif
