#define QUOTE(...) #__VA_ARGS__
char * first_part_page = QUOTE(
	
<meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1">
<html>
<head>
<link rel='stylesheet' href='style.css'>
<title>
);
char * mid_part_page = QUOTE(
</title>
</head>
<body>
<div id="menu-button" onclick="showMenu()">MENU</div>
);
char * last_part_page = QUOTE(
<script src="script.js"></script>
</body>
</html>
);


char * java_script = QUOTE(function sendData(id){var formData=new FormData();var x=document.getElementById(id);formData.append(id,x.value);var xhr=new XMLHttpRequest();xhr.open('POST','/receiveData',!0);xhr.send(formData)}
function showMenu(){var divs=document.getElementsByTagName('div');for(var i=0;i<divs.length;i++){if(divs[i].id=="menu")
divs[i].style.display="block"}}
function onMenuClick(name){var divs=document.getElementsByTagName('div');for(var i=0;i<divs.length;i++){if(divs[i].id!=name&&divs[i].id!="menu-button"&&divs[i].id!="wifi")
divs[i].style.display="none";else divs[i].style.display="block"}}
function ajaxData(){var xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){if(this.readyState==4&&this.status==200){var resText=xhttp.responseText;var obj=JSON.parse(resText);console.log(resText);var reciveClass=document.getElementsByClassName("recive");var i;for(i=0;i<reciveClass.length;i++){reciveClass[i].value=obj[reciveClass[i].id]}
ajaxData()}};xhttp.open('GET','/transData',!0);xhttp.send()}
function onloadDone(){onMenuClick("");ajaxData()}
window.onload=onloadDone);


char* menu_css =QUOTE(*{margin:0;padding:0}body{background:#7a90ff;background:-moz-linear-gradient(-45deg,#7a90ff 0%,#ffffff 100%);background:-webkit-linear-gradient(-45deg,#7a90ff 0%,#ffffff 100%);background:linear-gradient(135deg,#7a90ff 0%,#ffffff 100%)}div{outline:3px solid #1c6ea4;outline-offset:2px;padding:15px 15px;margin:10px;margin-top:20px}label{font-family:Tahoma,Geneva,sans-serif;font-size:19px;letter-spacing:0;word-spacing:2px;color:#000;font-weight:700;text-decoration:none;font-style:normal;font-variant:normal;text-transform:uppercase;padding:10px;text-shadow:1px 1px 5px rgba(0,0,0,.2)}input[type="text"]{width:100%;padding:12px 20px;margin:8px 0;display:inline-block;border:1px solid #ccc;border-radius:4px;font-size:18px;box-sizing:border-box}button[type="button"]{width:auto;background-color:#4caf50;color:white;padding:14px 20px;margin:8px 0;border:none;border-radius:4px;cursor:pointer}input[type="range"]{-webkit-appearance:none;margin:8px 0;width:100%;height:20px;border-radius:5px;background:white;opacity:.8;-webkit-transition:0.2s;transition:opacity 0.2s}input[type="range"]::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:35px;height:35px;border-radius:50%;background:blue;cursor:pointer}#menu-button{outline:0;background:blue;color:white;padding:15px 15px;text-align:center;font-size:18px;margin:2px 2px;float:left;-webkit-box-shadow:2px 3px 9px 2px rgba(0,0,0,.52);box-shadow:2px 3px 9px 2px rgba(0,0,0,.52)}#wifi{padding:5px;margin:0;outline:0;background:#4caf50;color:white;text-align:right;height:10%;float:top;-webkit-box-shadow:2px 3px 9px 2px rgba(0,0,0,.52);box-shadow:2px 3px 9px 2px rgba(0,0,0,.52)}#wifi>input[type="text"]{margin:2px;width:35%;outline:0;padding:2px;font-size:15px}#wifi>label{font-size:15px;width:auto}#menu{text-align:center;background:#1f568b;position:absolute;top:0;width:70%;height:auto}#menu ul li{display:table;width:auto;height:50px}#menu ul li a{color:#f1f1f1;font-size:20px;text-decoration:none;text-transform:uppercase;width:auto;padding:5px});