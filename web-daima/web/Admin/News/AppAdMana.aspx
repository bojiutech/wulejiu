<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AppAdMana.aspx.cs" Inherits="Bzw.Admin2.Admin.News.AppAdMana" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {

	margin-top: 0px;
}
-->
</style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>APP消息</strong>
            </td>
        </tr>
        <tr>
            <td align="right">
                消息标题：
            </td>
            <td align="left">
                <input name="txtTitle" type="text" id="txtTitle" size="50" value="" maxlength="150"
                    runat="server" class="put" style="width: 480px;" /><span style="color:red">* 标题最多22个字。</span>
            </td>
        </tr>
        <tr>
            <td align="right">
                消息内容：
            </td>
            <td align="left">
                <asp:TextBox ID="txtBody" Text="" runat="server" class="put" TextMode="MultiLine"
                    Height="70" Width="480"></asp:TextBox><span style="color:red">* 内容最多60个字。</span>
            </td>
        </tr>
        <tr>
            <td align="right">
                所属平台：
            </td>
            <td align="left">
                <asp:DropDownList ID="DropDownList1" runat="server">
                    <asp:ListItem Selected="True" Value="0">手游平台</asp:ListItem>
                    <asp:ListItem Value="1">U3D平台</asp:ListItem>
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td align="right">
                权重排序：
            </td>
            <td align="left">
                <input name="txtOrderID" type="text" id="txtOrderID" style="width: 100px;" value="0"
                    maxlength="10" runat="server" class="put" />
            </td>
        </tr>
        <tr>
            <td align="right">
                &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text="提&nbsp;交 " class="put" OnClick="FlashEdits" />
                <asp:Button ID="Button2" runat="server" Text="返&nbsp;回 " class="put" OnClick="Button2_Click" />
            </td>
        </tr>
    </table>
    <div>
    </div>
    </form>
</body>
</html>
