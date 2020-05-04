

#include "vocaui.h"
#include <Ticker.h>
#include <Adafruit_NeoPixel.h>
// #include "RTClib.h"
Adafruit_NeoPixel pixels(60, D3, NEO_GRB + NEO_KHZ800);
int BRIGHTNESS = 100;
uint32_t curSecondPoint = 0;
Ticker fadeSecond;


uint32_t lastSeconds = 61;
uint32_t lastHours = 61;
uint32_t lastMinute = 61;


uint32_t seconds;
uint32_t hours;
uint32_t minute;
bool manTime = false;
// RTC_DS1307 rtc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // loadConfigFile(true); // for dev
  loadConfigFile(false); // for using
  render_init("Điều Khiển Led Full");
  begin_menu("menu1", "Hiệu Ứng",[](String val){
    manTime=false;
  });
 render_button("hu1","Hiệu Ứng 1",[](String val){
        for (int i = pixels.numPixels(); i >= 0; i--) {
          pixels.setPixelColor(i, 255, 0, 0);
          pixels.show();
          delay(20);
        }
        pixels.clear();
        for (int i = pixels.numPixels(); i >= 0; i--) {
          pixels.setPixelColor(i, 0, 255, 0);
          pixels.show();
          delay(20);
        }
        pixels.clear();
        for (int i = pixels.numPixels(); i >= 0; i--) {
          pixels.setPixelColor(i, 0, 0, 255);
          pixels.show();
          delay(20);
        }
        pixels.clear();
  });
  render_button("hu2","Hiệu Ứng 2",[](String val){
    for (int i = 0; i < 50; ++i)
    {
     for (int i = pixels.numPixels(); i >= 0; i--) {
    pixels.setPixelColor(i,random(255), random(255), random(255));
   
  }
   pixels.show();
   delay(100);
    }
         

           pixels.clear();
  });
  render_button("hu3","Hiệu Ứng 3",[](String val){
        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, 255, -1, -1);
          pixels.show();
          delay(20);
        }
        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, -1, 255, -1);
          pixels.show();
          delay(20);
        }
        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, -1, -1, 255);
          pixels.show();
          delay(20);
        }

        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, 0, -1, -1);
          pixels.show();
          delay(20);
        }
        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, -1, 0, -1);
          pixels.show();
          delay(20);
        }
        for (int i = pixels.numPixels(); i >= 0; i--) {
          setColor(i, -1, -1, 0);
          pixels.show();
          delay(20);
        }
        pixels.clear();
  });
  

  end_menu();
 begin_menu("menu2", "developer",[](String val){
  manTime=true;
  });  

 render_inputText("gio","gio",[](String val){

  });

 render_inputText("phut","phut",[](String val){

  });
 render_inputText("giay","giay",[](String val){

  });
  end_menu();
  initVoCa();

  //====

  pixels.begin();
    for (int i = pixels.numPixels(); i >= 0; i--) {
    pixels.setPixelColor(i, 255, 0, 0);
    pixels.show();
    delay(20);
  }
  pixels.clear();
  for (int i = pixels.numPixels(); i >= 0; i--) {
    pixels.setPixelColor(i, 0, 255, 0);
    pixels.show();
    delay(20);
  }
  pixels.clear();
  for (int i = pixels.numPixels(); i >= 0; i--) {
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
    delay(20);
  }
  pixels.clear();
pixels.show();
  // rtc.begin();

  while(millis()<30000){
    for (int i = pixels.numPixels(); i >= 0; i--) {
    pixels.setPixelColor(i,random(255), random(255), random(255));
   
  }
   pixels.show();
      voCaHandle();

  delay(50);
  }
}

uint32_t count=0;
uint32_t sssss=millis();

void loop() {
  // put your main code here, to run repeatedly:

  voCaHandle();
// DateTime now = rtc.now();
  if(!manTime){
      // seconds = now.second();
      // hours = now.hour();
      // minute = now.minute();
      seconds = timeClient.getSeconds();
      hours = timeClient.getHours();
      minute = timeClient.getMinutes();
  }else{
    seconds = String(getValue("giay")).toInt();
    hours = String(getValue("gio")).toInt();
    minute = String(getValue("phut")).toInt();


  }



    if (lastSeconds != seconds) {
      curSecondPoint = pixels.numPixels() - seconds - 1;
      fadeSecond.attach_ms(75, fadeSecondFunc);

    //   setColor(curSecondPoint, BRIGHTNESS, -1, -1);
    // for (int i = pixels.numPixels(); i >= 0; i--) {
    //   if(i!=curSecondPoint)
    //       setColor(i, 0, -1, -1);
    // }
    //  pixels.show();

       uint32_t curMinPoint = pixels.numPixels() - minute - 1;
      handleMinutePoint(curMinPoint);
 

      int32_t curHoursPoint = pixels.numPixels() - 1 - hours * 5 - minute / 12;
      handleHoursPoint(curHoursPoint);
      pixels.show();
      lastSeconds = seconds;
    }

}
void handleMinutePoint(int32_t curPoint){
      setColor(curPoint, -1, BRIGHTNESS, -1);
      for (int i = pixels.numPixels(); i >= 0; i--) {
      if(i!=curPoint)
          setColor(i, -1, 0, -1);
    }
     pixels.show();
}
void handleHoursPoint(int32_t curPoint){
      setColor(curPoint, -1, -1, BRIGHTNESS);
      for (int i = pixels.numPixels(); i >= 0; i--) {
      if(i!=curPoint)
          setColor(i, -1, -1, 0);
    }
     pixels.show();
}
void fadeSecondFunc() {
  static int step = 0;
  static uint32_t preSecondPoint = pixels.numPixels();
  setColor(curSecondPoint, pixels.gamma8(BRIGHTNESS * step / 13), -1, -1);
  if(preSecondPoint<pixels.numPixels())
    setColor(preSecondPoint, pixels.gamma8(BRIGHTNESS * (13 - step) / 13), -1, -1);
  pixels.show();
  step++;
  if (step == 13) {
    step = 0;
    preSecondPoint = curSecondPoint;
    for (int i = pixels.numPixels(); i >= 0; i--) {
      if(i!=curSecondPoint)
          setColor(i, 0, -1, -1);
    }
     pixels.show();
    fadeSecond.detach();
  }

}

void setColor(uint32_t pixel, int16_t r, int16_t g, int16_t b) {
  uint8_t red = (pixels.getPixelColor(pixel) >> 16);
  uint8_t green = (pixels.getPixelColor(pixel) >> 8);
  uint8_t blue = (pixels.getPixelColor(pixel));
  if (r >= 0)
    red = r;
  if (g >= 0)
    green = g;
  if (b >= 0)
    blue = b;
  pixels.setPixelColor(pixel, red, green, blue);
}
