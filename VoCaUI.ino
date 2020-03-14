
#include "vocaui.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  delay(5000);
  loadConfigFile();
  render_init("Điều khiển nhiệt độ");
  begin_menu("ĐK. Nhiệt độ");
  render_reciveText("curTemp", "Hiện Tại");
  render_button("onRelay", "Bật bơm",false);
  render_button("offRelay", "Tắt bơm");
  render_range("overValue","G.trị quá nhiệt",0,100,1);
  render_switch("pump", "Máy Bơm",false);
  render_switch("overTemp", "Quá Nhiệt");
  end_menu();

  Serial.begin(115200);
  initVoCa();
  sensors.begin();
  sensors.setWaitForConversion(false);


}
void loop() {
  voCaHandle();
  sensors.requestTemperatures();

  ConfigFileJson["curTemp"] = sensors.getTempCByIndex(0);
  if(ConfigFileJson["curTemp"]> float(ConfigFileJson["overValue"]))
  	ConfigFileJson["overTemp"]=true;
  else
  	ConfigFileJson["overTemp"]=false;
  if (ConfigFileJson["onRelay"] != NULL) {
    ConfigFileJson["onRelay"] = NULL;
    digitalWrite(D2, HIGH);
  }
 
  
  if (ConfigFileJson["offRelay"] != NULL) {
    ConfigFileJson["offRelay"] = NULL;
    digitalWrite(D2, LOW);
  }
   if(digitalRead(D2)== HIGH)
  	ConfigFileJson["pump"] = true;
  if(digitalRead(D2)== LOW)
  	ConfigFileJson["pump"] = false;
LOG(int(ConfigFileJson["time"]));
}
