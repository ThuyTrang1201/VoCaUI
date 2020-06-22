/*
  Sửa kiểu trả về (content type) cho phù hợp với javascript và css
  Chỉ cho chạy soft AP khi thiết lập
*/

//#define ETHERNET
#include "vocaui.h"
#include "mail.h"
bool isAlarmMailAdd = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  LOG("booot");
  // loadConfigFile(true); // for dev
  loadConfigFile(false); // for using
  render_init("cafe vong cat");
  begin_menu("mngMail", "test giao diện", [](String val) {
    LOG(val + " -- test giao diện" );
  });
  render_inputText("mesg", "Nội Dung",true, [](String val) {
    LOG(val + " -- Nội Dung" );
  });
  render_range("testrange", "đây là range",0,100,1,true, [](String val) {
    LOG(val + " -- đây là range" );
  });
  render_switch("testswitch", "đây là swicth",true, [](String val) {
    LOG(val + " -- đây là swicth" );
  setValue("teststate",val);
  });
  render_state("teststate", "đây là state");
  render_TimePicker("TimePicker1", "TimePicker",true, [](String val) {

    uint32_t stamp = val.toInt();
    uint32_t _hour = stamp / 60; 
      uint32_t _min  = stamp % 60; 
    LOG(val + " -- TimePicker1  "  +_hour+" "+_min);


  });
  render_TimePicker("TimePicker2", "TimePicker",true, [](String val) {
     uint32_t stamp = val.toInt();
    uint32_t _hour = stamp / 60; 
      uint32_t _min  = stamp % 60; 
    LOG(val + " -- TimePicker2  "  +_hour+" "+_min);
  });
  render_textView("tview", "Nội Dung");
  render_button("testMail", "Gửi Thử1",true, [](String val) {
    LOG("testMail");
    addMail("testMailtestMail");
  });
render_button("testMail2", "Gửi Thử2",true, [](String val) {
    LOG("testMail2");
  });
  end_menu();


    addTaskEvent(1,[](int dayW, int hour, int min){

      uint32_t stamp = String(getValue("TimePicker1")).toInt();
      uint32_t _hour = stamp / 60; 
      uint32_t _min  = stamp % 60; 
      if(_hour == hour
        && _min == min){
          LOG(String(" -- TimePicker1  chay: ")  + dayW+" "+hour+" "+min);
      }
    

    });

    addTaskEvent(2,[](int dayW, int hour, int min){
         uint32_t stamp = String(getValue("TimePicker2")).toInt();
      uint32_t _hour = stamp / 60; 
      uint32_t _min  = stamp % 60; 
      if(_hour == hour
        && _min == min){
          LOG(String(" -- TimePicker2  chay: ")  + dayW+" "+hour+" "+min);
      }
    

    });
  initVoCa();


}

uint32_t preTime = millis();
void loop() {
  // put your main code here, to run repeatedly:

  voCaHandle();


}
