<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Down2" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/topbtn.js"></script>
    <script type="text/javascript" src="/Public/Js/submu.js"></script>
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
    <form id="form1" runat="server">
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
            <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                overflow: hidden; height: 62px;">
                <i class="ico_67 i1 newsNotice png"></i>
                <div id='noticetime' class="time">
                    <span></span>
                </div>
                <div class="text" style="text-align: left;">
                    <a style="color: #fff;" href="/Down2.aspx">游戏大厅 </a>&nbsp;| &nbsp; <a href="/GameList.aspx">
                        游戏列表</a>
                  
                </div>
            </div>
            <div class="totalBd">
                <div class="yxjs">
                    <table cellpadding="0" cellspacing="0" class="tab06" >
                        <tr>
                            <td rowspan="5" style="padding: 5px; vertical-align: top;">
                            <a target="_blank" href="<%= smallUrl%>">    <img src="<%= mainImg%>" alt="点击下载客户端" style=" border:0px;" width="240px" height="208px" /></a>
                            </td>
                            <th scope="row" style="width:12%; ">
                                更新时间
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <asp:Literal ID="lteTime" runat="server"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                版&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <asp:Literal ID="lteCopy" runat="server"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                应用平台
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <asp:Literal ID="LteUse" runat="server"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                软件大小
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <asp:Literal ID="LteSize" runat="server"></asp:Literal>KB
                            </td>
                        </tr>
                        <tr>
                            <th scope="row" style="vertical-align: top;">
                                游戏介绍：
                            </th>
                            <td colspan="2" >
                                <asp:Literal ID="lteInfo" runat="server"></asp:Literal>
                            </td>
                        </tr>
                    </table>
                    <div class="yx_btn" style="text-align: center;">
                        <a target="_blank" href="<%= smallUrl%>">
                            <img src="/Images/cont_btn01.png" alt="" /></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a
                                href="<%= fullUrl%>"><img src="/Images/cont_btn02.png" alt="" /></a></div>
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
