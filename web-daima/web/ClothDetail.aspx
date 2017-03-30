<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ClothDetail.aspx.cs" Inherits="Bzw.Web.ClothDetail" %>
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
                <div class="text" style=" text-align:left;">
                    购买服装
                </div>
            </div>
            <div class="totalBd">
             <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02" >
                        <tr>
                            <td width="42%" align="right" valign="middle">
                                <img src="<%=ImgSrc %>" width="182" height="182" />
                            </td>
                            <td width="58%" class="prize_info">
                                <strong>名称：<%=LogName %></strong> <br />
                                7天有效期价格：<%=UiCommon.StringConfig.AddZeros(WeekPrice)%><%=UiCommon.StringConfig.MoneyName%><br />
                                30天有效期价格：<%=UiCommon.StringConfig.AddZeros(MonthPrice) %><%=UiCommon.StringConfig.MoneyName %><br />
                                赠送：<%=SendLotteries %>
                                <%=UiCommon.StringConfig.GoldName %><br />
                                道具说明：<span class="textgray"><%=Descript %></span>
                                <br />
                                购买类型：<select id="selType" name="selType"> <option value="7">7天有效期</option><option value="30">30天有效期</option></select>
                            </td>
                            <asp:HiddenField ID="hidId" runat="server" />
                        </tr>
                        <tr>
                            <td colspan="2" style="text-align: center;">
                                <asp:Button ID="btnBuy" class="but_011" runat="server" Text="购 买" OnClick="btnBuy_Click" style=" background-image:url(/images/shop_but02.gif);  border:0px; width:64px; height:23px; cursor:pointer" OnClientClick="return confirm('您确定要购买此服装吗？')"/>
                                &nbsp;&nbsp;&nbsp;
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

