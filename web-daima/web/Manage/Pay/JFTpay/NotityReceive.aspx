<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage_Pay_JFTpay_NotityReceive" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>聚付通支付</title>
    <meta name="description" content="">
    <meta http-equiv="Content-Type" content="text/html; charset=uft-8" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <style type="text/css">
        body
        {
            font-size: 12px;
            margin-left: 0px;
            margin-top: 0px;
            margin-right: 0px;
            margin-bottom: 0px;
        }
        .Sy1
        {
            color: #2179DD;
        }
        .Sy2
        {
            color: #FFFFFF;
            font-size: 16px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="4" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    返回环迅支付结果</h3>
                <p class="dqwz">
                    当前位置：首页 > 账户充值</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <form id="form2" runat="server">
                    <div style="text-align: center">
                    
                                    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
                                        <tr>
                                            <td height="30" colspan="2" bgcolor="#6BBE18">
                                                <span style="color: #FFFFFF">感谢您使用聚付通支付平台</span>
                                            </td>
                                        </tr>
                                     
                                        <tr>
                                            <td align="left" width="30%" class="Sy1">
                                                &nbsp;&nbsp;商户订单号
                                            </td>
                                            <td align="left">
                                                &nbsp;&nbsp;<label id="id" runat="server"></label>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td align="left">
                                                &nbsp;&nbsp;支付结果
                                            </td>
                                            <td align="left">
                                                &nbsp;&nbsp;<label id="state" runat="server"></label>
                                            </td>
                                        </tr>
                                    </table>
                               
                    </div>
                    </form>
                    <div id="warning">
                        请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <!--right End-->
        <!--content End-->
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
    </form>
</body>
</html>
