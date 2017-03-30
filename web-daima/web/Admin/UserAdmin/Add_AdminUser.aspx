﻿<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Add_AdminUser" CodeBehind="Add_AdminUser.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>添加管理员 </title>
    <link href="../css/Inc_style.css" rel="stylesheet" type="text/css">
    <style type="text/css">
<!--
body {
	
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
}
-->
</style>
    <script type="text/ecmascript" language="javascript">
<!--
        function SetFocus() {
            if (document.Login.AdminName.value == '')
                document.Login.AdminName.focus();
            else
                document.Login.AdminName.select();
        }

        function CheckForm() {
            if (document.Login.AdminName.value == '') {
                alert('请输入用户名！');
                document.Login.AdminName.focus();
                return false;
            }
            if (document.Login.AdminPwd.value == '') {
                alert('请输入密码！');
                document.Login.AdminPwd.focus();
                return false;
            }
        }

        function CheckBrowser() {
            var app = navigator.appName;
            var verStr = navigator.appVersion;
            if (app.indexOf('Netscape') != -1) {
                alert('友情提示：\n    您使用的是Netscape浏览器，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
            } else if (app.indexOf('Microsoft') != -1) {
                if (verStr.indexOf('MSIE 3.0') != -1 || verStr.indexOf('MSIE 4.0') != -1 || verStr.indexOf('MSIE 5.0') != -1 || verStr.indexOf('MSIE 5.1') != -1)
                    alert('友情提示：\n    您的浏览器版本太低，可能会导致无法使用后台的部分功能。建议您使用 IE6.0 或以上版本。');
            }
        }
//-->
    </script>
</head>
<body>
    <div align="center">
        <form method="POST" name='Login' id="Login" action="" runat="server" onsubmit='return CheckForm();'>
        <div style="width: 100%; text-align: center; margin: 0px auto;">
            <table border="1" align="center" cellpadding="3" cellspacing="0" bordercolorlight="#335078"  style="width: 99%; font-size: 12px; letter-spacing: 1px; ">
                <tr bgcolor="#B6EBC4">
                    <td bgcolor="#C5D5E4" height="25" style="width: 615px">
                        <p align="center">
                            <b>增加管理员</b>
                    </td>
                </tr>
                <tr>
                    <td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;text-align:left;  border-bottom: medium none;padding-left:30px; ">
                       
                     
                            <br>
                            用户名：
                            <asp:TextBox ID="AdminName" runat="server" class="put"></asp:TextBox>
                       
                    </td>
                </tr>
                <tr>
                    <td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;text-align:left;  border-bottom: medium none;padding-left:30px; ">
                       
                      
                            密&nbsp;&nbsp;码：
                            <asp:TextBox ID="AdminPwd" TextMode="Password" runat="server" class="put"></asp:TextBox>
                        
                    </td>
                </tr>
                <tr>
                   <td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;text-align:left;  border-bottom: medium none;padding-left:30px; ">
                        <div align="center">
                            <div style="width:100%; text-align:left;">
                                分配权限：<br />
                                <div style="padding-left: 18px; line-height: 30px;">
                                    <asp:CheckBoxList ID="chkListModels" runat="server" RepeatColumns="5" RepeatDirection="Horizontal"
                                        RepeatLayout="Flow">
                                    </asp:CheckBoxList>
                                </div>
                            </div>
                        </div>
                    </td>
                </tr>
                <tr>
                    <td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;text-align:left;  border-bottom: medium none;padding-left:300px; ">
                      
                            <asp:Button ID="Button1" runat="server" Text="确定添加" name="B1" class="put" OnClick="Add_AdminUsers" />
                    </td>
                </tr>
            </table>
        </div>
        </form>
    </div>
    <div align="center">
    </div>
    <div align="center" style=" padding-top:10px;">
        <center>
            <table width="99%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolorlight="#335078"  bordercolordark="#FFFFFF" bgcolor="#C5D5E4" style="font-size: 12px; letter-spacing: 1px;">
                <tr align="center" bgcolor="#B6EBC4">
                    <td width="77" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">编号</font>
                    </td>
                    <td width="143" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">管理帐号</font>
                    </td>
                    <td width="53" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">修改</font>
                    </td>
                    <td width="51" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">删除</font>
                    </td>
                    <td width="196" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">时间</font>
                    </td>
                </tr>
                <asp:Repeater ID="List_AdminUsers" runat="server">
                    <ItemTemplate>
                        <tr valign="middle">
                            <td width="77" height="24" bgcolor="#E0E9F1">
                                <%=AdminId=AdminId+1%>
                            </td>
                            <td width="143" height="24" bgcolor="#E0E9F1">
                                <%# Eval("Username") %>
                            </td>
                            <td width="53" height="24" bgcolor="#E0E9F1">
                                <a href="Edit_AdminUser.aspx?id=<%# Eval("id")%>">修改</a>
                            </td>
                            <td width="51" height="24" bgcolor="#E0E9F1">
                                <%# ControlDelLink(Eval("id"), Eval("UserGroup"))%>
                            </td>
                            <td width="196" height="24" bgcolor="#E0E9F1">
                                <%# Eval("LastLoginTime") %>
                            </td>
                        </tr>
                    </ItemTemplate>
                </asp:Repeater>
            </table>
        </center>
    </div>
</body>
</html>
