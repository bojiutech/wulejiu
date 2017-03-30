<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ClothDetail" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/marquee.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/DaoJu.js"></script>

</head>
<body style="background-image: none;">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        overflow: hidden; text-align: left; float: left;">
            <div id="title01">
                <h3 class="fl">
                    服装商城</h3>
                <p class="dqwz">
                    当前位置：首页 > <a href="/Manage/ClothList.aspx?type=<%=Utility.Common.GetStringOfUrl("token") %>"
                        title="服装商城">服装商城</a></p>
            </div>
            <div id="sub_nr">
                <div id="props">
                    <form id="Form1" class="democss" runat="server">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                        <tr>
                            <td width="42%" align="right" valign="middle">
                                <img src="<%=ImgSrc %>" width="82" height="82" />
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
                                <asp:Button ID="btnBuy" class="but_011" runat="server" Text="购 买" OnClick="btnBuy_Click" OnClientClick="return confirm('您确定要购买此服装吗？')"/>
                                &nbsp;&nbsp;&nbsp;
                            </td>
                        </tr>
                    </table>
                    </form>
                </div>
            </div>
            <p>
                &nbsp;</p>
        </div>
</body>
</html>
