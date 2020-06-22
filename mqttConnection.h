#ifndef MQTT_CONNECTION
#define MQTT_CONNECTION

#include <PubSubClient.h>
#include "html/sourceHtml.h"
#include "sysFunc.h"
CLIENT cMQTT;
PubSubClient mqttClient(cMQTT);
std::map < String, String > inComeData;
void json2MapInComeData(String json);
bool isPubDasboard = false;
void publicMqtt(String data, String topic, bool retain=false) {
  mqttClient.beginPublish(topic.c_str(), data.length(), retain);
  for(uint32_t i=0;i<data.length();i++)
    mqttClient.print(data[i]);
    mqttClient.endPublish();
}
void initMqttConnection() {
  // cMQTT.setTimeout(500);
  mqttClient.setServer(getValue("mqttAddr"), String(getValue("mqttPort")).toInt());
  mqttClient.setCallback([](char* topic, byte * payload, unsigned int length) {
    String tmp;
    for (int i = 0; i < length; i++) {
      tmp += (char)payload[i];
    }
    json2MapInComeData(tmp);
    setValue(inComeData["id"], inComeData["value"]);
    if (inComeData["id"] == "all") {
      publicMqtt(String(getRoot()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "/tx",false);

    } else if (inComeData["id"] == "ui") {
      publicMqtt(String(getPage()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "/dashboard",true);


    }

  });
  String clientId = NAME_DEVICE;
  clientId += String(random(0xffff), HEX);
  mqttClient.connect(clientId.c_str(), getValue("mqttUser"), getValue("mqttPass"));
  mqttClient.subscribe((String(getValue("mqttUser")) + "/" + NAME_DEVICE + "/rx/#").c_str(), 1);


  isPubDasboard = false;


}

void mqttHandle() {
  if (!mqttClient.connected()) {
    initMqttConnection();
    return;
  }
  if (!isPubDasboard) {
    publicMqtt(String(getPage()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "/dashboard",true);
    isPubDasboard = true;
  }

  mqttClient.loop();
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
