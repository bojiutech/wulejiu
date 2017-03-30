var okButtonChineseName = "ȷ��";
var layerTitleChineseName = "��ʾ";

function isNotEmpty(obj){
	if(arguments.length == 1)
		msg = "�������Ϊ�գ�";
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

/*���벻��Ϊ0*/
function isNotZero(obj){
	if(arguments.length == 1)
		msg = "�������Ϊ�㣡";
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

/*��֤�ƶ��ֻ����������Ƿ���ȷ*/
function isYdMobile(obj){
	if(arguments.length == 1)
		msg = "�ֻ������ʽ����ȷ��";
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
/*��֤��ͨ�ֻ����������Ƿ���ȷ*/
function isLtMobile(obj){
	if(arguments.length == 1)
		msg = "�ֻ������ʽ����ȷ��";
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

//��֤�����ֻ����������Ƿ���ȷ
function isDxMobile(obj){
	if(arguments.length == 1)
		msg = "�ֻ������ʽ����ȷ��";
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



//������֤����
var Wi = [ 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 ];// ��Ȩ����
var ValideCode = [ 1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2 ];// ���֤��֤λֵ.10����X
function IdCardValidate(idCard){
	//idCard = trim(idCard.replace(/ /g,""));
	if(idCard.length == 15)
	{   
		return isValidityBrithBy15IdCard(idCard);   
	}
	else if(idCard.length == 18)
	{   
		var a_idCard = idCard.split("");// �õ����֤����   
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
* �ж����֤����Ϊ18λʱ������֤λ�Ƿ���ȷ  
* @param a_idCard ���֤��������  
* @return  
*/  
function isTrueValidateCodeBy18IdCard(a_idCard){   
	var sum = 0; // ������Ȩ��ͱ���   
	if (a_idCard[17].toLowerCase() == 'x'){   
		a_idCard[17] = 10;// �����λΪx����֤���滻Ϊ10�����������   
	}   
	for( var i = 0; i < 17; i++){   
		sum += Wi[i] * a_idCard[i];// ��Ȩ���   
	}   
	valCodePosition = sum % 11;// �õ���֤����λ��   
	if (a_idCard[17] == ValideCode[valCodePosition]){   
		return true;   
	}
	else
	{   
		return false;   
	}
}   

/**  
* ��֤18λ�����֤�����е������Ƿ�����Ч����  
* @param idCard 18λ�����֤�ַ���  
* @return  
*/  
function isValidityBrithBy18IdCard(idCard18){   
	var year =  idCard18.substring(6,10);   
	var month = idCard18.substring(10,12);   
	var day = idCard18.substring(12,14);   
	var temp_date = new Date(year,parseFloat(month)-1,parseFloat(day));   
	// ������getFullYear()��ȡ��ݣ�����ǧ�������   
	if(temp_date.getFullYear()!=parseFloat(year) || temp_date.getMonth()!=parseFloat(month)-1 || temp_date.getDate()!=parseFloat(day)){   
		return false;
	}
	else
	{   
		return true;
	}
}
/**  
* ��֤15λ�����֤�����е������Ƿ�����Ч����  
* @param idCard15 15λ�����֤�ַ���  
* @return  
*/  
function isValidityBrithBy15IdCard(idCard15){   
	var year =  idCard15.substring(6,8);   
	var month = idCard15.substring(8,10);   
	var day = idCard15.substring(10,12);   
	var temp_date = new Date(year,parseFloat(month)-1,parseFloat(day));   
	// ���������֤�е����������迼��ǧ��������ʹ��getYear()����   
	if(temp_date.getYear()!=parseFloat(year) || temp_date.getMonth()!=parseFloat(month)-1 || temp_date.getDate()!=parseFloat(day)){   
		return false;   
	}
	else
	{
		return true;
	}
}
/*�õ��ַ�����*/
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

//not IE is required=��ֹ���
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

//�Ƿ���ȷ���ֻ��� ����ⲻ������  �ƶ�����=1 ������=2 ���ź�=3 ��Ч��=0
function isMobileChk(value,flag)
{
	var reg1 = /^(134|135|136|137|138|139|147|150|151|152|158|159|187|188|182|183|157|178)\d{8}$/;
	var reg2 = /^(130|131|132|145|155|156|185|186|176)\d{8}$/;
	var reg3 = /^(133|153|189|180|181|177)\d{8}$/;
	var reg0 = /^(134|135|136|137|138|139|147|150|151|152|158|159|187|188|182|183|157|130|131|132|145|155|156|185|186|133|153|189|180|181|184|176|177|178|170|171)\d{8}$/;//������Ч���ֻ��Ŷ�
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
/*��֤�����Ƿ�Ϊ����*/
function isChinese(obj){
	if(arguments.length == 1)
		msg = "ֻ���������ģ�";
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
//��֤���п���
function isBankCard(cardNo){
	var re = /^\d{15,20}$/;
	if(re.test(cardNo))
	{
		return true;
	}else{
		return false;
	}
}

