#ifndef RENDER_HTML
#define RENDER_HTML
#define SIZE_HTML 50000
#include "html/sourceHtml.h"

#include "sysFunc.h"

String responeBuf = "";
String listMenu = "";


// void render_inputText(String id, String label, bool newline = true){
//     responeBuf += String("<label>") + label + "</label>\n";
//     responeBuf += String("<input type=\"text\" id=\"")+id+"\""+ " onblur=\"sendData(this)\""
//     + ">";
//     if(newline){
//      responeBuf +="<br>";
//     }
// }
void render_inputText(String id, String label, String value, bool newline = true, onValueChange func = [](String val){}) {
    responeBuf += String("<label>") + label + "</label>\n";
    responeBuf += String("<input type=\"text\" id=\"") + id + "\"" + " onchange=\"sendData(this)\"" +
        " value=\"" + value + "\"" +
        ">";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_label(String id, String label, bool newline = true) {
    responeBuf += String("<label>") + label + "</label>";
    responeBuf += String("<label id=\"") + id + "\">" + "</label>\n";
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_reciveText(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    responeBuf += String("<label>") + label + "</label>\n";
    responeBuf += String("<input type=\"text\" id=\"") + id + "\"" +
        "class=\"recive\"" +
        " readonly" +
        ">";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_range(String id, String label, int min, int max, int step, bool newline = true, onValueChange func = [](String val){}) {
    responeBuf += String("<label>") + label + " </label>\n";
    responeBuf += String("<label></label>");
    responeBuf += String("<input type=\"range\" id=\"") + id + "\"" +
        "min=\'" + min + "\'" +
        "max=\'" + max + "\'" +
        "step=\'" + step + "\'" +
        "onchange=\"sendData(this)\"" +
        "oninput=\"this.previousSibling.innerHTML=this.value\"" +
        ">";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_updatetButton(bool newline = true) {
    String id = "reset";
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"location.assign('/update')\"" +
        ">UPDATE</button>";

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_resetButton(bool newline = true) {
    String id = "reset";
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sendData(this)\"" +
        ">RESET</button>";
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_formatButton(bool newline = true) {
    String id = "format";
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sendData(this)\"" +
        ">FORMAT</button>";
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_button(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sendData(this)\">" +
        label + "</button>";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);


    if (newline) {
        responeBuf += "<br>";
    }
}
void render_state(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);
    responeBuf += String("<label>") + label + "</label>" +
        "<input type=\"checkbox\" disabled=\"true\" id=\"" + id + "\">";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_switch(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);
    responeBuf += String("<label>") + label + "</label>" +
        "<input type=\"checkbox\" id=\"" + id + "\"" +
        " onclick=\"sendData(this)\"" +
        "\">";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_TimePicker(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);
    responeBuf += String("<label>") + label + "</label><br>" +
     +"<label>Giờ: </label>" +"<select class=\"hList\"></select>"
      +"<label>Phút: </label>" +"<select class=\"mList\"></select>"  
      +"<button onclick=\"sendData(this)\" class=\"timePicker\" id=\"" + id + "\">OK</button>";  
     std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);
    if (newline) {
        responeBuf += "<br>";
    }
}
void begin_menu(String name) {
    listMenu += "<li onclick=\"onMenuClick(\'" + name + "\')\"><a href=\"#\" >" + name + "</a></li>";
    responeBuf += "<div id=\"" + name + "\">";
}
void end_menu() {
    responeBuf += "</div>";
}
const char * getPage() {
    static bool gotPage = false;
    if (gotPage)
        return responeBuf.c_str();
    responeBuf += "<div id=\"menu\"><ul>";
    responeBuf += listMenu;
    responeBuf += "</ul></div>";
    responeBuf += last_part_page;
    gotPage = true;
    return responeBuf.c_str();
}
void render_init(String title) {
    responeBuf.reserve(SIZE_HTML);
    responeBuf += first_part_page + title + mid_part_page;
    begin_menu("wifi");
    render_label("time", "T.Gian: ");
    render_inputText("staid", "Tên Wifi", ConfigFileJson["staid"], true);
    render_inputText("stapass", "Mật Khẩu", ConfigFileJson["stapass"], true);
    end_menu();
    begin_menu("setting");
    render_inputText("mqttAddr", "Địa chỉ MQTT", ConfigFileJson["mqttAddr"], true);
    render_inputText("mqttPort", "Cổng MQTT", ConfigFileJson["mqttPort"], true);
    render_inputText("mqttUser", "Tên MQTT", ConfigFileJson["mqttUser"], true);
    render_inputText("mqttPass", "Mật Khẩu MQTT", ConfigFileJson["mqttPass"], true);
    render_resetButton(false);
    render_formatButton(false);
    render_updatetButton();
    end_menu();
}
#endif