#ifndef VOCAUI
#define VOCAUI
#include "sysDefine.h"
#include "sysFunc.h"
#include "wifi.h"
#include "renderHtml.h"
#include "mqttConnection.h"
#include "taskSchedule.h"
#include "mail.h"
uint32_t vocaTimer = 0;
void initVoCa() {
  initWifi();
  initMqttConnection();
}

void handleChangeValueEvent() {
  bool sendFlag = false;

  for (std::pair < String, onValueChange > func : listFunc) {
    if (changeFlag[func.first] == true) {
      func.second(getValue(func.first.c_str()));
      sendFlag = true;
      changeFlag[func.first] = false;
    }
  }

  if (sendFlag) {
    saveConfigFile();
    publicMqtt(String(getRoot()), String(getValue("mqttUser")) + "/" + NAME_DEVICE + "/tx");

  }

}
void voCaHandle() {
  if (millis() - vocaTimer > 30) {
    delay(5);
    wifiHandle();
    delay(5);
    mqttHandle();
    delay(5);
    if(gotTime)
    {
      handlerTaskSchedule();
      delay(5);
    }
    handleChangeValueEvent();
    delay(5);
    handleMail();
    delay(5);
    vocaTimer = millis();
  }

}
#endif
