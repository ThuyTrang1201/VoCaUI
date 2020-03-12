#include "sysDefine.h"
#include "sysFunc.h"
#include "wifi.h"
uint32_t vocaTimer = 0;
void initVoCa(){
	initWifi();
}
void voCaHandle(){
	if(millis() - vocaTimer > 50){
			wifiHandle();
			vocaTimer=millis();
	}

}