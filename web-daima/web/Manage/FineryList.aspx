<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FineryList.aspx.cs" Inherits="Bzw.Web.Manage.FineryList" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>
        <%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台
    </title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet"
        type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <link href="/css/lightbox.css" type="text/css" rel="stylesheet" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/topbtn.js"></script>
    <script type="text/javascript" src="/Public/Js/submu.js"></script>
    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        html
        {
            overflow-x: hidden;
            overflow-y: auto;
        }
        .plus
        {
            margin-left: 220px;
            margin-top: -140px;
            width: 415px;
            _margin-left: 110px;
            _margin-top: -215px;
        }
        .plus a
        {
            display: inline-block;
            text-align: center;
            width: 95px;
            color: #0073cc;
            font-size: 11px;
            -webkit-text-size-adjust: none;
        }
        .plus a:hover
        {
            color: #000000;
        }
        
        /*------------#prize And #props-----------------*/#prize, #props
        {
            padding: 15px 15px 0;
            float: left;
        }
        #prize dl, #props dl
        {
            width: 110px;
            height: 280px;
            float: left;
            overflow: hidden;
            text-align: center;
            border-bottom: 1px solid #cbecfb;
            margin-bottom: 20px;
        }
        #props dl
        {
            height: 150px;
        }
        #prize dt, #props dt
        {
            height: 12px;
            padding-top: 2px;
        }
        #props dd
        {
            margin-bottom: 10px;
        }
        #prize strong, #props strong
        {
            display: block;
            padding-top: 5px;
        }
        #prize dd img, #props img
        {
            width: 100px;
            height: 100px;
            overflow: hidden border: 1px solid #b6d6ec;
        }
        .btn
        {
            display: block;
            width: 106px;
            height: 34px;
            line-height: 34px;
            color: White;
            margin: 0 auto;
            background: url(/images/sub_btn01.jpg) no-repeat left top;
        }
        .red
        {
            color: Red;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu2" runat="server" />
        <div class="min_max_adap">
            <form id="form1" runat="server">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text" style="text-align: left;">
                            <a href="/daoju.aspx" style="font-size: 14px;">道具商城</a> &nbsp;|&nbsp; <a style="font-size: 14px;
                                color: #000; font-weight: 500" href="/Manage/Finerylist.aspx">精品ID</a>
                        </div>
                    </div>
                    <div class="totalBd">
                        <div id="content01" style="width: 861px; margin: 0px; padding: 0px; clear: both;
                            padding-left: 50px; overflow: hidden; text-align: left; float: left;">
                            <div id="sub_nr">
                                <div id="idss">
                                    <label>
                                        <img src="/Images/id01.jpg" alt="" /></label>
                                    <input type="text" size="50" class="in" runat="server" name="seachid" id="seachid" />
                                    <asp:ImageButton ImageUrl="/Images/cont_btn04.jpg" runat="server" ID="BtnSeach" OnClick="BtnSeach_Click" />
                                </div>
                                <div id="tjlh">
                                    <ul>
                                        <asp:Repeater ID="FineryIDTop" runat="server">
                                            <ItemTemplate>
                                                <ul>
                                                    <li><strong class="text05">ID:<a href='/Manage/FineryIDSale.aspx?id=<%#Eval("FineryID") %>'
                                                        class="link02"><%#Eval("FineryID") %></a></strong><br />
                                                        价格：
                                                        <%#UiCommon.StringConfig.AddZeros(Eval("Price")) %>金币 </li>
                                                </ul>
                                            </ItemTemplate>
                                        </asp:Repeater>
                                        <asp:Label runat="server" Text="暂无推荐" ID="NoProTop" Visible="false"></asp:Label>
                                    </ul>
                                </div>
                                <div id="gz">
                                    <strong class="text05"><strong class="text05">规则</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                        <a href="/Manage/FineryList.aspx?type=all" id="all" class="link03">全部</a> &nbsp;|&nbsp;
                                        <a href="/Manage/FineryList.aspx?type=aabb" id="aabb" class="link03">AABB</a> &nbsp;|&nbsp;
                                        <a href="/Manage/FineryList.aspx?type=aabbcc" id="aabbcc" class="link03">AABBCC</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=abab" id="abab" class="link03">ABAB</a>&nbsp;
                                        |&nbsp; <a href="/Manage/FineryList.aspx?type=ababab" id="ababab" class="link03">ABABAB</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=abcabc" id="abcabc" class="link03">ABCABC</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=abgab" id="abgab" class="link03">ABGAB</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=3a" id="3a" class="link03">3A</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=4a" id="4a" class="link03">4A</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=5a" id="5a" class="link03">5A及以上</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=4sun" id="4sun" class="link03">4顺及以上</a>&nbsp;
                                        | &nbsp;<a href="/Manage/FineryList.aspx?type=date" id="date" class="link03">生日</a>
                                </div>
                                <div id="jplh">
                                    <p>
                                        <strong class="text05">精品靓号</strong> <strong>您可以在页面上方的搜索框输入您想要找的号码，也可以看看我们推荐的精品靓号。</strong></p>
                                    <ul>
                                        <asp:Repeater ID="FineryIDList" runat="server">
                                            <ItemTemplate>
                                                <li><strong class="text05">ID&nbsp;&nbsp;&nbsp;&nbsp;：<a href='/Manage/FineryIDSale.aspx?id=<%#Eval("FineryID") %>'
                                                    class="link02"><%#Eval("FineryID") %></a></strong><br />
                                                    价格：<%# UiCommon.StringConfig.AddZeros(Eval("Price")) %><%=UiCommon.StringConfig.MoneyName %>
                                                </li>
                                            </ItemTemplate>
                                        </asp:Repeater>
                                        <asp:Label ID="NoProList" Visible="False" ForeColor="Red" runat="server"></asp:Label>
                                    </ul>
                                </div>
                            </div>
                            <div class="sabrosus">
                                <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                    FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                                    ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                                    TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                                    CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="12">
                                </webdiyer:AspNetPager>
                            </div>
                            <p>
                                &nbsp;</p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="mask" style="display: none;" id="mask">
            </div>
            <div class="serviceIbox popup png" style="display: none;" id="servicePopup">
                <div class="service">
                    <div class="iboxClose">
                        <a class="popupCloseTrigger png" href="javascript:;"></a>
                    </div>
                    <div class="serviceQQ">
                        &nbsp;
                    </div>
                </div>
                <div class="serviceBottom">
                </div>
            </div>
            <div class="rechargeIbox popup png" style="display: none;" id="rechargePopup">
            </div>
            <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
            <script src="/js/scroll.js" type="text/javascript"></script>
            <!--[if IE 6]>
    <script src="/js/DD_belatedPNG.js"></script>
    <script>
        fixPng();
        function fixPng()
        {
            DD_belatedPNG.fix('.png');
	        $(function(){
		        $('a.for56ie6 img,a.for68ie6 img,a.for32ie6 img').each(function(){
			        var $i = $('<i>');
			        $(this).replaceWith($i);
			        $i.attr('style', 'cursor:pointer;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod="scale",src="'+ $(this).attr('src') +'");background-image:none;');
		        });
	        });
        }
    </script>
    <![endif]-->
            </form>
        </div>
    </div>
</body>
</html>
