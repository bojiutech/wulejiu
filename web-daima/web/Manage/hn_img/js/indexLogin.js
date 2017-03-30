function checkinput(){
	if(document.input.username.value == ""){
		document.input.username.focus();
		alert("用户名不能为空！");
		return false;
	}
	if(document.input.password.value == ""){
		document.input.password.focus();
		alert("密码不能为空！");
		return false;
	}else
		return true;
}

$('login').innerHTML = "<div class='loadingN'><img src='http://hn_img/images/newIndex/201008/loadingN.gif' alt='数据加载中' /></div>";
var url = "/ajax/login_index.php";
var pars = "time="+Math.random();
var myAjax = new Ajax.Updater({success: "login"},url,{method:"get",parameters: pars,onFailure: reportError});
function reportError(request){
	$('login').innerHTML = "<div class='loadingN'>数据加载失败,请刷新当前页面重试.</div>";
}

function changeTabsCss(id,classname){
	if(!$(id)) return false;
	$(id).className = classname;
}


