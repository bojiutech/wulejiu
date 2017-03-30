timeout = 10000
var profileEmailNotEmpty = "邮箱帐号不能为空。";
var profileEmailRule = "请输入有效邮箱。";
var profileUserNameRule = "用户名输入不合法。";
function showUsernameErr(){
	if($("#uerror").length == 0){
		var str = '<li class="username" id="uerror">';
		str += '<div class="tipWord forUp ">';
		str += '用户名不能为1开头11位数字。如果您填写的是手机号码，请您注册手机帐户，更安全更便捷。';
		str += '<div><button onclick="changeRegType();return false;">继续</button><span></span></div>';
		str += '</div></li>';
		$("ul[class='regList'] li[class='username']:last").after(str);
	}
}

//用户名称验证
function checkLoginName(t){
	t = (arguments.length == 0) ? false : true;
	var regtype = $("input[name='userregtype']").val();
	var errorname = "";
	switch(regtype){
		case '1':
			errorname = "username";
			var obj = $("input[name='username']"), username = obj.val(), usernamelen = getTrueLength(username), tag = "checkUserNameMsg";
			//为空
			if($.trim(username) == ""){
				t ? alert(profileUserNameNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileUserNameNotEmpty, 2);
				return false;
			}
			//验证是否是1开头11位数字
			var res = isMobileChk(username,0);
			if(res){
				//showUsernameErr();
				t ? alert(profileUserNameRule,function(){setFocus(obj);}) : showMsg(tag, profileUserNameRule, 2);
				return false;
			}else{
				if($("#uerror").length) $("#uerror").remove();
			}
			//长度限制
			if(usernamelen < 4 || usernamelen >　18){
				t ? alert(usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong,function(){setSelect(obj)}) : showMsg(tag, usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong, 2);
				return false;
			}
			break;
		case '2':
			errorname = "mobilenumber";
			var obj = $("input[name='mobilenumber']"), username = obj.val(), tag = "checkMobileNumberMsg";
			//为空
			if($.trim(username) == ""){
				t ? alert(profilePhoneNumberNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profilePhoneNumberNotEmpty, 2);
				lastUserName = username;
				return false;
			}
			//合法性校验
			var res = isMobileChk(username,0);
			if(!res){
				t ? alert(profilePhoneNumberSize,function(){setSelect(obj)}) : showMsg(tag, profilePhoneNumberSize, 2);
				lastUserName = username;
				return false;
			}
			break;
		case '3':
			errorname = "email";
			var obj = $("input[name='email']"), username = obj.val(), usernamelen = getTrueLength(username), tag = "checkEmailMsg";
			//为空
			if($.trim(username) == ""){
				t ? alert(profileEmailNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileEmailNotEmpty, 2);
				return false;
			}
			//合法性校验
			var res = isEmail(username);
			if(!res){
				t ? alert(profileEmailRule,function(){setSelect(obj)}) : showMsg(tag, profileEmailRule, 2);
				return false;
			}
	}
	//AJAX验证
	if(!t || $("#"+tag).html() == "" || username != lastUserName || lastRegType){
		if(username == lastUserName && regtype == lastRegType){
			return;
		}else{
			lastUserName = username;
			lastRegType = regtype;
		}
		showMsg(tag, "", 4);
		var sUrl = "http://a4.act.jj.cn/reg/check_loginname.php?loginname="+encodeURIComponent(username)+querystr+"&regtype="+regtype+"&callback=?";
		$.ajax({
				url: sUrl,
				type: "get",
				dataType: "jsonp",
				jsonp: "callback",
				success: function(json){
					if(json.REV == true){
						showMsg(tag, decodeURI(json.MSG), 1);
					}else{
						switch(json.MID){
							case 14:
								var msg = decodeURI(json.MSG);
								var str = '<li class="username" id="u_sameas_m">';
								str += '<div class="tipWord forUp ">';
								str += '您填写的是手机号码，将为您注册手机帐户，更安全更便捷。';
								str += '<div><button onclick="changeRegType();return false;">继续</button><span></span></div>';
								str += '</div></li>';
								$("ul[class='regList'] li[class='username']:last").after(str);
								
								showMsg(tag, msg+"<input type='hidden' name='"+errorname+"iserror' id='usernameiserror' value='2' />", 2);
								break;
							case 15:
								showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='"+errorname+"iserror' id='"+errorname+"iserror' value='2' />", 2);
								break;
							default:
								showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='"+errorname+"iserror' id='"+errorname+"iserror' value='2' />", 2);
								break;
						}
					}
				}
			});
	}
}
var lastRegType = 1;
function generalReg(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("generalReg()",once);
		return;
	}
	runtime = 0;

	var regtype = $("input[name='userregtype']").val();
	var errorname = "";
	var checkitem = "用户名";
	switch(regtype){
		case '1':
			checkitem = "用户名";errorname = "username";
			var username = $("input[name='username']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
			break;
		case '2':
			checkitem = "手机号";errorname = "mobilenumber";
			var username = $("input[name='mobilenumber']"), nickname = $("input[name='nickname']"), password = $("input[name='password']"), smscode = $("input[name='smscode']");
			break;
		case '3':
			checkitem = "邮箱";errorname = "email";
			var username = $("input[name='email']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
			break;
	}

	//用户名
	var chkname = checkLoginName(true);
	if(chkname == false) return false;
	//密码
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//昵称
	var chknick = checkNickName(true);
	if(chknick == false) return false;
	
	if($("input[name='nicknameiserror']") && $("input[name='nicknameiserror']").val() == 2){
		alert("昵称不正确，请根据提示修改！",function(){setSelect(nickname);});
		return false;
	}
	//真实姓名
	//身份证号
	var regtype = $("#userregtype").val();
	if(regtype == "3" || regtype == "1" || regtype == "2"){
		var realname = $("input[name='realName']"), realName = realname.val();
		var idcard = $("input[name='idCard']"), idCard = idcard.val();
		if($.trim(realName) == ""){
			alert("真实姓名不能为空",function(){setFocus(realname);});
			return false;
		}
		/*if(!isChinese(realName,'真实姓名只能输入中文')){
			setSelect(realname);
			return false;
		}*/
		if($.trim(idCard) == ""){
			alert("身份证号不能为空",function(){setFocus(idcard);});
			return false;
		}
		/*if(!IdCardValidate(idCard)){
			alert('身份证号输入错误，请重新输入',function(){setSelect(idcard);});
			return false;
		}*/
	}
	//用户名
	if($("input[name='"+errorname+"iserror']") && $("input[name='"+errorname+"iserror']").val() == 2){
		alert(checkitem+"不正确，请根据提示修改！",function(){setSelect(username);});
		return false;
	}
	//协议书
	if($("input[name='userselect']").length > 0 && $("input[name='userselect']").attr("checked") != true){
		alert("请阅读用户服务协议！");
		return false;
	}
	if(regtype == '2'){
		//短信验证码
		if($.trim(smscode.val()) == ''){
			alert("请输入短信验证码！",function(){setSelect(smscode);});
			return false;
		}

	}
	if($("#verifyVal").length > 0 && $("#verifyVal").css("display") != 'none'){
		$("#verifyVal").val() == '' ? alert("请输入验证码",function(){setFocus($("#verifyVal"));}) : check_client_answer("formSubmit('http://jj.cn/reg/userReg.php')","alert('验证码输入不正确',function(){setSelect($('#verifyVal'));});");
		return false;
	}
	return formSubmit("http://jj.cn/reg/userReg.php");
}
function showMsg(id,msg,flag){
	if(!$('#'+id)) return false;
	switch(flag){
		case 1:
			msg = '<span class="JuCOk"><img src="http://hn_img/images/reg/correct.gif" width="20" height="20"></span>';
			break;
		case 2:
			msg = '<span class="JuCNo"><img src="http://hn_img/images/reg/error.gif" width="20" height="20">&nbsp;'+msg+'</span>';	
			break;
		case 3:
			msg = '<span class="JuCNo"><img src="http://hn_img/images/newIndex/checkWarn.gif" width="16" height="16">&nbsp;'+msg+'</span>';
			break;
		case 4:
			msg = '<span class="JuCOk"><img src="http://hn_img/images/newIndex/loading.gif" width="20" height="20"><input type="hidden" name="loading" value="loading" />&nbsp;'+msg+'</span>';	
			break;
	}
	$("#"+id).html(msg);
}
//手机验证码
var speed = 1000; //速度
var wait = 60; //停留时间
function updateinfo()
{
	var tmp ;
	tmp = document.getElementById('getcode') ;
	tmp.disabled = true;
	if(wait == 0)
	{
		tmp.innerHTML = "重新获取验证码";
		wait = 60 ;
		tmp.disabled = false;
	}
	else
	{
		tmp.innerHTML = "验证码获取中..."+wait;
		wait--;
		window.setTimeout("updateinfo()",speed);
	}
}
function getMsgCode(){
	var chkmobilenumber = checkLoginName(true);
	if(chkmobilenumber == false) return false;
	var mobilenumber = $("input[name='mobilenumber']");
	if($("input[name='mobilenumberiserror']") && $("input[name='mobilenumberiserror']").val() == 2){
		alert("手机号不正确，请根据提示修改！",function(){setSelect(mobilenumber);});
		$("#getcode").attr("disabled",false);
		return false;
	}
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading'){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("getMsgCode()",once);
		$("#getcode").attr("disabled",true);
		return;
	}
	runtime = 0;
	updateinfo();
	$("#smsTip").slideDown("slow"); 
	//$("input[name='smscode']").show().attr("disabled",true);
	var url = "http://a3.act.jj.cn/www/get_sms_code.php";
	$.ajax({
	    url: url,
		type: "get",
		data: {"mobile": $("input[name='mobilenumber']").val()},
		dataType: "jsonp",			
		cache: false,
		success: function(json)
		{
			switch(json.tmp_str)
			{
				case 4:
				case 3:
					showMsg("smscodeMsg",'非法操作!',2);
					break;
				case 2:
					showMsg("smscodeMsg",'短信获取失败，请稍后再试!',2);
					break;
				case 1:
					showMsg("smscodeMsg",'短时间内操作太多，请稍后重试!',2);
					break;
				default:
					$("input[name='smscode']").attr("disabled",false);
					showMsg("smscodeMsg",json.tmp_str,0);//'短信发送成功，请输入短信验证码。'+
					break;
			}
		},
		error:function(json)
		{
			showMsg("smscodeMsg",'短信获取失败，请稍后再试试!',0);
		}
	});
}