<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJuGM" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>大恐龙网络游戏世界___最专业的棋牌游戏平台</title>
    <meta name="Description" content="大恐龙游戏平台是中国最专业的网络棋牌游戏中心之一，是大恐龙网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,大恐龙游戏,大恐龙,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet"
        type="text/css" />
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
                            <a href="/daoju.aspx" style="color: #000; font-size: 14px; font-weight: 500">道具商城</a>
                            &nbsp;|&nbsp; <a style="font-size: 14px;" href="/Manage/Finerylist.aspx">精品ID</a>
                        </div>
                    </div>
                    <div class="totalBd" style="background-color: #bedff6;">
                        <div id="content01">
                            <div id="sub_nr">
                                <div id="props">
                                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                                        <tr>
                                            <td width="42%" align="right" valign="middle">
                                                <img src="/Image/DaoJu/<%=PropID %>.gif" width="136" height="82" />
                                            </td>
                                            <td width="58%" class="prize_info">
                                                <strong>道具名称：<%=PropName %></strong>
                                                <br />
                                                Vip价格：<%=UiCommon.StringConfig.AddZeros(VipPrice)%><%=UiCommon.StringConfig.MoneyName%><br />
                                                普通价格：<%=UiCommon.StringConfig.AddZeros(Price)%><%=UiCommon.StringConfig.MoneyName%><br />
                                                道具介绍：<span class="textgray"><%=PropDesc %></span>
                                            </td>
                                        </tr>
                                    </table>
                                    <div class="prizeText">
                                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                            <tr>
                                                <td height="30" align="right">
                                                    购买数量：
                                                </td>
                                                <td>
                                                    <input type="text" name="txtdj<%=PropID %>" id="txtdj<%=PropID %>" value="1" maxlength="3"
                                                        size="5" class="fr_input" />
                                                </td>
                                            </tr>
                                            <tr>
                                                <th height="38" scope="row">
                                                </th>
                                                <td>
                                                    <input type="submit" value="购  买" onclick="btnBuyDj('<%=PropID%>','<%=PropName%>','<%=VipPrice%>','<%=Price%>','<%=UiCommon.StringConfig.MoneyName %>')"
                                                        class="but_011" />
                                                </td>
                                            </tr>
                                        </table>
                                    </div>
                                </div>
                                <div class="clear">
                                </div>
                            </div>
                            <p>
                                &nbsp;</p>
                            <!--right End-->
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
