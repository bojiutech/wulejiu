<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ClothList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ OutputCache Duration="60" VaryByParam="page" %>
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

    <style type="text/css">
        /*------------#prize And #props-----------------*/#prize, #props
        {
            padding: 15px 15px 0;
            float: left;
        }
        #prize dl, #props dl
        {
            width: 210px;
            height: 380px;
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
            height: 22px;
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
            border: 1px solid #b6d6ec;
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
<body style="background-image: none;">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        overflow: hidden; text-align: left; float: left;">
            <div id="title01">
                <h3 class="fl">
                    服装商城</h3>
                <p class="dqwz">
                    当前位置：首页 &gt; 服装商城</p>
            </div>
            &nbsp;&nbsp;&nbsp; <a href="/DaoJu.aspx">游戏商城</a>&nbsp;|&nbsp; <font class="red">服装商城</font>
            <div id="sub_nr">
                <div id="prize">
                    <asp:Repeater ID="rpCloth" runat="server">
                        <ItemTemplate>
                            <dl>
                                <dd>
                                    <a href='/Manage/ClothDetail.aspx?id=<%#Eval("ID") %>&token=<%=Utility.Common.GetStringOfUrl("type") %>'
                                        title='<%#Eval("LogName") %>'>
                                        <img src='/Image/Users/<%#Eval("Sex").ToString() == "True" ? "b_" +( Convert.ToInt32(Eval("LogID").ToString())+1) + ".png" : "g_" + (Convert.ToInt32(Eval("LogID").ToString())+1) + ".png"%>'
                                            alt="" width="200" height="250" onerror="this.src='/Images/NoPicture/no_pic.gif';this.onerror='';" /></a></dd>
                                <dt><strong>
                                    <%#Eval("LogName") %>
                                </strong></dt>
                                <dt>
                                   7天<%=UiCommon.StringConfig.MoneyName%>：<%#UiCommon.StringConfig.AddZeros(Eval("WeekPrice"))%>
                                </dt>
                                <dt> 30天<%=UiCommon.StringConfig.MoneyName%>：<%#UiCommon.StringConfig.AddZeros(Eval("MonthPrice"))%></dt>
                                <dt><a href='/Manage/ClothDetail.aspx?id=<%#Eval("ID") %>&token=<%=Utility.Common.GetStringOfUrl("type") %>'
                                    class="btn">我要购买</a> </dt>
                            </dl>
                        </ItemTemplate>
                    </asp:Repeater>
                </div>
                <!--pageNumber-->
                <div class="clear">
                </div>
            </div>
            <p>
                &nbsp;</p>
        </div>
</body>
</html>
