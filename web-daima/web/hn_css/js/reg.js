var hasSubmit = false;
var profileUserNameNotEmpty = "�û�������Ϊ��";
var profileUserNameTooLong = "�û������ܳ���18���ַ�";
var profileUserNameTooShort = "�û�����������4���ַ�";
var profileUserNameIllegal = "�û���ֻ��������ĸ�����ֺ��»���";
var profileNickNameTooLong = "�ǳƲ��ܳ���18���ַ�";
var profileNickNameTooShort = "�ǳƲ�������4���ַ�";
var profilePasswordNotEmpty = "���벻��Ϊ��";
var profilePasswordNotEmptySymbol = "���벻�ܰ����ո�";
var profilePasswordIllegal = "��������Ƿ��ַ�";
var profilePasswordMatchRule = '����������+��ĸ���';
var profilePasswordTooLong = "���벻�ܳ���18���ַ�";
var profilePasswordTooShort = "���벻������8���ַ�";
var profilePasswordNotMatch = "�����������벻һ��";
var profileUserNameNickNameIsSame = "�ǳƺ��û�������һ��";
var profilePhoneNumberNotEmpty = "�ֻ��Ų���Ϊ��";
var profilePhoneNumberSize = "������11λ��Ч�ֻ�����";
var profileEmailNotEmpty = "�����ʺŲ���Ϊ��";
var profileEmailTooLong = "���䲻�ܳ���64���ַ�";
var profileEmailRule = "��������Ч����";
var lastEmail = lastPhoneNumber = lastUserName = lastNickName = lastPassword = lastPassword2 = "";
var okButtonChineseName = "ȷ��";
var layerTitleChineseName = "��ʾ";

var k = "", timeout = 3000/*��ʱʱ�� ��λ����*/, once = 200/*�����ʱ�� ��λ����*/, runtime = 0/*��ʱ�� ��¼��ǰ�ύ��������ʱ��*/,querystr='&n='+(+ new Date());
function regCheck(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("regCheck()",once);
		return;
	}
	runtime = 0;
	var username = $("input[name='username']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
	
	//���صǿ�
	$("#gologin").html("");
	//�û���
	var chkname = checkUserName(true);
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
	var regtype = $("#regtype").val();
	if(regtype == "jj" || regtype == "jjclient" || regtype == "5599"){
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
	if($("input[name='usernameiserror']") && $("input[name='usernameiserror']").val() == 2){
		alert("�û�������ȷ���������ʾ�޸ģ�",function(){setSelect(username);});
		return false;
	}
	//Э����
	if($("input[name='userselect']").length > 0 && $("input[name='userselect']").attr("checked") != true){
		alert("���Ķ��û�����Э�飡");
		return false;
	}
	if($("#verifyVal").length > 0){
		$("#verifyVal").val() == '' ? alert("��������֤��",function(){setFocus($("#verifyVal"));}) : check_client_answer("formSubmit('http://jj.cn/reg/userReg.php')","alert('��֤�����벻��ȷ',function(){setSelect($('#verifyVal'));});");
		return false;
	}
	return formSubmit("http://jj.cn/reg/userReg.php");
}
function siteRegCheck(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("siteRegCheck()",once);
		return;
	}
	runtime = 0;
	var username = $("input[name='username']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
	//�û���
	var chkname = checkUserName(true);
	if(chkname == false) return false;
	if($("input[name='usernameiserror']") && $("input[name='usernameiserror']").val() == 2){
		alert("�û�������ȷ���������ʾ�޸ģ�",function(){setSelect(username);});
		return false;
	}
	//�ǳ�
	var chknick = checkNickName(true);
	if(chknick == false) return false;
	
	if($("input[name='nicknameiserror']") && $("input[name='nicknameiserror']").val() == 2){
		alert("�ǳƲ���ȷ���������ʾ�޸ģ�",function(){setSelect(nickname);});
		return false;
	}
	//����
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//��ʵ����
	var realname = $("input[name='realName']"), realName = realname.val();
	if(realname.length > 0){
		if($.trim(realName) == ""){
			alert("��ʵ��������Ϊ��",function(){setFocus(realname);});
			return false;
		}
	}
	//���֤��
	var idcard = $("input[name='idCard']"), idCard = idcard.val();
	if(idcard.length > 0){
		if($.trim(idCard) == ""){
			alert("���֤�Ų���Ϊ��",function(){setFocus(idcard);});
			return false;
		}
		/*if(!IdCardValidate(idCard)){
			alert("���֤�Ŵ���",function(){setFocus(idcard);});
			return false;
		}*/
	}
	return formSubmit("http://jj.cn/reg/userReg.php");
}
function webGameRegCheck(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("webGameRegCheck()",once);
		return;
	}
	runtime = 0;
	var username = $("input[name='username']"), nickname = $("input[name='nickname']"), password = $("input[name='password']"), repassword = $("input[name='repassword']");
	//�û���
	var chkname = checkUserName(true);
	if(chkname == false) return false;
	var usernameerr = $("input[name='usernameiserror']");
	if(usernameerr && usernameerr.val() == 2){
		alert("�û�������ȷ���������ʾ�޸ģ�",function(){setSelect(username);});
		return false;
	}
	//�ǳ�
	var chknick = checkNickName(true);
	if(chknick == false) return false;

	if($("input[name='nicknameiserror']") && $("input[name='nicknameiserror']").val() == 2){
		alert("�ǳƲ���ȷ���������ʾ�޸ģ�",function(){setSelect(nickname);});
		return false;
	}
	//����
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//��ʵ����
	var realname = $("input[name='realName']"), realName = realname.val();
	if(realName != "" && !isChinese(realName,"��ʵ�����Ƿ�")){
		return false;
	}
	//���֤��
	var idcard = $("input[name='idCard']"), idCard = idcard.val();
	if(idCard != "" && !IdCardValidate(idCard)){
		alert("���֤�Ŵ���");
		return false;
	}
	return formSubmit("http://jj.cn/reg/userReg.php?reg=webgame");
}
//�ֻ���ע��
function mobileRegCheck(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("mobileRegCheck()",once);
		return;
	}
	runtime = 0;
	//���صǿ�
	$("#gologin").html("");

	var username = $("input[name='username']"), password = $("input[name='password']"), smscode = $("input[name='smscode']");
	//�ֻ���
	var chkmobile = checkMobileNumber(true), mobilenumber = $("input[name='mobilenumber']");
	if(chkmobile == false) return false;
	if($("input[name='mobileiserror']") && $("input[name='mobileiserror']").val() == 2){
		alert("�ֻ��Ų���ȷ���������ʾ�޸ģ�",function(){setSelect(mobilenumber);});
		return false;
	}
	//����
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//������֤��
	if($.trim(smscode.val()) == ''){
		alert("�����������֤�룡",function(){setSelect(smscode);});
		return false;
	}
	//Э����
	if($("input[name='userselect']").length > 0 && $("input[name='userselect']").attr("checked") != true){
		alert("���Ķ��û�����Э�飡");
		return false;
	}
	return formSubmit("http://jj.cn/reg/userReg.php");
}
function emailRegCheck(){
	runtime += once;
	if($("input[name='loading']") && $("input[name='loading']").val() == 'loading' && runtime <= timeout){
		typeof(k) == "string" ? "" : clearTimeout(k);
		k = setTimeout("emailRegCheck()",once);
		return;
	}
	runtime = 0;
	var email = $("input[name='email']"), nickname = $("input[name='nickname']"), password = $("input[name='password']");
	//����
	var chkemail = checkEmail(true);
	if(chkemail == false) return false;
	if($("input[name='emailiserror']") && $("input[name='emailiserror']").val() == 2){
		alert("�û�������ȷ���������ʾ�޸ģ�",function(){setSelect(email);});
		return false;
	}
	//�ǳ�
	var chknick = checkNickName(true);
	if(chknick == false) return false;
	
	if($("input[name='nicknameiserror']") && $("input[name='nicknameiserror']").val() == 2){
		alert("�ǳƲ���ȷ���������ʾ�޸ģ�",function(){setSelect(nickname);});
		return false;
	}
	//����
	var chkpass = checkPassword(true);
	if(chkpass == false) return false;

	var chkrepass = checkPassword2(true);
	if(chkrepass == false) return false;
	//��ʵ����
	var realname = $("input[name='realName']"), realName = realname.val();
	if(realname.length > 0){
		if($.trim(realName) == ""){
			alert("��ʵ��������Ϊ��",function(){setFocus(realname);});
			return false;
		}
	}
	//���֤��
	var idcard = $("input[name='idCard']"), idCard = idcard.val();
	if(idcard.length > 0){
		if($.trim(idCard) == ""){
			alert("���֤�Ų���Ϊ��",function(){setFocus(idcard);});
			return false;
		}
		/*if(!IdCardValidate(idCard)){
			alert("���֤�Ŵ���",function(){setFocus(idcard);});
			return false;
		}*/
	}
	return formSubmit("http://jj.cn/reg/userReg.php");
}
//������֤
function checkEmail(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='email']"), email = obj.val(), emaillen = getTrueLength(email), tag = "checkEmailMsg";
	//Ϊ��
	if($.trim(email) == ""){
		t ? alert(profileEmailNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileEmailNotEmpty, 2);
		return false;
	}
	//��������
	if(emaillen >��64){
		t ? alert(profileEmailTooLong,function(){setSelect(obj)}) : showMsg(tag, profileEmailTooLong, 2);
		return false;
	}
	if(!isEmail(email)){
		t ? alert(profileEmailRule,function(){setSelect(obj);}) : showMsg(tag, profileEmailRule, 2);
		return false;
	}
	//AJAX��֤
	if(!t || $("#"+tag).html() == "" || email != lastEmail){
		if(email == lastEmail){
			return;
		}else{
			lastEmail = email;
		}
		showMsg(tag, "", 4);
		var sUrl = "http://a4.act.jj.cn/reg/check_loginname.php?loginname="+encodeURIComponent(email)+querystr+"&regtype=3&callback=?";
		$.ajax({
				url: sUrl,
				type: "get",
				dataType: "jsonp",
				jsonp: "callback",
				success: function(json){
					if(json.REV == true){
						showMsg(tag, decodeURI(json.MSG), 1);
					}else{
						showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='emailiserror' id='emailiserror' value='2' />", 2);
					}
				}
			});
	}
}
//�ֻ�����֤
function checkMobileNumber(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='mobilenumber']"), mobilenumber = obj.val(), tag = "checkMobileNumberMsg";
	//Ϊ��
	if($.trim(mobilenumber) == ""){
		t ? alert(profilePhoneNumberNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profilePhoneNumberNotEmpty, 2);
		lastPhoneNumber = mobilenumber;
		return false;
	}
	var res = isMobileChk(mobilenumber,0);
	//��������
	if(!res){
		t ? alert(profilePhoneNumberSize,function(){setSelect(obj)}) : showMsg(tag, profilePhoneNumberSize, 2);
		lastPhoneNumber = mobilenumber;
		return false;
	}
	//AJAX��֤
	if(!t || $("#"+tag).html() == "" || mobilenumber != lastPhoneNumber){
		if(mobilenumber == lastPhoneNumber){
			return;
		}else{
			lastPhoneNumber = mobilenumber;
		}
		showMsg(tag, "", 4);
		var sUrl = "http://a4.act.jj.cn/reg/check_loginname.php?loginname="+encodeURIComponent(mobilenumber)+querystr+"&regtype=1&callback=?";	
		$.ajax({
				url: sUrl,
				type: "get",
				dataType: "jsonp",
				jsonp: "callback",
				cache: false,
				success: function(json){
					if(json.REV == true){
						showMsg(tag, decodeURI(json.MSG), 1);
					}else{
						showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='mobileiserror' id='mobileiserror' value='2' />", 2);
					}
				}
			});
	}
}
//�û�������֤
function checkUserName(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='username']"), username = obj.val(), usernamelen = getTrueLength(username), tag = "checkUserNameMsg";
	//Ϊ��
	if($.trim(username) == ""){
		t ? alert(profileUserNameNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profileUserNameNotEmpty, 2);
		return false;
	}
	//��������
	if(usernamelen < 4 || usernamelen >��18){
		t ? alert(usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong,function(){setSelect(obj)}) : showMsg(tag, usernamelen < 4 ? profileUserNameTooShort : profileUserNameTooLong, 2);
		return false;
	}
	//AJAX��֤
	if(!t || $("#"+tag).html() == "" || username != lastUserName){
		if(username == lastUserName){
			return;
		}else{
			lastUserName = username;
		}
		showMsg(tag, "", 4);
		var sUrl = "http://a4.act.jj.cn/reg/check_loginname.php?loginname="+encodeURIComponent(username)+querystr+"&regtype=1&callback=?";	
		$.ajax({
				url: sUrl,
				type: "get",
				dataType: "jsonp",
				jsonp: "callback",
				success: function(json){
					if(json.REV == true){
						showMsg(tag, decodeURI(json.MSG), 1);
					}else{
						showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='usernameiserror' id='usernameiserror' value='2' />", 2);
					}
				}
			});
	}
}
//�ǳ���֤
function checkNickName(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='nickname']"), nickname = obj.val(), nicknamelen = getTrueLength(nickname), tag = "checkUserNickMsg";
	//Ϊ��
	if($.trim(nickname) != ""){
		//��������
		if(nicknamelen < 4 || nicknamelen >��18){
			t ? alert(nicknamelen < 4 ? profileNickNameTooShort : profileNickNameTooLong,function(){setSelect(obj);}) : showMsg(tag, nicknamelen < 4 ? profileNickNameTooShort : profileNickNameTooLong, 2);
			return false;
		}
		//��Ч����֤
		if($.trim(nickname) == $.trim($("input[name='username']").val())){
			t ? alert(profileUserNameNickNameIsSame,function(){setSelect(obj);}) : showMsg(tag, profileUserNameNickNameIsSame, 2);
			return false;
		}
		//AJAX��֤
		if(!t || $("#"+tag).html() == "" || nickname != lastNickName){
			if(nickname == lastNickName){
				return;
			}else{
				lastNickName = nickname;
			}
			showMsg(tag, "", 4);
			var sUrl = "http://a4.act.jj.cn/reg/check_nickname.php?nickname="+encodeURIComponent(nickname)+querystr+"&callback=?";
			$.ajax({
					url: sUrl,
					type: "get",
					dataType: "jsonp",
					jsonp: "callback",
					success: function(json){
						if(json.REV == true){
							showMsg(tag, decodeURI(json.MSG), 1);
						}else{
							showMsg(tag, decodeURI(json.MSG)+"<input type='hidden' name='nicknameiserror' id='nicknameiserror' value='2' />", 2);
						}
					}
				});
		}
	}else{
		showMsg(tag, "");
	}
}
//������֤
function checkPassword(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='password']"), password = obj.val(), passwordlen = getTrueLength(password), tag = "checkPasswordMsg";
	//Ϊ��
	if(password == ""){
		t ? alert(profilePasswordNotEmpty,function(){setFocus(obj);}) : showMsg(tag, profilePasswordNotEmpty, 2);
		return false;
	}
	//��������
	if(passwordlen < 8 || passwordlen >��18){
		t ? alert(passwordlen < 8 ? profilePasswordTooShort : profilePasswordTooLong,function(){setSelect(obj);}) : showMsg(tag, passwordlen < 8 ? profilePasswordTooShort : profilePasswordTooLong, 2);
		return false;
	}
	//��Ч����֤
	var reg = true;
	var haveEmpty = false;
	for(i=0;i<passwordlen;i++){
		var charcode = password.charCodeAt(i);
		if(charcode < 32 || charcode > 126 || charcode == 39){
			reg = false;
		}else if(charcode == 32){
			haveEmpty = true;
		}
	}
	if(!reg){
		t ? alert(profilePasswordIllegal,function(){setSelect(obj);}) : showMsg(tag, profilePasswordIllegal, 2);
		return false;
	}
	if(haveEmpty){
		t ? alert(profilePasswordNotEmptySymbol,function(){setSelect(obj);}) : showMsg(tag, profilePasswordNotEmptySymbol, 2);
		return false;
	}
	var n = (password.match(/[\d]+/g) ? 1 : 0) + (password.match(/[a-z]+/g) ? 1 : 0) + (password.match(/[A-Z]+/g) ? 1 : 0) + (password.match(/[~!@#\$%\^&\*\(\)_\+\|\{\}":\?<>`\-=\\\[\]';\/\.,]+/g) ? 1 : 0);
	if(n<2){
		t ? alert(profilePasswordMatchRule,function(){setSelect(obj);}) : showMsg(tag, profilePasswordMatchRule, 2);
		return false;
	}else{
		showMsg(tag, "", 1);
	}
	if($("input[name='repassword']").val() != '') checkPassword2();
}
//�ظ�������֤
function checkPassword2(t){
	t = (arguments.length == 0) ? false : true;
	var obj = $("input[name='repassword']"), repassword = obj.val(), repasswordlen = getTrueLength(repassword), tag = "checkPasswordMsg2";
	if(repassword == "" && !t){
		showMsg(tag, profilePasswordNotEmpty, 2);
		return false;
	}
	if(repassword != $("input[name='password']").val()){
		t ? alert(profilePasswordNotMatch,function(){setSelect(obj);}) : showMsg(tag, profilePasswordNotMatch, 2);
		return false;
	}
	//��������
	if((repasswordlen < 8 || repasswordlen >��18) && !t){
		showMsg(tag, repasswordlen < 8 ? profilePasswordTooShort : profilePasswordTooLong, 2);
		return false;
	}
	showMsg(tag, "", 1);
}
function formSubmit(url){
	if(!hasSubmit){
		$("form[name='form1']").attr("action",url).submit();
		setTimeout(function(){
			$.alerts.ifClose = 0;
			jHtml('',"��ʾ",600);
			$(".pmsg").html("<div class='alertLoading'><img src='http://hn_img/images/jquery_alert/alertLoading.gif'><span>ע���ύ�У����Ե� ...</span></div>");
		},0);
	}else{
		alert("���Ѿ��ύ���벻Ҫ�ظ��ύ��");
		return false;
	}
}
function showHead(){
	if($("#touxiang").css("display") == 'none'){
		showImage(1);
		$("#touxiang").css("display","");
	}else{
		$("#touxiang").css("display","none");
	}
}
function changeState(){
	if(hasSubmit == true){
		hasSubmit = false;
		$("getcode1").src = '/verify_code/img.php?'+Math.random();
	}
}
function hideHead(picNo){
	if(picNo == 0)
		picNo = $("input[name='figureid']").val();
	$("#headPic").attr('src',"http://hn_img/images/head/"+picNo+".jpg");
	$("input[name='figureid']").val(picNo);
	$("#touxiang").css("display","none");
}
var headarr = new Array;
for(var i=1; i<=100;i++){
	headarr.push(i);
}
function showImage(pageNo){
	var pageNum = 9, pageTotal = 12, headToatl = 100, headMaxId = 100;
	if(pageNo < 1)
		pageNo = 1
	if(pageNo > pageTotal)
		pageNo = pageTotal
	imageStr = "<div class='txShow'>"
	for(i = 0;i < 9;i++){
		picNo = (pageNo - 1) * pageNum + i
		picNo = headarr[picNo];
		if(picNo - 1 < headMaxId)
			imageStr = imageStr + "<a href='#' onClick='hideHead("+picNo+");return false;' ><img src='http://hn_img/images/head/"+picNo+".jpg' width='57' height='50' /></a>"
	}
	previousPage = pageNo - 1
	nextPage = pageNo + 1
	imageStr = imageStr + "</div><div class='txClick'><a href='#' onClick='showImage("+ previousPage +");return false;' class='aBlock'> &lt; </a><a href='#' onClick='showImage("+ nextPage +");return false;' class='aBlock'> &gt; </a><div class='yema'>"+ pageNo +"/"+ pageTotal +"</div><a href='#' onClick='hideHead(0);return false;' class='aBlock'> �� </a></div>"
	$("#touxiang").html(imageStr);
}
function showMsg(id,msg,flag){
	if(!$('#'+id)) return false;
	switch(flag){
		case 1:
			msg = '<span class="JuCOk"><img src="http://hn_img/images/newIndex/checkRight.gif" width="13" height="13"></span>';
			break;
		case 2:
			msg = '<span class="JuCNo"><img src="http://hn_img/images/newIndex/checkError.gif" width="13" height="13">&nbsp;'+msg+'</span>';	
			break;
		case 3:
			msg = '<span class="JuCNo"><img src="http://hn_img/images/newIndex/checkWarn.gif" width="13" height="13">&nbsp;'+msg+'</span>';
			break;
		case 4:
			msg = '<span class="JuCOk"><img src="http://hn_img/images/newIndex/loading.gif" width="13" height="13"><input type="hidden" name="loading" value="loading" />&nbsp;'+msg+'</span>';	
			break;
	}
	$("#"+id).html(msg);
}
function isEmail(str){
	return /^([a-zA-Z0-9_-]\.*)+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-]+)*(\.[a-zA-Z0-9_-]{2,3})$/.test(str);
}
function setFocus(obj){
	window.setTimeout(function(){obj.focus();}, 10);
}
function setSelect(obj){
	window.setTimeout(function(){obj.select();}, 10);
}
function alert(msg, callback){
	$.alerts.okButton = "ȷ��";
	$.alerts.ifClose = 0;
	if(typeof(callback) == "function"){
		jAlert(msg,"��ʾ",function(){callback();});
	}else{
		jAlert(msg,"��ʾ");
	}
}