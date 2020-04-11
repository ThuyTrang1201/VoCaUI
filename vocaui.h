#ifndef VOCAUI
#define VOCAUI
#include "sysDefine.h"
#include "sysFunc.h"
#include "wifi.h"
#include "renderHtml.h"
#include "mqttConnection.h"
#include "taskSchedule.h"
uint32_t vocaTimer = 0;

void initVoCa(){
	initWifi();
	initMqttConnection();
}
void handleChangeValueEvent(){
	bool sendFlag = false;
		
		for (std::pair < String, onValueChange > func : listFunc) {	
			if(changeFlag[func.first] == true){
				func.second(ConfigFileJson[func.first]);
				sendFlag = true;
				changeFlag[func.first] = false;
			}
		}

		if(sendFlag){
			publicMqtt(String(ConfigFileJson.as<String>()),String(ConfigFileJson["mqttUser"].as<String>()) +"/"+NAME_DEVICE +"/tx");

		}
		
}
void voCaHandle(){
	if(millis() - vocaTimer > 10){
		mqttHandle();
		wifiHandle();
		handlerTaskSchedule();
		handleChangeValueEvent();
		vocaTimer=millis();
	}

}
#endif
