
#define DEVICE D2

#include "vocaui.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  // loadConfigFile(true); // for dev, xóa các thuộc tính ko quan trọng
  loadConfigFile(false); // for using
  render_init("Tên title");
  begin_menu("Tên menu");
  render_button("onDevice", "Bật Đèn", false, [](String val) {
    digitalWrite(DEVICE, HIGH);
  });
  render_button("offDevice", "Tắt Đèn", true, [](String val) {
    digitalWrite(DEVICE, LOW);
  });

  render_reciveText("device", "Đèn đang: ", true);
  end_menu();


  begin_menu("Hẹn giờ Thiết Bị");
  // timePicker có giá trị là số phút kể từ lúc 0 giờ
  // VD: 6h30 có giá trị là 6*6+30 = 390
  render_TimePicker("onTime", "T.Gian bật đèn", true);
  render_TimePicker("offTime", "Thời gian tắt", true);
  end_menu();



  addTaskEvent(1, [](int dayW, int hour, int min) {
    int onVal = ConfigFileJson["onTime"].as<String>().toInt();
    int offVal = ConfigFileJson["offTime"].as<String>().toInt();
    int hOn = onVal / 60;
    int mOn = onVal % 60;
    int hOff = offVal / 60;
    int mOff = offVal % 60;
    if (hOn == hOff
        && mOn == mOff) {
      return;
    }
    if (hOn == hour
        && mOn == min) {
      digitalWrite(DEVICE, LOW);
    }
    if (hOff == hour
        && mOff == min) {
      digitalWrite(DEVICE, HIGH);
    }
  });
  
  initVoCa();
  pinMode(DEVICE, OUTPUT);

  // khởi tạo giá trị cho biến
  // nếu không khởi tạo, sẽ chạy giá trị đã lưu
  setValue("offDevice", "init");



}
int lastDeviceState = -1;

void loop() {
  // put your main code here, to run repeatedly:
  voCaHandle();
  if (lastDeviceState != digitalRead(DEVICE)) {
    if (!digitalRead(DEVICE))
      setValue("device", "Tắt");
    else
      setValue("device", "Bật");

    lastDeviceState = digitalRead(DEVICE);
  }


}
