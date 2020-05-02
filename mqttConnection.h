#ifndef MQTT_CONNECTION
#define MQTT_CONNECTION

#include <ArduinoMqttClient.h>
#include "html/sourceHtml.h"
#include "sysFunc.h"
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
// StaticJsonDocument<SIZE_CONFIG_FILE> inComeData;
void publicMqtt(String data, String topic){
	mqttClient.beginMessage(topic, data.length(), true, 1, false);
    mqttClient.print(data);
    mqttClient.endMessage();
}
void initMqttConnection(){

// 	mqttClient.setUsernamePassword(getValue("mqttUser"), getValue("mqttPass"));
// 	mqttClient.connect(getValue("mqttAddr"), String(getValue("mqttPort")).toInt());
  
 


//     mqttClient.onMessage([](int messageSize){
// inComeData.to<JsonObject>();
//   DeserializationError err;
//   while (mqttClient.available()) {
//     err = deserializeJson(inComeData, mqttClient);

//   }

//    if(!err){
//    	setValue(inComeData["id"].as<char *>(),inComeData["value"].as<char *>());
//    	if(inComeData["id"].as<String>() == "all"){
//    		publicMqtt(String(getRoot()),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/tx");
//    	}else if (inComeData["id"].as<String>() == "ui"){
//       publicMqtt(getPage(),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/dashboard");

//     }
//    }

//   });


//   mqttClient.subscribe(String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/rx/#", 1);
  
//   publicMqtt(getPage(),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/dashboard");
}
void mqttHandle(){
  // if(!mqttClient.connected()){
  //   initMqttConnection();
  //   }

  //   mqttClient.poll();
}


#endif
