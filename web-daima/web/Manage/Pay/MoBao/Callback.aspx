<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Callback.aspx.cs" Inherits="com.mobaopay.merchant.Callback" %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head2" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
    <title></title>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
    <style type="text/css">
        .logo
        {
            background: url(/images/structurePng.png) no-repeat;
            background-position: -81px -50px;
            width: 251px;
            height: 98px;
            float: left;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="Div1" style="text-align: center; margin: 0 auto; width: 100%;">
        <div id="Div2">
            <h3 class="fl">
                返回支付结果</h3>
            <p class="dqwz">
            </p>
        </div>
        <div id="Div3" style="text-align: center; margin: 0 auto; width: 100%;">
            <div style="text-align: left; margin: 0 auto; width: 25%; line-height: 180%; color: Blue;
                float: left;">
                &nbsp;
            </div>
            <div class="logo">
            </div>
            <div style="text-align: left; margin: 0 auto; width: 30%; line-height: 180%; color: Blue;
                float: left;">
                支付结果：
                <%=veryfyDesc%>
                <asp:Literal ID="Lab_msg" runat="Server" />
                <br />
                订单号：
                <%=orderNo%><br />
                充值金额：
                <%=tradeAmt%><br />
                <a href="/" style="color: Red" title="网站首页">网站首页</a><br />
            </div>
        </div>
    </div>
    <p>
        &nbsp;</p>
    <!--right End-->
    </form>
</body>
</html>
