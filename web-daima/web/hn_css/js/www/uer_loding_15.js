$.ajax({	   
	url: "http://a3.act.jj.cn/www/login_common.php?callback=?",
	type: "get",
	dataType: "jsonp",
	jsonp: "callback",
	cache: false,
	success: function(json){
		if(json.user_login_state == 1){
			$("#usr_loding").html("<span class='nh'>��ã�</span><a class='name' href='http://my.jj.cn/account/honour.php' target='_blank'>"+json.user_nick+"</a>��<a href='http://jj.cn/user/logout.php'>�˳�</a>")
		}else{
			$("#usr_loding").html("<a href='http://login.jj.cn/user/login.php'>[ ��¼ ]</a>��<a href='http://www.jj.cn/reg/reg.html' target='_blank'>[ ע�� ]</a>")
		}
	},
	error:function(msg){
		$("#usr_loding").html("����ʧ��");
	}
});