<%@ Control Language="C#" AutoEventWireup="true" Codebehind="Top.ascx.cs" Inherits="DataAnaly.Analy.Top" %>
<script type="text/javascript" language="javascript" src="/Public/Js/jquery.js"></script>
<script type="text/javascript" language="javascript" src="/Public/Js/analy.js"></script>
<div id="top">
	<div id="logo" style="display:none;">
		<img src="/Analy/Images/analy/logo.gif" width="120" height="42" alt="正易龙" /></div>
	<div class="title">
		
	</div>
	<div class="date">
		<%=UiCommon.AnalyLoginInfo.Default.UserName%>，&nbsp;&nbsp;欢迎您！&nbsp;&nbsp;<a href="/Analy/Default.aspx">系统首页</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a
			href="javascript:void(0);" onclick="AdminEditMe();" title="修改自己的密码等资料">修改密码</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a
				href="/Analy/LoginOut.aspx" title="退出登录">退出登录</a>
	</div>
	<div id="nav">
    <ul class="sf-menu">
	<li><a href="javascript:void(0);" title="在线玩家分析中心">在线玩家分析中心</a>
		<ul>
			<li><a href="/Analy/Online2/OnlineUser_Date.aspx" title="在线人数统计">在线人数统计</a></li>
			<li><a href="/Analy/Online/OnlineUsers.aspx?type=0" title="当前在线人数">当前在线玩家</a></li>
			<li><a href="/Analy/Online/OnlineUsers.aspx?type=1" title="在线机器人列表">当前在线机器人</a> </li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="在线人数中心">新玩家分析中心</a>
		<ul>
			<li><a href="/Analy/NewUser/DateReport.aspx" title="新玩家每日数据统计">每日数据统计</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=0" title="注册详细列表">注册详细列表</a></li>
			<li><a href="/Analy/NewUser/UserLoginList.aspx" title="登录游戏列表">登录游戏列表</a></li>
			<li><a href="/Analy/NewUser/PayList.aspx" title="新玩家充值记录">新玩家充值记录</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="在线人数中心">记录列表分析中心</a>
		<ul>
			<li><a href="/Analy/Records/UserLoginList.aspx" title="登陆游戏记录">登陆游戏记录</a></li>
			<li><a href="/Analy/Records/ActiveList.aspx" title="活跃玩家记录">活跃玩家记录</a></li>
			<li><a href="/Analy/Records/PayList.aspx" title="用户充值记录">玩家充值记录</a></li>
			<li><a href="/Analy/Records/GameRecord.aspx" title="玩家游戏记录">玩家游戏记录</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=2" title="注册24小时后登陆游戏玩家">注册24小时后登陆游戏玩家</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=1" title="注册24小时内登陆过游戏玩家">注册24小时内登陆过游戏玩家</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="数据统计中心">运营数据统计中心</a>
		<ul>
			<li><a href="/Analy/Report/LoopMoneyReport.aspx" title="金币流通统计">金币流通统计</a></li>
			<li><a href="/Analy/Report/DateReport.aspx" title="每日数据统计">每日数据统计</a></li>
			<li><a href="/Analy/Report/MonthReport2.aspx" title="每月数据统计">每月数据统计</a></li>
			<li><a href="/Analy/Report/AgencyRegReport.aspx" title="每日注册统计">每日注册统计</a></li>
			<li><a href="/Analy/Report/PayReport.aspx" title="每日充值统计">每日充值统计</a></li>
			<li><a href="/Analy/Report/GameTaxReport.aspx" title="每日抽水统计">每日抽水统计</a></li>
			<li><a href="/Analy/Report/GameCountReport.aspx" title="每日游戏局数统计">每日游戏局数统计</a></li>
			<li><a href="/Analy/Report/AgencyDateReport.aspx" title="代理商每日数据统计">代理商每日数据统计</a></li>
			<li><a href="/Analy/Report/GameCountAndTaxReport.aspx" title="游戏局数及抽水统计">游戏局数及抽水统计</a></li>
			<li><a href="/Analy/Report/AgencyUsers.aspx" title="代理商直属玩家注册统计">代理商直属玩家注册统计</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="图形数据分析中心">图形数据分析中心</a>
		<ul>
			<li><a href="/Analy/Chart/DateChart.aspx?type=0" title="每日数据分析">每日数据分析</a></li>
			<li><a href="/Analy/Chart/DateChart.aspx?type=1" title="新玩家每日数据分析">新玩家每日数据分析</a></li>
			<li><a href="/Analy/Chart/Chart.aspx?type=0" title="每日时间点数据分析">每日时间点数据分析</a></li>
			<li><a href="/Analy/Chart/Chart.aspx?type=1" title="新玩家每日时间点数据分析">新玩家每日时间点数据分析</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="系统管理">系统管理</a>
		<ul>
			<li><a href="/Analy/Config.aspx" title="参数设置">参数设置</a></li>
			<li><a href="javascript:void(0);" onclick="AdminEditMe();" title="修改密码">修改密码</a></li>
			<li><a href="/Analy/Default.aspx" title="系统首页">系统首页</a></li>
		</ul>
	</li>
</ul>
	</div>

	<script type="text/javascript">
		$(document).ready(
			function()
			{
				//$.get(
					//"/Analy/Menu.aspx?x=" + Math.random(),
					//function(data)
					//{
						//if(data != null && data != "")
						//{
							//$("div#nav").html(data);
							jQuery(function()
							{
								if (jQuery('ul.sf-menu'))
									jQuery('ul.sf-menu').superfish({ speed: 20, delay: 500 }); //页面一加载完成立即初始化菜单
							});
						//}
		//} //读取菜单
					
				//);
			}
		);
	</script>

</div>
