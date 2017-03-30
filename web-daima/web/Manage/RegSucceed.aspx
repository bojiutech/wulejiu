<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="RegSucceed.aspx.cs" Inherits="Bzw.Web.Manage.RegSucceed" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
       <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/password_check.js"></script>
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
</head>
<body>
   <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
    <div class="bgBox">
        <img src="/images/Bg2.jpg" />
    </div>
    <div class="wrap">
        <div class="header">
            <div class="mainNav " id="mainNav">
                <uc1:NewMenu ID="NewMenu1" runat="server" />
            </div>
            <a href="/index.aspx">
                <div class="logo png">
                </div>
            </a>
        </div>
        <div class="totalContent">
            <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                overflow: hidden; height: 62px;">
                <i class="ico_67 i1 newsNotice png"></i>
                <div id='noticetime' class="time">
                    <span></span>
                </div>
                <div class="text" style="font-size: 14px;">
                  注册成功！
                </div>
            </div>
            <div class="totalBd">
                <div class="totalTabc png" style="width: 100%;">
                    <div class="totalsubContent" style="height: 560px; width: 95%;">
                        <div class="scrollBg">
                            <div style="top: 1px;" class="scroll">
                            </div>
                        </div>
                        <div class="scrollBg">
                            <div class="scroll" style="top: 174px;">
                            </div>
                        </div>
                        <div id="newsContent" class="content newsNotice vscrollTrigger" style="overflow-y: hidden;
                            height: 550px; width: 90%;">
                      
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    注册</h3>
                <p class="dqwz">
                    当前位置：首页 > 注册成功</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <div style="padding: 10px; width: 90%; border: 1px solid #ece9d8; text-align: left;
                        overflow: hidden;">
                        <div style="margin: 0px auto; padding: 10px; width: 95%; text-align: center; overflow: hidden;">
                            <span style="font-size: 14px; font-weight: 700">恭喜注册成功！</span><br />
                        </div>

                        <div style=" text-align:right;width: 50%; text-align: left; overflow: hidden;  margin-left:255px">
                        帐号为： <span runat="server" id="span1"></span>
                        <br />
                        密码为： <span runat="server" id="span2"></span>
                        <br />
                        进入&nbsp;<a style="color: Blue;" href="/Manage/index.aspx">个人中心</a> <span runat="server"
                            id="span_rs"></span>

                            </div>
                    </div>
                    <br/>
                                        <br/>
                </div>
            </div>
            <p>
                &nbsp;</p>
       
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
</body>
</html>
