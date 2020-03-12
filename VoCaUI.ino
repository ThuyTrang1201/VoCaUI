#include "vocaui.h"

void setup() {
	loadConfigFile();
	render_init("put your setup code here, to run once:");

	begin_menu("tesssst");
	render_reciveText("test","test");
	render_reciveText("millis","millis");
	render_range("range","chay thu",0,100,1);
	end_menu();


	begin_menu("Xem nhiệt độ");

	render_reciveText("curTemp","Nhiệt độ hiện tại");
	end_menu();


	begin_menu("Kiểm tra nút nhấn");

	render_button("button","Nhấn thử đi");
	end_menu();
	Serial.begin(115200);
	initVoCa();


}
uint32_t ledTimer = 0,counttttttt=0;
void loop() {

voCaHandle();

counttttttt++;
ConfigFileJson["test"]= counttttttt;
ConfigFileJson["millis"]= millis();


if(ConfigFileJson["button"] !=NULL){
	LOG(String("button ") + "da nhan");
	ConfigFileJson["button"] = NULL;
}
uint32_t tmpInt = ConfigFileJson["range"].as<int>();
if(millis() - ledTimer > tmpInt*10){
		 digitalWrite(LED_PIN, !digitalRead(LED_PIN));
		 ledTimer=millis();
	}
}
