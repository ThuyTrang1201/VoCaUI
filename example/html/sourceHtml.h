#ifndef SOURCE_HTML
#define SOURCE_HTML

const char * first_part_page = R""""(
	
<meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1">
<html>
<head>
<link rel='stylesheet' href='style.css'>
<title>
)"""";
const char * mid_part_page = R""""(
</title>
</head>
<body>
<div id="mnubtn" onclick="shwlmnu()">| | |</div>
)"""";
const char * last_part_page = R""""(
<div id="mask" onclick="hideMenu()"></div>
<script src="script.js"></script>
</body>
</html>
)"""";


const char * java_script = R""""(var rfg=[];var tokn=0;function sdt(i,v){var f=new FormData();f.append(i,v);var x=new XMLHttpRequest();x.open("POST","/recv",!0);x.send(f);rfg.push(i);rfg=Array.from(new Set(rfg));senb(i,false)}function senb(i,v){var c=document.getElementById(i);if(c==null)return;c=c.getElementsByTagName('*');for(var n of c){n.disabled=!v}}function shwlmnu(){document.getElementById("mnubtn").style.display='none';document.getElementsByClassName('lmnu')[0].style.display='block'}function hidelmnu(){document.getElementById("mnubtn").style.display='block';document.getElementsByClassName('lmnu')[0].style.display='none'}function oMnClk(i){sdt(i,'clkd');var mnus=document.getElementsByClassName('mnu');for(var j=0;j<mnus.length;j++){var e=mnus[j];if(e.id===i)e.style.display='block';else e.style.display='none'}hidelmnu()}function ajax(){var conn=new XMLHttpRequest();conn.timeout=950;var cto=window.setTimeout(ctof,1000);function ctof(){if(rfg.length>0)sdt('all','');ajax();console.log("Request timed out")}conn.onreadystatechange=function(){if(this.readyState==4&&this.status==200){var res=conn.responseText;console.log(res);var o=JSON.parse(res);tokn=conn.getResponseHeader('tokn');for(x in o){e=document.getElementById(x);rfg.splice(rfg.indexOf(x),1);senb(x,true);if(e==null)continue;var cls=e.getAttribute("class");var chdr=e.children;if(cls==="inptxt"){if(chdr[1].value===''){chdr[1].value=o[x];chdr[2].innerHTML='OK'}}else if(cls==="sglbtn"){if(chdr[0].innerHTML==='...')chdr[0].innerHTML=o[x]}else if(cls==="txtvie"){chdr[1].value=o[x]}else if(cls==="rng"){if((chdr[2]!==document.activeElement)){chdr[1].innerHTML=o[x];chdr[2].value=o[x]}}else if(cls==="swch"){chdr[1].checked=o[x].toLowerCase()==='true'}else if(cls==="state"){chdr[1].checked=o[x].toLowerCase()==='true';chdr[1].disabled=true}else if(cls==="tmpk"){if((chdr[3]!==document.activeElement)&&(chdr[5]!==document.activeElement)){var val=parseInt(o[x]);chdr[3].value=parseInt(val/60);chdr[5].value=val%60}}};window.clearTimeout(cto);ajax()}};conn.open("POST","/trans",!0);var f=new FormData();f.append('tokn',tokn);conn.send(f)}function onloadDone(){var hLst=document.createElement("datalist");var eHLsts=document.getElementsByClassName('hLst');for(var j=0;j<eHLsts.length;j++){for(var i=0;i<24;i++){eHLsts[j].options.add(new Option(i,i))}};var eMLsts=document.getElementsByClassName('mLst');for(var j=0;j<eMLsts.length;j++){for(var i=0;i<60;i++){eMLsts[j].options.add(new Option(i,i))}}sdt('all','');document.getElementsByClassName('mnu')[2].style.display='block';ajax()}window.onload=onloadDone;)"""";


const char* menu_css =R""""(*{margin:0;padding:0}body{background-color:lightblue}#mnubtn{position:absolute;transform:rotate(90deg);outline:0;background:#666666e0;color:#fff;padding:10px 10px;text-align:center;font-size:30px;margin:5px 5px;float:left;cursor:pointer}.mnu{width:100%;position:absolute;margin-top:65px;margin-left:5px;border:2px solid gray;border-radius:15px;padding:10px;text-align:center}.mnu>label{letter-spacing:5px;text-transform:uppercase;font-size:25px;color:#F44336;font-weight:700;text-shadow:0 0 5px #000}.lmnu{position:absolute;width:100%;height:100%;background:#9e9e9ed1;padding-left:5px;padding-top:10px}.lmnu li{width:70%;font-size:30px;list-style-type:none;padding:10px;text-transform:uppercase;font-weight:700;background:#666666e0;margin-bottom:5px}.lmnu a{color:#f1f1f1;text-decoration:none}.lmnu li:hover{font-size:35px}.inptxt{border-radius:5px;background-color:#f2f2f2;padding:20px}.inptxt>label{float:left;font-weight:700}.inptxt>input{width:100%;padding:12px 20px;margin:8px 0;display:inline-block;border:1px solid #ccc;border-radius:4px;box-sizing:border-box}.inptxt>button{width:100%;background-color:#4CAF50;color:#fff;padding:14px 20px;margin:8px 0;border:none;border-radius:4px;cursor:pointer}.inptxt>button:disabled{background-color:#ccc;color:#666}button{background-color:#f44336;border:none;border-radius:10px;color:#fff;padding:15px 32px;text-align:center;display:inline-block;font-size:16px;margin:10px}.txtvie{border-radius:5px;background-color:#f2f2f2;padding:30px}.txtvie>label{float:left;font-weight:700}.txtvie>input{width:100%;padding:12px 20px;margin:8px 0;display:inline-block;border:1px solid #ccc;border-radius:4px;box-sizing:border-box}.sglbtn>button{background-color:#4CAF50;border:none;border-radius:5px;color:#fff;padding:15px 32px;text-align:center;display:inline-block;font-size:16px;margin:10px}.sglbtn>button:disabled{background-color:#ccc;color:#666}.rng{border-radius:5px;background-color:#f2f2f2;padding:20px}.rng>label{float:left;font-weight:700;margin-bottom:10px}.rng>input{-webkit-appearance:none;width:100%;height:25px;background:#d3d3d3;outline:none;opacity:.7;-webkit-transition:.2s;transition:opacity .2s}.rng>input::-moz-range-thumb{width:25px;height:25px;background:#4CAF50;cursor:pointer}.rng>input:hover{opacity:1}.rng>input::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:25px;height:25px;background:#4CAF50;cursor:pointer}.tmpk{display:flex;text-align:left;border-radius:5px;background-color:#f2f2f2;padding:20px;align-items:center}.tmpk>label{font-weight:700;margin-bottom:10px}.tmpk>label:first-child{font-weight:700;margin-bottom:10px}.tmpk>select{background-color:#f1f1f1;width:100px;margin:5px;text-align:center;line-height:75px;font-size:30px}.tmpk>button{background-color:#555;border:none;border-radius:10px;padding:15px 32px;text-align:center;display:inline-block;font-size:16px;margin:10px}.tmpk>button:disabled{background-color:#ccc;color:#666}.swch{display:flex;border-radius:5px;background-color:#f2f2f2;padding:30px;text-align:center;align-items:center}.swch>label{float:left;font-weight:700;margin-bottom:10px;margin-right:20px}.swch>input[type=checkbox]{visibility:hidden}.swch label:nth-child(3){cursor:pointer;width:100px;height:50px;background:#4CAF50;display:block;border-radius:50px;position:relative}.swch label:nth-child(3):after{color:#000;content:'OFF';position:absolute;top:3px;left:3px;width:45px;height:45px;background:#fff;font-size:20px;line-height:40px;border-radius:45px;transition:0.3s}.swch input:checked+label:nth-child(3){background:#F44336}.swch input:checked+label:nth-child(3):after{content:'ON';vertical-align:bottom;left:calc(100% - 5px);transform:translateX(-100%)}.swch label:nth-child(3):active:after{width:130px}.state{display:flex;border-radius:5px;background-color:#f2f2f2;padding:30px;text-align:center;align-items:center}.state>label{float:left;font-weight:700;margin-bottom:10px;margin-right:20px}.state>input[type=checkbox]{visibility:hidden}.state label:nth-child(3){cursor:pointer;width:100px;height:50px;background:#4caf50a8;display:block;border-radius:50px;position:relative}.state label:nth-child(3):after{color:#000;content:'OFF';position:absolute;top:3px;left:3px;width:45px;height:45px;background:#fff;font-size:20px;line-height:40px;border-radius:45px;transition:0.3s}.state input:checked+label:nth-child(3){background:#f44336a8}.state input:checked+label:nth-child(3):after{content:'ON';vertical-align:bottom;left:calc(100% - 5px);transform:translateX(-100%)}.state label:nth-child(3):active:after{width:130px})"""";
#endif