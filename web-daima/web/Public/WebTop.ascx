<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebTop.ascx.cs" Inherits="Bzw.Web.Public.WebTop" %>
<script type="text/javascript" src="/Public/Js/jquery.js"></script>
<script type="text/javascript" src="/Public/Js/common.js"></script>
<script language="javascript" type="text/javascript">
    $().ready(function () {
        var span_name = $('#span_name');
        if (span_name != null) {
            var s = span_name.text();
            if (s != null && s.length > 6) {
                span_name.text(s.substr(0, 6));
            }
        }
    });
</script>
<div id="header">
    <div id="h_topcontent">
        <ul>
            <li class="h_logo">
                <img src="/images/logo.gif" /></li>
            <li class="h_call" style="color: Black">
                <img src="/images/call.gif" /></li>
            <%if (UiCommon.UserLoginInfo.IsLogin)
              { %>
            <li class="h_topnav"><span id="span_name" title='<%=UiCommon.UserLoginInfo.UserName %>'  style="color: Red;"><%=UiCommon.UserLoginInfo.UserName %>&nbsp;</span>
              | | <a href="/Manage/Default.aspx">
                    管理中心</a> &nbsp;|&nbsp;<a onclick="return confirm('确认退出登录吗？')" href="/Public/Logout.aspx">退出</a></li>
            <%

                }
              else
              {%>
            <li class="h_topnav"><a href="/Manage/Login.aspx">登录</a> 或 <a href="/Manage/Reg.aspx">
                注册</a></li>
            <%} %>
        </ul>
    </div>
    <div id="nav">
        <ul>
            <li class="last"><a href="/Default.aspx" <%= pageType==1?"class=\"current\"":"" %>>首 页</a></li>
            <li><a href="/Down.aspx" <%= pageType==2?"class=\"current\"":"" %>>游戏下载</a></li>
            <!--<li><a href="/Manage/FineryID.aspx"  <%= pageType==3?"class=\"current\"":"" %>>精品ID</a></li>-->
            <li><a href="/Manage/ClothList.aspx?type=" <%= pageType==3?"class=\"current\"":"" %>>
                服装道具</a></li>
            <li><a <%= pageType==4?"class=\"current\"":"" %> href="/Manage/Pay/Yeepay2/Default.aspx">
                帐户充值</a></li>
            <li><a href="/NewsList.aspx" <%= pageType==5?"class=\"current\"":"" %>>新闻中心</a></li>
            <li><a href="/Promoter.aspx" <%= pageType==6?"class=\"current\"":"" %>>推广员</a></li>
            <li><a href="/RankGameTime2.aspx" <%= pageType==7?"class=\"current\"":"" %>>排行榜</a></li>
            <li><a href="/JiangPin.aspx" <%= pageType==8?"class=\"current\"":"" %>>兑奖中心</a></li>
            <li ><a href="/Service.aspx" <%= pageType==9?"class=\"current\"":"" %>>客服中心
            </a></li>
            <li ><a href="/News2.aspx?id=43" <%= pageType==9?"class=\"current\"":"" %>>
                公司简介 </a></li>
        </ul>
    </div>
</div>
