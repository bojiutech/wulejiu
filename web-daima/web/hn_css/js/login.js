function checkinput(){
	if($("#username").val() == ""){
		$("#username").focus();
		alert("用户名不能为空！");
		return false;
	}
	if($("#password").val() == ""){
		$("#password").focus();
		alert("密码不能为空！");
		return false;
	}else
		return true;
}

$('#login').html("<div class=\"loadingN\"><img src=\"http://hn_img/images/newIndex/201008/loadingN.gif\" alt=\"数据加载中\" /></div>");
var url = "http://www.jj.cn/ajax/login_common.php?callback=?";

$.ajax({	   
	url: url,
	type: "get",
	dataType: "jsonp",
	jsonp: "callback",
	cache: false,
	success: function(json){
		if(json.user_login_state == 1)
		{
			login_html  = "<ul class=\"Fy\">\n";
			login_html += "<li onmouseout=\"document.getElementById('Fy01').style.display = 'none';\" onmouseover=\"document.getElementById('Fy01').style.display = 'block';\" >\n";
			login_html += "<div class=\"X\">\n";
			login_html += "<a href=\"http://my.jj.cn/account/honour.php\" title=\"进入我的荣誉室\"><span class=\"pImg\"><img src=\""+json.user_head_url+"\" /></span>"+json.user_nick+"</a>\n";
			login_html += "</div>\n";
			login_html += "<span class=\"pImgTop\"></span>\n";
			login_html += "<div id=\"Fy01\" class=\"L\">\n";
			login_html += "<div class=\"T1\"><b></b></div>\n";
			login_html += "<div class=\"LR LR01\">\n";
			login_html += "<div class=\"Go\">\n";
			login_html += "<div class=\"GoTo\"></div>\n";
			login_html += "<span class=\"GoDi\"><img src=\""+json.user_head_url+"\"/></span>\n";
			login_html += "<a class=\"Gf\" href=\"http://my.jj.cn/account/account.php\">更换头像</a>\n";
			login_html += "</div>\n";
			login_html += "<dl class=\"Dl01\">\n";
			login_html += "<dt><b><a href=\"http://my.jj.cn/account/honour.php\">进入荣誉室</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://"+json.user_id+".show.jj.cn/article/\">日志</a></b><span><a href=\"http://"+json.user_id+".show.jj.cn/article/action_write/\">发表</a></span></dt>\n";
			login_html += "<dt><b><a href=\"http://"+json.user_id+".show.jj.cn/album_list/\">相册</a></b><span><a href=\"http://"+json.user_id+".show.jj.cn/photo_upload/\">上传</a></span></dt>\n";
			/*login_html += "<dt><b><a href=\"http://"+json.user_id+".show.jj.cn/friends/\">好友</a></b><span><a href=\"http://"+json.user_id+".show.jj.cn/friends/\">管理</a></span></dt>\n";*/
			login_html += "<dt><b><a href=\"http://t.jj.cn/\">说说</a></b><span><a href=\"http://t.jj.cn/\">更新</a></span></dt>\n";
			login_html += "<dt style=\"border-bottom:none;\"><b><a href=\"http://"+json.user_id+".show.jj.cn/leavemsg/\">留言</a></b><span><a href=\"http://"+json.user_id+".show.jj.cn/leavemsg/\">查看</a></span></dt>\n";
			login_html += "</dl>\n";
			login_html += "</div>\n";
			login_html += "</div>\n";
			login_html += "</li>\n";
			login_html += "<li onmouseout=\"document.getElementById('Fy02').style.display = 'none';\" onmouseover=\"document.getElementById('Fy02').style.display = 'block';\" >\n";
			login_html += "<div class=\"X\"><a href=\"http://my.jj.cn/\" title=\"进入我的JJ\"><img src=\"http://hn_img/images/newIndex/201008/topdn02.gif\" /></a></div>\n";
			login_html += "<div id=\"Fy02\" class=\"L\">\n";
			login_html += "<div class=\"T1\"><b></b></div>\n";
			login_html += "<div class=\"LR\">\n";
			login_html += "<dl class=\"Dl02\">\n";
			login_html += "<dt><b><a href=\"http://my.jj.cn/money/change.php\">兑换金币</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://my.jj.cn/money/coffer.php\">保 险 箱</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://my.jj.cn/money/getgold.php\">领取金币</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://my.jj.cn/goods/compose.php\">合 成 炉</a></b></dt>\n";
			login_html += "<dt style=\"border-bottom:none;\"><b><a href=\"http://my.jj.cn/goods/present.php\">物品赠送</a></b></dt>\n";
			login_html += "</dl>\n";
			login_html += "</div>\n";
			login_html += "</div>\n";
			login_html += "</li>\n";
			if(json.is_join_club == 1)
			{
			login_html += "<li onmouseout=\"document.getElementById('Fy03').style.display = 'none';\" onmouseover=\"document.getElementById('Fy03').style.display = 'block';\" >\n";
			login_html += "<div class=\"X\"><a href=\"http://club.jj.cn/interface.php\" title=\"进入我的公社\"><img src=\"http://hn_img/images/newIndex/201008/topdn04.gif\" /></a></div>\n";
			login_html += "<div id=\"Fy03\" class=\"L\">\n";
			login_html += "<div class=\"T1\"><b></b></div>\n";
			login_html += "<div class=\"LR\">\n";
			login_html += "<dl class=\"Dl03\">\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/interface.php\">我的公社</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/member_dynamic.php\">公社动态</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/admin/contributions.php\">公社财务</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/commune_info.php\">公社详情</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/match_list.php\">内部赛事</a></b></dt>\n";
			login_html += "<dt><b><a href=\"http://club.jj.cn/message.php\">公社告示</a></b></dt>\n";
			login_html += "<dt style=\"border-bottom:none;\"><b><a href=\"http://club.jj.cn/faq.php\">公社指南</a></b></dt>\n";
			login_html += "</dl>\n";
			login_html += "</div>\n";
			login_html += "</div>\n";
			login_html += "</li>\n";
			}
			login_html += "<li>\n";
			login_html += "<div class=\"X\"><a id=\"top_no_read_msg_title\" href=\"http://my.jj.cn/msg.php\" title=\"我共有 "+json.user_msg_nums+" 条未读信息\"><img src=\"http://hn_img/images/newIndex/201008/topdn03.gif\" /><b id=\"top_no_read_msg_num_3\">"+json.user_msg_nums+"</b></a></div>\n";
			login_html += "</li>\n";
			login_html += "</ul>\n";
			login_html += "<ul class=\"Bu\">\n";
			login_html += "<li><a href=\"http://pay.jj.cn/\"><img src=\"http://hn_img/images/newIndex/201008/czbut.gif\" alt=\"充值\" /></a></li>\n";
			login_html += "<li><a href=\"http://jj.cn/user/logout.php\"><img src=\"http://hn_img/images/newIndex/201008/dropout.gif\" alt=\"退出\"/></a></li>\n";
			login_html += "</ul>\n";
		}
		else
		{
			login_html  = "<form method=\"post\" name=\"input\" id=\"input\" onsubmit=\"return checkinput()\" action=\"http://jj.cn/user/loginact.php\">\n";
			login_html += "<ul class=\"Lo\">\n";
			login_html += "<li class=\"li1\">用户:</li>\n";
			login_html += "<li class=\"li2\"><input id=\"username\" name=\"username\" type=\"text\"/></li>\n";
			login_html += "<li class=\"li3\">密码:</li>\n";
			login_html += "<li class=\"li4\"><input id=\"password\" name=\"password\" type=\"password\"/></li>\n";
			login_html += "<li class=\"li5\"><button type=\"submit\"></button></li>\n";
			login_html += "<li class=\"li6\"><a href=\"http://www.jj.cn/reg/reg.html\"><img src=\"http://hn_img/images/newIndex/201008/loginbut.gif\" alt=\"注册成为JJ玩家\"/></a></li>\n";
			login_html += "</ul>\n";
			login_html += "</form>\n";
			login_html += "<ul class=\"Bu\">\n";
			login_html += "<li><a href=\"http://pay.jj.cn/\"><img src=\"http://hn_img/images/newIndex/201008/czbut.gif\" alt=\"充值\" /></a></li>\n";
			login_html += "</ul>\n";
		}
		
		$('#login').html(login_html);
	},
	error:function(msg){
		$('#login').html("<div class=\"loadingN\">数据加载失败,请刷新当前页面重试.</div>");
	}
});
