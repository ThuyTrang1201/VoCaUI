#ifndef MAIL
#define MAIL
#include "sysDefine.h"
#include "sysFunc.h"
CLIENT cMail;
uint32_t mailTimer = millis();

bool sendMail(String Content, String desMail
              , String name, String psk, String token = "") {
  if (desMail == ""
      || Content == "")
    return false;



  cMail.stop();
  if (cMail.connect("www.ngoinhaiot.com", 80)) {

    cMail.println("GET /mailManager/index.php HTTP/1.1");
    cMail.println(String("Submit: true"));
    cMail.println(String("Name: ") + name);
    cMail.println(String("Password: ") + psk);
    cMail.println(String("Tomail: ") + desMail);
    cMail.println(String("Content: ") + Content);
    cMail.println(String("token: ") + token);
    cMail.println("Connection: close");
    cMail.println();
    cMail.flush();
  }
  else {

  }
  delay(1000);
  String tmp = cMail.readString();
  cMail.stop();
  if (tmp.indexOf("SENT") > 0) {
    return true;
  }

  else {
    return false;

  }
}

void handleMail() {
  static uint32_t deltaTime = 5000;
  if (millis() - mailTimer > deltaTime) {
    mailTimer = millis();
    deltaTime = 5000;
    if (String(getValue("mailCnt")) != "null") {
      String tmp = getValue("mailCnt");
      if (tmp.startsWith("#"))
        tmp = tmp.substring(1);
      if (tmp.indexOf("#") < 0) {
        setValue("mailCnt", "null");
        return;
      }
      String aPart = tmp.substring(0, tmp.indexOf("#"));
      if (sendMail(aPart,
                   getValue("desMail"),
                   getValue("user"),
                   getValue("pass"),
                   getValue("tknMail"))
          || aPart.length() == 0
         )
      {
        String tmpVal = tmp.substring(aPart.length() + 1).c_str();
        if (tmpVal.length() == 0)
          tmpVal = "null";
        setValue("mailCnt", tmpVal);

        // nếu gửi thành công thì phải đợi thêm 1 phút
        deltaTime = 60000;
      }
    }

  }

}
void addMail(String Content) {
  String tmp = String(getValue("mailCnt"));
  //  LOG(Content);
  if (tmp == "null") // is empty
    tmp = "";
  tmp += Content + "#";
  setValue("mailCnt", tmp);
}

#endif
