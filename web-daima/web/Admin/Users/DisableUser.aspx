<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DisableUser.aspx.cs" Inherits="Bzw.Admin2.Admin.Users.DisableUser" %>
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

    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form  id="form1" runat="server" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <b>用户帐号设置</b></td>
            </tr>
            <tr>
                <td  align="right">用户帐号：</td>
                <td  align="left">
                  &nbsp;
                  <asp:Label runat="server" ID="lab_UserName" Text=""></asp:Label>
                </td>
            </tr>

       
            <tr>
                <td align="right" valign="top">
                    用户ID：</td>
                <td align="left">
                    &nbsp;
                    <asp:Label runat="server" ID="lab_UserID" Text=""></asp:Label>
                    </td>
            </tr>
           
       
            <tr>
                <td align="right" valign="top">
                    状态：</td>
                <td align="left">
                  &nbsp;  <asp:DropDownList ID="drop_state" runat="server">
                  <asp:ListItem Text="启用" Value="0"></asp:ListItem>
                  <asp:ListItem Text="禁用" Value="1"></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
           
       
            <tr>
                <td align="right" valign="top">
                    （禁用/启用）备注：</td>
                <td align="left">
                    &nbsp;
                       <asp:TextBox runat="server" ID="txt_Des" Text="" TextMode="MultiLine"  Rows="5" Width="310"></asp:TextBox>
                    </td>
            </tr>
           
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    <asp:Button ID="Button1" runat="server" Text="确定" class="put" 
                        onclick="Button1_Click"/>
                    &nbsp;&nbsp;
                    <input type="button" name="Submit2" value=" 返 回 " class="put" onclick="javascript:history.back();"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
