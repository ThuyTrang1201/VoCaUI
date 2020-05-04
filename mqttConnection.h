#ifndef MQTT_CONNECTION
#define MQTT_CONNECTION

#include <ArduinoMqttClient.h>
#include "html/sourceHtml.h"
#include "sysFunc.h"
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
std::map < String, String > inComeData;
void json2MapInComeData(String json);
void publicMqtt(String data, String topic){
	mqttClient.beginMessage(topic, data.length(), true, 1, false);
    mqttClient.print(data);
    mqttClient.endMessage();
}
void initMqttConnection(){

	mqttClient.setUsernamePassword(getValue("mqttUser"), getValue("mqttPass"));
	mqttClient.connect(getValue("mqttAddr"), String(getValue("mqttPort")).toInt());
  
 mqttClient.setConnectionTimeout(3000);


    mqttClient.onMessage([](int messageSize){
    	String tmp;
  while (mqttClient.available()) {
  	tmp+=mqttClient.readString();


  }
  	json2MapInComeData(tmp);

   	setValue(inComeData["id"],inComeData["value"]);
   	if(inComeData["id"]== "all"){
   		publicMqtt(String(getRoot()),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/tx");
   	}else if (inComeData["id"] == "ui"){
      publicMqtt(getPage(),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/dashboard");

    }


  });


  mqttClient.subscribe(String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/rx/#", 1);
  
  publicMqtt(getPage(),String(getValue("mqttUser")) +"/"+NAME_DEVICE+ "/dashboard");
}
void mqttHandle(){
  if(!mqttClient.connected()){
    initMqttConnection();
    }

    mqttClient.poll();
}
void json2MapInComeData(String json) {
  inComeData.clear();
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
      inComeData[key] = value;
    }
  }
}

#endif
