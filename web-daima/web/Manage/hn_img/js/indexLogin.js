function checkinput(){
	if(document.input.username.value == ""){
		document.input.username.focus();
		alert("�û�������Ϊ�գ�");
		return false;
	}
	if(document.input.password.value == ""){
		document.input.password.focus();
		alert("���벻��Ϊ�գ�");
		return false;
	}else
		return true;
}

$('login').innerHTML = "<div class='loadingN'><img src='http://hn_img/images/newIndex/201008/loadingN.gif' alt='���ݼ�����' /></div>";
var url = "/ajax/login_index.php";
var pars = "time="+Math.random();
var myAjax = new Ajax.Updater({success: "login"},url,{method:"get",parameters: pars,onFailure: reportError});
function reportError(request){
	$('login').innerHTML = "<div class='loadingN'>���ݼ���ʧ��,��ˢ�µ�ǰҳ������.</div>";
}

function changeTabsCss(id,classname){
	if(!$(id)) return false;
	$(id).className = classname;
}


