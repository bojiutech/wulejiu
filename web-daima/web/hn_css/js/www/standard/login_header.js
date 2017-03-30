$('#logining').html("<div class=\"loadingN\"><img src=\"http://hn_img/images/newIndex/201008/loadingN.gif\" alt=\"数据加载中\" /></div>");
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
			login_html +='<li><a target="_blank" href="http://my.jj.cn/account/honour.php">荣誉室</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://t.jj.cn">进入说说</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/money/change.php">兑换金币</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/goods/present.php">物品赠送</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/money/getgold.php">领取金币</a></li>';
			login_html +='<li><a target="_blank" href="http://my.jj.cn/goods/compose.php">合成炉</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://my.jj.cn/money/coffer.php">保险箱</a></li>';
			login_html +='<li class="l"><a target="_blank" href="http://my.jj.cn/msg.php">消息</a> <span class="t">'+json.user_msg_nums+'</span></li>';
			login_html +='<li><a href="http://jj.cn/user/logout.php">退出</a></li>';
			login_html +='</ul>';
			login_html +='</div>';
			login_html +='</div>';
			login_html +='<a class="c" href="http://pay.jj.cn/">充值</a>';
			login_html +='</div>';
		}
		else
		{
			login_html  = '<div class="lg">[<a href="http://login.jj.cn/user/login.php">登录</a>]<a href="http://my.jj.cn/securityCenter/pwdComplaint.php" target="_blank">忘记密码?</a> [<a href="http://www.jj.cn/reg/reg.html" target="_blank">注册</a>]</div>';
		}
		
		$('#logining').html(login_html);
	},
	error:function(msg){
		$('#logining').html("<div css='arr'>加载失败,请刷新重试</div>");
	}
});
