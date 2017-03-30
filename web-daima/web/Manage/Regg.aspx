<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Regg" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>
        <%=ConfigurationManager.AppSettings["sitename"].ToString()%>
        网络游戏世界___最专业的棋牌游戏平台 </title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/password_check.js"></script>

    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        html { overflow-x: hidden; overflow-y: auto; }
        .plus { margin-left: 220px; margin-top: -140px; width: 415px; _margin-left: 110px; _margin-top: -215px; }
        .plus a { display: inline-block; text-align: center; width: 95px; color: #0073cc; font-size: 11px; -webkit-text-size-adjust: none; }
        .plus a:hover { color: #000000; }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:newmenu id="NewMenu2" runat="server" />
        <div class="min_max_adap">
            <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
                <div class="wrap">
                    <div class="totalContent">
                        <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                            overflow: hidden; height: 62px;">
                            <i class="ico_67 i1 newsNotice png"></i>
                            <div id='noticetime' class="time">
                                <span></span>
                            </div>
                            <div class="text" style="font-size: 14px;">
                                服务条款！
                            </div>
                        </div>
                        <div class="totalBd">
                            <div class="totalTabc png" style="width: 100%;">
                                <div id="content01" style="width: 90%; height: 100%">
                                    <div id="title01" style="width: 100%;">
                                        <h3 class="fl">
                                            服务条款</h3>
                                        <p class="dqwz">
                                            当前位置：首页 > 服务条款</p>
                                    </div>
                                    <div id="sub_nr" style="width: 90%; padding: 0; height: 100%;">
                                        <textarea name="textarea" id="textarea" cols="115" rows="20" readonly="readonly"><%=BLL.Config.GetContent(BLL.Config.ItemName_Accept) %></textarea>
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
