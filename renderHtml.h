#include "html/sourceHtml.h"
String responeBuf="";
String listMenu="";

void render_inputText(String id, String label, bool newline = true){
    responeBuf += String("<label>") + label + "</label>\n";
    responeBuf += String("<input type=\"text\" id=\"")+id+"\""+ " onblur=\"sendData('" + id+"')\""
    + ">";
    if(newline){
    	responeBuf +="<br>";
    }
}
void render_inputText(String id, String label, String value, bool newline = true){
    responeBuf += String("<label>") + label + "</label>\n";
    responeBuf += String("<input type=\"text\" id=\"")+id+"\""+ " onblur=\"sendData('" + id+"')\""
    + " value=\""+value+"\""
    + ">";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_reciveText(String id, String label, bool newline = true){
    responeBuf += String("<label>") + label + "</label>\n";
    responeBuf += String("<input type=\"text\" id=\"")+id+"\""
    + "class=\"recive\""
    + " readonly"
    + ">";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_range(String id, String label, int min, int max, int step, bool newline = true){
    responeBuf += String("<label>") + label + " </label>\n";
    responeBuf += String("<label id=\"")+id+"vl\"></label>\n";
    responeBuf += String("<input type=\"range\" id=\"")+id+"\""
    + "min=\'" + min +"\'"
    + "max=\'" + max +"\'"
    + "step=\'" + step +"\'"
    + "onchange=\"sendData('" + id+"')\""
    + "oninput=\"" + id+"vl.innerHTML=this.value\""
    + ">";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_resetButton(bool newline = true){
	String id = "reset";
    responeBuf += String("<button type=\"button\" id=\"")+id+"\""+ " onclick=\"sendData('" + id+"')\""
    + ">RESET</button>";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_formatButton(bool newline = true){
	String id = "format";
    responeBuf += String("<button type=\"button\" id=\"")+id+"\""+ " onclick=\"sendData('" + id+"')\""
    + ">FORMAT</button>";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_button(String id, String label, bool newline = true){
	ConfigFileJson[id] = NULL;
    responeBuf += String("<button type=\"button\" id=\"")+id+"\""+ " onclick=\"sendData('" + id+"')\">"
    +label +"</button>";
     if(newline){
    	responeBuf +="<br>";
    }
}
void render_switch(String id, String label, bool newline = true){
	ConfigFileJson[id] = NULL;
    responeBuf += String("<label>")+label+"</label>"
+"<input class=\"recive\" type=\"checkbox\" id=\"" + id +"\">";
 if(newline){
    	responeBuf +="<br>";
    }
}
void begin_menu(String name){
	listMenu+="<li onclick=\"onMenuClick(\'" + name + "\')\"><a href=\"#\" >" + name + "</a></li>";
	responeBuf+="<div id=\""+name+"\">";
}
void end_menu(){
	responeBuf+="</div>";
}
String getPage(){
	static bool gotPage = false;
	if(gotPage)
		return responeBuf;
	responeBuf += "<div id=\"menu\"><ul>";
		responeBuf+=listMenu;
	responeBuf += "</ul></div>";
	responeBuf += "<div id=\"mask\"></div>";
	responeBuf += last_part_page;
	gotPage = true;
	return responeBuf;
}
void render_init(String title){
	responeBuf+=first_part_page+title+mid_part_page;
	begin_menu("wifi");
	render_inputText("staid","Tên Wifi",ConfigFileJson["staid"],true);
	render_inputText("stapass","Mật Khẩu",ConfigFileJson["stapass"],true);
	end_menu();
	begin_menu("setting");
	render_resetButton(false);
	render_formatButton(false);
	end_menu();
}
