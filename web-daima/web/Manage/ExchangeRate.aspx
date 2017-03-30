<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ExchangeRate" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body style="background-image: none;">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        overflow: hidden; text-align: left; float: left;">
        <div id="title01">
            <h3 class="fl">
                汇率换算</h3>
            <p class="dqwz">
                当前位置：首页 > 会员中心 > 汇率换算</p>
        </div>
        <div id="sub_nr">
            <div class="cz">
                <form id="Form1" runat="server" onsubmit="return onFormSubmit(this)">
                <table width="100%" border="0" cellpadding="0" cellspacing="0" class="memberTable">
                    <tr>
                        <th width="24%" height="35" align="right" scope="row">
                            输入<%=UiCommon.StringConfig.MoneyName %>数：
                        </th>
                        <td width="76%">
                            <input type="text" id="PayMoney" name="PayMoney" maxlength="9" class="input" onkeypress="return KeyPressNum(this,event);"
                                onkeyup="CalculationMoney()" />
                            *
                            <%=UiCommon.StringConfig.MoneyName %>数请输入大于零的整数,兑换比率为<label id="lblRate">2000</label>：1
                        </td>
                    </tr>
                    <tr>
                        <th height="35" align="right" scope="row">
                            兑换成￥：
                        </th>
                        <td>
                            <input type="text" id="ExchangeMoney" readonly="readonly" value="0" class="input" />￥
                        </td>
                    </tr>
                </table>
                </form>
                <script type="text/javascript">
                    function CalculationMoney() {
                        var MoneyRate = document.getElementById("lblRate").innerText;

                        KeyPressNum(this, $("#PayMoney").val());
                        if (isNaN($("#PayMoney").val())) {
                            $("#ExchangeMoney").val("0");

                            return false;

                        } else {
                            $("#ExchangeMoney").val($("#PayMoney").val() / MoneyRate);
                        }
                    }
                </script>
            </div>
        </div>
        <p>
            &nbsp;</p>
        <div class="clear">
        </div>
    </div>
</body>
</html>
