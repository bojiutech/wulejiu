timeout = 10000
var profileEmailNotEmpty = "�����ʺŲ���Ϊ�ա�";
var profileEmailRule = "��������Ч���䡣";
var profileUserNameRule = "�û������벻�Ϸ���";
function showUsernameErr(){
	if($("#uerror").length == 0){
		var str = '<li class="username" id="uerror">';
		str += '<div class="tipWord forUp ">';
		str += '�û�������Ϊ1��ͷ11λ���֡��������д�����ֻ����룬����ע���ֻ��ʻ�������ȫ����ݡ�';
		str += '<div><button onclick="changeRegType();return false;">����</button><span></span></div>';
		str += '</div></li>';
		$("ul[class='regList'] li[class='username']:last").after(str);
	}
}

//�û�������֤
function checkLoginName(t){
	t = (arguments.length == 0) ? false : true;
	var regtype = $("input[name='userregtype']").val();
	var errorname = "";
	switch(regtype){
		case '1':
			errorname = "username";
			var obj = $("input[name='username']"), username = obj.val(), usernamelen = getTrueLength(username), tag = "checkUserNameMsg";
			//Ϊ��
			if($.trim(username) == ""){
				t ? alert(profileUserNameNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileUserNameNotEmpty, 2);
				return false;
			}
			//��֤�Ƿ���1��ͷ11λ����
			var res = isMobileChk(username,0);
			if(res){
				//showUsernameErr();
				t ? alert(profileUserNameRule,function(){setFocus(obj);}) : showMsg(tag, profileUserNameRule, 2);
				return false;
			}else{
				if($("#uerror").length) $("#uerror").remove();
			}
			//��������
			if(usernamelen < 4 || usernamelen >��18){
				t ? alert(usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong,function(){setSelect(obj)}) : showMsg(tag, usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong, 2);
				return false;
			}
			break;
		case '2':
			errorname = "mobilenumber";
			var obj = $("input[name='mobilenumber']"), username = obj.val(), tag = "checkMobileNumberMsg";
			//Ϊ��
			if($.trim(username) == ""){
				t ? alert(profilePhoneNumberNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profilePhoneNumberNotEmpty, 2);
				lastUserName = username;
				return false;
			}
			//�Ϸ���У��
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
			//Ϊ��
			if($.trim(username) == ""){
				t ? alert(profileEmailNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileEmailNotEmpty, 2);
				return false;
			}
			//�Ϸ���У��
			var res = isEmail(username);
			if(!res){
				t ? alert(profileEmailRule,function(){setSelect(obj)}) : showMsg(tag, profileEmailRule, 2);
				return false;
			}
	}
	//AJAX��֤
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
								str += '����д�����ֻ����룬��Ϊ��ע���ֻ��ʻ�������ȫ����ݡ�';
								str += '<div><button onclick="changeRegType();return false;">����</button><span></span></div>';
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
	var checkitem = "�û���";
	switch(regtype){
		case '1':
			checkitem = "�û���";errorname = "username";
			var username = $("input[name='username']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
			break;
		case '2':
			checkitem = "�ֻ���";errorname = "mobilenumber";
			var username = $("input[name='mobilenumber']"), nickname = $("input[name='nickname']"), password = $("input[name='password']"), smscode = $("input[name='smscode']");
			break;
		case '3':
			checkitem = "����";errorname = "email";
			var username = $("input[name='email']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
			break;
	}

	//�û���
	var chkname = checkLoginName(true);
	if(chkname == false) return false;
	//����
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//�ǳ�
	var chknick = checkNickName(true);
	if(chknick == false) return false;
	
	if($("input[name='nicknameiserror']") && $("input[name='nicknameiserror']").val() == 2){
		alert("�ǳƲ���ȷ���������ʾ�޸ģ�",function(){setSelect(nickname);});
		return false;
	}
	//��ʵ����
	//���֤��
	var regtype = $("#userregtype").val();
	if(regtype == "3" || regtype == "1" || regtype == "2"){
		var realname = $("input[name='realName']"), realName = realname.val();
		var idcard = $("input[name='idCard']"), idCard = idcard.val();
		if($.trim(realName) == ""){
			alert("��ʵ��������Ϊ��",function(){setFocus(realname);});
			return false;
		}
		/*if(!isChinese(realName,'��ʵ����ֻ����������')){
			setSelect(realname);
			return false;
		}*/
		if($.trim(idCard) == ""){
			alert("���֤�Ų���Ϊ��",function(){setFocus(idcard);});
			return false;
		}
		/*if(!IdCardValidate(idCard)){
			alert('���֤�������������������',function(){setSelect(idcard);});
			return false;
		}*/
	}
	//�û���
	if($("input[name='"+errorname+"iserror']") && $("input[name='"+errorname+"iserror']").val() == 2){
		alert(checkitem+"����ȷ���������ʾ�޸ģ�",function(){setSelect(username);});
		return false;
	}
	//Э����
	if($("input[name='userselect']").length > 0 && $("input[name='userselect']").attr("checked") != true){
		alert("���Ķ��û�����Э�飡");
		return false;
	}
	if(regtype == '2'){
		//������֤��
		if($.trim(smscode.val()) == ''){
			alert("�����������֤�룡",function(){setSelect(smscode);});
			return false;
		}

	}
	if($("#verifyVal").length > 0 && $("#verifyVal").css("display") != 'none'){
		$("#verifyVal").val() == '' ? alert("��������֤��",function(){setFocus($("#verifyVal"));}) : check_client_answer("formSubmit('http://jj.cn/reg/userReg.php')","alert('��֤�����벻��ȷ',function(){setSelect($('#verifyVal'));});");
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
//�ֻ���֤��
var speed = 1000; //�ٶ�
var wait = 60; //ͣ��ʱ��
function updateinfo()
{
	var tmp ;
	tmp = document.getElementById('getcode') ;
	tmp.disabled = true;
	if(wait == 0)
	{
		tmp.innerHTML = "���»�ȡ��֤��";
		wait = 60 ;
		tmp.disabled = false;
	}
	else
	{
		tmp.innerHTML = "��֤���ȡ��..."+wait;
		wait--;
		window.setTimeout("updateinfo()",speed);
	}
}
function getMsgCode(){
	var chkmobilenumber = checkLoginName(true);
	if(chkmobilenumber == false) return false;
	var mobilenumber = $("input[name='mobilenumber']");
	if($("input[name='mobilenumberiserror']") && $("input[name='mobilenumberiserror']").val() == 2){
		alert("�ֻ��Ų���ȷ���������ʾ�޸ģ�",function(){setSelect(mobilenumber);});
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
					showMsg("smscodeMsg",'�Ƿ�����!',2);
					break;
				case 2:
					showMsg("smscodeMsg",'���Ż�ȡʧ�ܣ����Ժ�����!',2);
					break;
				case 1:
					showMsg("smscodeMsg",'��ʱ���ڲ���̫�࣬���Ժ�����!',2);
					break;
				default:
					$("input[name='smscode']").attr("disabled",false);
					showMsg("smscodeMsg",json.tmp_str,0);//'���ŷ��ͳɹ��������������֤�롣'+
					break;
			}
		},
		error:function(json)
		{
			showMsg("smscodeMsg",'���Ż�ȡʧ�ܣ����Ժ�������!',0);
		}
	});
}