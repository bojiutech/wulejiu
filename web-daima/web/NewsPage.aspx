<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="NewsPage.aspx.cs" Inherits="Bzw.Web.NewsPage" %>

<%@ Register Src="Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
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
    </style>
    <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
    <script src="js/jsScroller.js" type="text/javascript"></script>
    <script src="js/jsScrollbar.js" type="text/javascript"></script>
    <script type="text/javascript">
        var scroller = null;
        var scrollbar = null;
        window.onload = function () {
            scroller = new jsScroller(document.getElementById("Scroller-1"), 400, 500);
            scrollbar = new jsScrollbar(document.getElementById("Scrollbar-Container"), scroller, false);
        }
    </script>
    <style type="text/css">
        .Container
        {
            float: left;
            top: 50px;
            left: 100px;
            width: 98%;
            height: 500px;
        }
        #Scroller-1
        {
            position: absolute;
            overflow: hidden;
            width: 100%;
            height: 500px;
        }
        #Scroller-1 p
        {
            margin: 0;
            padding: 10px 20px;
            text-indent: 20px;
            font-size: 14px;
            color: #10375b;
            padding-bottom: 22px;
        }
        .Scroller-Container
        {
            position: absolute;
            top: 0px;
            left: 0px;
            padding-top: 40px;
        }
        .Scrollbar-Track
        {
            width: 10px;
            position: absolute;
            top: 75px;
            left: 98%;
            background-color: #EEE;
            position: absolute;
            background: url(/images/structureGif.gif) no-repeat;
            background-position: -490px 0;
            width: 10px;
            height: 307px;
            right: 1px;
            top: 4px;
            z-index: 2;
        }
        .Scrollbar-Handle
        {
            position: absolute;
            top: 0px;
            left: 0px;
            width: 10px;
            height: 30px;
            background-color: #CCC;
            position: absolute;
            background: url(/images/structureGif.gif) no-repeat;
            background-position: -470px 0;
            width: 8px;
            height: 132px;
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
                        <div class="text" style="font-size: 14px;">
                            <%=NewTitle %>
                        </div>
                    </div>
                    <div class="totalBd " style="background: url(/images/newsRightBg.png) repeat-x;">
                        <div class="Container">
                            <div id="Scroller-1">
                                <div class="Scroller-Container ">
                                    <%=NewContent %>
                                </div>
                            </div>
                        </div>
                        <div id="Scrollbar-Container">
                            <div class="Scrollbar-Track">
                                <div class="Scrollbar-Handle">
                                </div>
                            </div>
                        </div>
                        <div class="totalTabc png" style="width: 100%; display: none;">
                            <div class="totalsubContent" style="height: 560px; width: 95%;">
                                <div id="newsContent" class="content newsNotice vscrollTrigger" style="overflow-y: hidden;
                                    height: 550px; width: 90%;">
                                    <%=NewContent %>
                                </div>
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
