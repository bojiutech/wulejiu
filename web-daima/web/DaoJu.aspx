<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJu" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>
        <%= SiteConfig.GetParaValue("Title")%>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta name="Description" content="<%= SiteConfig.GetParaValue("Title")%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%= SiteConfig.GetParaValue("Title")%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%= SiteConfig.GetParaValue("Title")%>游戏,<%= SiteConfig.GetParaValue("Title")%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
        <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/DaoJu.js"></script>
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
        <uc1:NewMenu ID="NewMenu1" runat="server" />
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
                            <a href="/daoju.aspx" style="color: #000; font-size: 14px; font-weight: 500">道具商城</a>
                            &nbsp;|&nbsp; <a style="font-size: 14px;" href="/Manage/Finerylist.aspx">精品ID</a>
                        </div>
                    </div>
                    <div class="totalBd" style="background-color: #bedff6;">
                        <div id="sub_nr" style="margin-top: 10px;">
                            <div id="dhzx" style="width: 800px; overflow: hidden;">
                                <asp:Repeater ID="rpDaoJu" runat="server">
                                    <ItemTemplate>
                                        <dl>
                                            <dd>
                                                <img src="Image/DaoJu/<%#Eval("PropID") %>.gif" width="136" height="82" alt="<%#Eval("PropName") %>" /></dd>
                                            <dt class="text05">
                                                <%#Eval("PropName") %></dt>
                                            <dt>
                                                <input name="" type="button" value="赠 送" class="shop_but_01" onclick="javascript:location.href='/DaoJuZS.aspx?id=<%#Eval("PropID") %>'" />
                                                <input name="" type="button" value="购 买" class="shop_but_02" onclick="javascript:location.href='/DaoJuGM.aspx?id=<%#Eval("PropID") %>'" />
                                            </dt>
                                        </dl>
                                    </ItemTemplate>
                                </asp:Repeater>
                                <!--pageNumber-->
                                <div class="sabrosus">
                                    <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                        FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                                        ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                                        TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                                        CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="10">
                                    </webdiyer:AspNetPager>
                                </div>
                            </div>
                            <div class="clear">
                            </div>
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
