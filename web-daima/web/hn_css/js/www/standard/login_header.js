$('#logining').html("<div class=\"loadingN\"><img src=\"http://hn_img/images/newIndex/201008/loadingN.gif\" alt=\"���ݼ�����\" /></div>");
var url = "http://a3.act.jj.cn/www/login_common.php?callback=?";
$.ajax({	   
	url: url,
	type: "get",
	dataType: "jsonp",
	jsonp: "callback",
	cache: false,
	success: function(json){
		if(json.user_login_state == 1)
		{	
			login_html ='<div class="ld">';
			login_html +='<div class="n">';
			login_html +='<div onmouseover="javascript:this.className=\'hov\';" onmouseout="javascript:this.className=\'\';">';
			login_html +='<a class="i" href="http://my.jj.cn/account/honour.php"><em><img src="http://header.jj.cn/'+json.user_id+'/" /></em><span>'+json.user_nick+'</span></a>';
            login_html +='<ul class="n_in">';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/account/honour.php">������</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://t.jj.cn">����˵˵</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/money/change.php">�һ����</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/goods/present.php">��Ʒ����</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/money/getgold.php">��ȡ���</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/goods/compose.php">�ϳ�¯</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://my.jj.cn/money/coffer.php">������</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://my.jj.cn/msg.php">��Ϣ</a> <span class="t">'+json.user_msg_nums+'</span></li>';
			login_html +='<li><a href="http://jj.cn/user/logout.php">�˳�</a></li>';
			login_html +='</ul>';
			login_html +='</div>';
			login_html +='</div>';
			login_html +='<a class="c" href="http://pay.jj.cn/">��ֵ</a>';
			login_html +='</div>';
		}
		else
		{
			login_html  = '<div class="lg">[<a href="http://login.jj.cn/user/login.php">��¼</a>]<a href="http://my.jj.cn/securityCenter/pwdComplaint.php" target="_blank">��������?</a> [<a href="http://www.jj.cn/reg/reg.html" target="_blank">ע��</a>]</div>';
		}
		
		$('#logining').html(login_html);
	},
	error:function(msg){
		$('#logining').html("<div css='arr'>����ʧ��,��ˢ������</div>");
	}
});
