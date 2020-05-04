#ifndef RENDER_HTML
#define RENDER_HTML
#define SIZE_HTML 50000
#include "html/sourceHtml.h"

#include "sysFunc.h"

String responeBuf = "";
String listMenu = "";
void render_inputText(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
      setValue(id.c_str(),"",true);
      responeBuf += emptyString
    + "<div id='"+id+"' class='inptxt'>"
    + "<label>" + label + "</label>"
    + "<input type='text'>"
    + "<button onclick=\"sdt('"+id+"',this.previousSibling.value)\">"
    + "OK</button>"
    +"</div>";
    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_textView(String id, String label, bool newline = true) {
      setValue(id.c_str(),"",true);
      responeBuf += emptyString
    + "<div id='"+id+"' class='txtvie'>"
    + "<label>" + label + "</label>"
    + "<input type='text' readonly>"
    +"</div>";

     std::pair < String, onValueChange > tmpPair(id, [](String val){});
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_range(String id, String label, int min, int max, int step, bool newline =true, onValueChange func = [](String val){}) {
     setValue(id.c_str(),"",true);
     responeBuf += emptyString
                + "<div id='"+id+"' class='rng'>"
                + "<label>" + label + "</label>"
                + "<label></label>"
                + "<input type='range'" +
                    "min='" + min + "'" +
                    "max='" + max + "'" +
                    "step='" + step + "'" +
                    "onchange=\"sdt('"+id+"',this.value); this.blur()\"" +
                    "oninput=\"this.previousSibling.innerHTML=this.value\"" +
                    ">"
                +"</div>";

       

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
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sdt('rst','')\"" +
        ">RESET</button>";
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_formatButton(bool newline = true) {

    String id = "format";
    responeBuf += String("<button type=\"button\" id=\"") + id + "\"" + " onclick=\"sdt('fmt','')\"" +
        ">FORMAT</button>";
    if (newline) {
        responeBuf += "<br>";
    }
}
void render_button(String id, String label, onValueChange func = [](String val){}, bool newline = true) {
    setValue(id.c_str(),"",true);
    responeBuf += emptyString
    + "<div id='"+id+"' class='sglbtn'>"
    + "<button onclick=\"sdt('"+id+"','"+label+"')\">"
    + label
    + "</button>"
    +"</div>";
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
    responeBuf += emptyString
    + "<div id='"+id+"' class='swch'>"
    + "<label>" + label + "</label>"
    + "<input id = '_"+id+"' type='checkbox' onclick=\"sdt('"+id+"',this.checked.toString())\">"
    + "<label for='_"+id+"'></label>"
    +"</div>";

    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}
void render_state(String id, String label, bool newline = true) {
    setValue(id.c_str(),"",true);
    responeBuf += emptyString
    + "<div id='"+id+"' class='state'>"
    + "<label>" + label + "</label>"
    + "<input  id = '_"+id+"' type='checkbox' disabled='disabled'>"
    + "<label for='_"+id+"'></label>"
    +"</div>";

    std::pair < String, onValueChange > tmpPair(id, [](String val){});
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);

    if (newline) {
        responeBuf += "<br>";
    }
}

void render_TimePicker(String id, String label, bool newline = true, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);

      responeBuf += emptyString
    + "<div id='"+id+"' class='tmpk'>"
    + "<label>" + label + "</label><br>"
    + "<label>Giờ: </label><select class='hLst'></select>"
    + "<label>Phút: </label><select class='mLst'></select>"
    +"<button onclick=\"var p=this.parentElement.children; var m = p[5];var h = p[3]; var v = parseInt(m.value) + h.value * 60; sdt('"+id+"',v)\">OK</button>"
    +"</div>";


     std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);
    if (newline) {
        responeBuf += "<br>";
    }
}
void begin_menu(String id, String name, onValueChange func = [](String val){}) {
    setValue(id.c_str(),"",true);
    listMenu += "<li onclick=\"oMnClk('" + id + "','')\"><a href=\"#\" >" + name + "</a></li>";
    responeBuf += "<div class='mnu' id=\"" + id + "\" style='display: none'>"
    + "<label>" + name + "</label><br>";
    std::pair < String, onValueChange > tmpPair(id, func);
    std::pair < String, bool > tmpPair2(id, false);
    changeFlag.insert(tmpPair2);
    listFunc.insert(tmpPair);
}
void end_menu() {
    responeBuf += "</div>";
}
const char * getPage() {
    static bool gotPage = false;
    if (gotPage)
        return responeBuf.c_str();
    responeBuf += "<div class='lmnu' style='display: none' onclick='hidelmnu();'><ul>";
    responeBuf += listMenu;
    responeBuf += "</ul></div>";
    responeBuf += last_part_page;
    gotPage = true;
    return responeBuf.c_str();
}
void render_init(String title) {
    responeBuf.reserve(SIZE_HTML);
    responeBuf += first_part_page + title + mid_part_page;
    begin_menu("wifi","wifi");
    render_textView("time", "T.Gian: ");
    render_inputText("staid", "Tên Wifi", true);
    render_inputText("stapass", "Mật Khẩu", true);
    end_menu();
    begin_menu("setting","setting");
    render_inputText("mqttAddr", "Địa chỉ MQTT", true);
    render_inputText("mqttPort", "Cổng MQTT", true);
    render_inputText("mqttUser", "Tên MQTT", true);
    render_inputText("mqttPass", "Mật Khẩu MQTT", true);
    render_resetButton(false);
    render_formatButton(false);
    render_updatetButton();
    end_menu();
}
#endif