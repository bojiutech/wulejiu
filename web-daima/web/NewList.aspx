<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="NewList.aspx.cs" Inherits="Bzw.Web.NewList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
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
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
    <style type="text/css">
        html { overflow-x: hidden; overflow-y: auto; }
        .plus { margin-left: 220px; margin-top: -140px; width: 415px; _margin-left: 110px; _margin-top: -215px; }
        .plus a { display: inline-block; text-align: center; width: 95px; color: #0073cc; font-size: 11px; -webkit-text-size-adjust: none; }
        .plus a:hover { color: #000000; }
        .newtype { height: 60px; }
        .newtype li { display: inline-block; font-size: 16px; height: 60px; }
        .newtype li a { line-height: 60px; }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="form1" runat="server">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                        height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div class="text" style="padding: 0px;">
                            <ul class="newtype">
                                <asp:Repeater ID="rpNewType" runat="server">
                                    <ItemTemplate>
                                        <li><a href='NewList.aspx?tid=<%#Eval("Typeid")%>'>
                                            <%#Eval("TypeName")%></a></li>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </ul>
                        </div>
                    </div>
                    <div class="totalBd" style="overflow: hidden; padding: 5px; line-height: 180%; color: #fff;
                        padding-top: 20px; font-size: 13px; font-weight: 500">
                        <table border="0" cellpadding="0" cellspacing="0" class="tableList2" style="width:100%;height:100%">
                            <asp:Repeater ID="rpNewsList" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td class="font02">
                                            &nbsp;&nbsp; [<%#Eval("TypeName")%>]&nbsp;&nbsp;<a href="/NewsPage.aspx?id=<%#Eval("News_ID") %>"
                                                style='color: <%#Eval("TitleColor").ToString() == "black" ? "#000" : Eval("TitleColor")%>;'
                                                target="_blank" title="<%#Eval("Title").ToString() %>"><%# Eval("Title").ToString() %></a>
                                        </td>
                                        <td class="font03">
                                            <%#Eval("Issue_Time","{0:yyyy-MM-dd}")%>
                                        </td>
                                    </tr>
                                </ItemTemplate>
                            </asp:Repeater>
                            <tr>
                                <td colspan="2" style="text-align: center; padding: 5px;">
                                    <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                        FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                                        PageSize="21" ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList"
                                        SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                                        CurrentPageButtonClass="current" ShowPrevNext="False">
                                    </webdiyer:AspNetPager>
                                </td>
                            </tr>
                        </table>
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
