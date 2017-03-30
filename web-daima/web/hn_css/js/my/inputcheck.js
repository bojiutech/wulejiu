var okButtonChineseName = "确定";
var layerTitleChineseName = "提示";

function isNotEmpty(obj){
	if(arguments.length == 1)
		msg = "必填项不能为空！";
	else
		msg=arguments[1];
	if(obj.val() == "" || obj.val() == null){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}
	else
		return true;
}

/*输入不能为0*/
function isNotZero(obj){
	if(arguments.length == 1)
		msg = "必填项不能为零！";
	else
		msg=arguments[1];
	if(obj.val() == 0){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}
	else
		return true;
}

/*验证移动手机号码输入是否正确*/
function isYdMobile(obj){
	if(arguments.length == 1)
		msg = "手机号码格式不正确！";
	else
		msg = arguments[1];
	var reg0 = /^(134|135|136|137|138|139|147|150|151|152|158|159|187|188|182|183|184|157|178)\d{8}$/;
	var result = false;
	if(reg0.test(obj.val()))result = true;
	if(!result){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}else
		return true;		
}
/*验证联通手机号码输入是否正确*/
function isLtMobile(obj){
	if(arguments.length == 1)
		msg = "手机号码格式不正确！";
	else
		msg = arguments[1];
	var reg0 = /^(130|131|132|145|155|156|185|186|176)\d{8}$/;
	var result = false;
	if(reg0.test(obj.val()))result = true;
	if(!result){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}else
		return true;		
}

//验证电信手机号码输入是否正确
function isDxMobile(obj){
	if(arguments.length == 1)
		msg = "手机号码格式不正确！";
	else
		msg = arguments[1];
	var reg0 = /^(133|153|189|180|181|177)\d{8}$/;
	var result = false;
	if(reg0.test(obj.val()))result = true;
	if(!result){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}else
		return true;		
}



//检测身份证号码
var Wi = [ 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 ];// 加权因子
var ValideCode = [ 1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2 ];// 身份证验证位值.10代表X
function IdCardValidate(idCard){
	//idCard = trim(idCard.replace(/ /g,""));
	if(idCard.length == 15)
	{   
		return isValidityBrithBy15IdCard(idCard);   
	}
	else if(idCard.length == 18)
	{   
		var a_idCard = idCard.split("");// 得到身份证数组   
		if(isValidityBrithBy18IdCard(idCard)&&isTrueValidateCodeBy18IdCard(a_idCard))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{   
		return false;
	}
}
/**  
* 判断身份证号码为18位时最后的验证位是否正确  
* @param a_idCard 身份证号码数组  
* @return  
*/  
function isTrueValidateCodeBy18IdCard(a_idCard){   
	var sum = 0; // 声明加权求和变量   
	if (a_idCard[17].toLowerCase() == 'x'){   
		a_idCard[17] = 10;// 将最后位为x的验证码替换为10方便后续操作   
	}   
	for( var i = 0; i < 17; i++){   
		sum += Wi[i] * a_idCard[i];// 加权求和   
	}   
	valCodePosition = sum % 11;// 得到验证码所位置   
	if (a_idCard[17] == ValideCode[valCodePosition]){   
		return true;   
	}
	else
	{   
		return false;   
	}
}   

/**  
* 验证18位数身份证号码中的生日是否是有效生日  
* @param idCard 18位书身份证字符串  
* @return  
*/  
function isValidityBrithBy18IdCard(idCard18){   
	var year =  idCard18.substring(6,10);   
	var month = idCard18.substring(10,12);   
	var day = idCard18.substring(12,14);   
	var temp_date = new Date(year,parseFloat(month)-1,parseFloat(day));   
	// 这里用getFullYear()获取年份，避免千年虫问题   
	if(temp_date.getFullYear()!=parseFloat(year) || temp_date.getMonth()!=parseFloat(month)-1 || temp_date.getDate()!=parseFloat(day)){   
		return false;
	}
	else
	{   
		return true;
	}
}
/**  
* 验证15位数身份证号码中的生日是否是有效生日  
* @param idCard15 15位书身份证字符串  
* @return  
*/  
function isValidityBrithBy15IdCard(idCard15){   
	var year =  idCard15.substring(6,8);   
	var month = idCard15.substring(8,10);   
	var day = idCard15.substring(10,12);   
	var temp_date = new Date(year,parseFloat(month)-1,parseFloat(day));   
	// 对于老身份证中的你年龄则不需考虑千年虫问题而使用getYear()方法   
	if(temp_date.getYear()!=parseFloat(year) || temp_date.getMonth()!=parseFloat(month)-1 || temp_date.getDate()!=parseFloat(day)){   
		return false;   
	}
	else
	{
		return true;
	}
}
/*得到字符长度*/
function getTrueLength(myStr){
	var i,trueLength,temp;
	trueLength = 0;
	for(i = 0;i < myStr.length;i++){
		temp = myStr.charCodeAt(i);
		if(temp>127){
			trueLength = trueLength + 2;
		}else if(temp == 60|| temp == 62){
			trueLength = trueLength + 4;
		}else if(temp == 39){
			trueLength = trueLength + 2;
		}else{
			trueLength = trueLength + 1;
		}
	}
	return trueLength;
}

//not IE is required=禁止黏贴
function fncKeyStop(evt)
{
    if(!window.event)
    {
        var keycode = evt.keyCode;
        var key = String.fromCharCode(keycode).toLowerCase();
        if(evt.ctrlKey && key == "v")
        {
          evt.preventDefault();
          evt.stopPropagation();
        }
    }
}

//是否正确的手机号 仅检测不弹出框  移动号码=1 联调号=2 电信号=3 有效号=0
function isMobileChk(value,flag)
{
	var reg1 = /^(134|135|136|137|138|139|147|150|151|152|158|159|187|188|182|183|157|178)\d{8}$/;
	var reg2 = /^(130|131|132|145|155|156|185|186|176)\d{8}$/;
	var reg3 = /^(133|153|189|180|181|177)\d{8}$/;
	var reg0 = /^(134|135|136|137|138|139|147|150|151|152|158|159|187|188|182|183|157|130|131|132|145|155|156|185|186|133|153|189|180|181|184|176|177|178|170|171)\d{8}$/;//所有有效的手机号段
	var reg ;
	if( flag == 1 )
	{
		reg = reg1 ;
	}
	else if( flag == 2 )
	{
		reg = reg2 ;
	}
	else if( flag == 3 )
	{
		reg = reg3 ;
	}
	else
	{
		reg = reg0;
	}
	
	if(reg.test(value))
		return true;
	else
		return false;		
}
/*验证输入是否为中文*/
function isChinese(obj){
	if(arguments.length == 1)
		msg = "只能输入中文！";
	else
		msg = arguments[1];
	var re = /[^\u4E00-\u9FA5]/g;
	if(re.test(obj)){
		$.alerts.okButton = okButtonChineseName;
		$.alerts.ifClose = 0;
		jAlert(msg,layerTitleChineseName);
		return false;
	}
	else
		return true;
}
//验证银行卡号
function isBankCard(cardNo){
	var re = /^\d{15,20}$/;
	if(re.test(cardNo))
	{
		return true;
	}else{
		return false;
	}
}

