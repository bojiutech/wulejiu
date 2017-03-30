<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PhoneExEdit.aspx.cs" Inherits="Bzw.Admin.Admin.Pay.PhoneExEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form1" runat="server">
    <table border="1" align="left" width="60%" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF">
        <tr>
            <td>
                商品KEY：
            </td>
            <td>
                <asp:TextBox runat="server" ID="txtKey"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td>
                需花费：
            </td>
            <td>
                ￥&nbsp;<asp:TextBox runat="server" ID="txtMoney"  ></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td>
                兑换金币：
            </td>
            <td>
                <asp:TextBox runat="server" ID="txtCoin"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td>
                商品描述：
            </td>
            <td>
                <asp:TextBox runat="server" ID="txtDec"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Button ID="btnAdd"  runat="server" OnClientClick="return onFormSubmit(this)" Text=" 提 交 " OnClick="btnEdit_Click" class="put" />
            </td>
        </tr>
    </table>
        <script type="text/javascript">
        <!--
            function onFormSubmit(f) {

                var msgfix = '温馨提示：\n\n[';
                var msgend = '] 请输入大于或等于零的数字！';

                if (!alertNull(document.getElementById("txtKey"), '温馨提示：\n\n请输入商品KEY！')) {
                    return false;
                }
                if (!alertNull(document.getElementById("txtMoney"), '温馨提示：\n\n请输入兑换所需RMB！')) {
                    return false;
                }
                if (!alertNull(document.getElementById("txtCoin"), '温馨提示：\n\n请输入兑换的金币数额！')) {
                    return false;
                }
                return true;
            }
         //-->
    </script>
    </form>
</body>
</html>
