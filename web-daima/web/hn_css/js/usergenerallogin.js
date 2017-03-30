function checklogin(isShowCode) {
	var userName = $("#username").val();
	var userPass = $("#userpass").val();
	var hasUserName = (userName == "") || (userName == null) || (userName.length == 0);
	var hasUserPass = (userPass == "") || (userPass == null) || (userPass.length == 0); 	
	var loginName;
	var msg = "";
	var hasErr = false;
		
	if(hasUserName && hasUserPass) {		
		msg +=��"�������˺ź�����";
		hasErr = true;
		$("#username").trigger("focusin");
	} else if(hasUserName) {
		msg +=��"�����������˺�";
		hasErr = true;
		$("#username").trigger("focusin");
	} else if(!isRightUserName(userName)) {
		msg +=��"��������˺Ų���ȷ";
		hasErr = true;
		$("#username").trigger("focusin");
	} else if(hasUserPass) {
		msg +=��"����������";
		hasErr = true;
		$("#userpass").trigger("focusin");
	} else if(userPass.length < 6 || userPass.length > 20) {
		msg +=��"���볤����6��20���ַ�֮��";
		hasErr = true;
		$("#userpass").trigger("focusin");
	}
	if(hasErr) {
		$("#errMsg").html(msg);
		return false;
	}
	if(isShowCode == 1 || isNeedVerify() || $("#verifyVal").length) {
		var verifyVal = $("#verifyVal").val();
		var hasVerifyVal = (verifyVal == "") || (verifyVal == null) || (verifyVal.length == 0);
		if(hasVerifyVal) {
			$("#errMsg").html("��������֤��");
			$("#verifyVal").trigger("focusin");
			return false;
		}
		check_client_answer('verifySuccess()','verifyFail()');		
	} else {
		verifySuccess();
	}
}

function verifySuccess() {
	$("#loginFrom").submit();	
}

function verifyFail() {
	$("#errMsg").html("��֤�����벻��ȷ");
	return false;
}

function isNeedVerify() {
	var isNeed = false;
	loginInfo = $.cookie("UserLoginInfo");
	if(loginInfo != "" && loginInfo != null) {
		temp = loginInfo.split(",");
		if(temp[0] != $("#username").val() || temp[1] != "1") {
			isNeed = true;
		}
	} else {
		isNeed = true;
	}
	return isNeed;
}

//����û���
function isRightUserName(userName) {
	var regex = [/^13[0-9]{9}$|1[58]{1}[0-35-9]{1}[0-9]{8}$|14[57]{1}[0-9]{8}$/,/^[_a-zA-Z0-9]{3,19}$/,/^([a-zA-Z0-9_-]\.*)+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-]+)*(\.[a-zA-Z0-9_-]{2,3})$/];
	for(i in regex){
		if(regex[i].test(userName)) {
			return true;
		}
	}
	return false;
}