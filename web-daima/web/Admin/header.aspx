<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="header.aspx.cs" Inherits="Bzw.Admin2.Admin.header" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="css/admin.css" type="text/css" rel="stylesheet">
</head>
<body>
    <table cellspacing="0" cellpadding="0" width="100%" background="images/header_bg.jpg"
        border="0">
        <tr height="56">
            <td width="260" style="padding:0px; margin:0px; vertical-align:top;">
                <img height="56" src="images/header_left.jpg" width="260">
            </td>
            <td style="font-weight: bold; color: #fff; padding-top: 20px" align="middle">
                当前用户：<span runat="server" id="span_name"></span>
               
                 &nbsp;&nbsp; <a style="color: #fff" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/UserAdmin/Edit_AdminUsers.aspx" target="main">修改口令</a> &nbsp;&nbsp;
                <a style="color: #fff" onclick="if (confirm('确定要退出吗？')) return true; else return false;"
                    href="/admin/admin_logout.aspx" target="_parent">退出系统</a>
            </td>
            <td  style="text-align:right; padding-right:20px; font-size:12px; width:268px">
               <span style="color:#fff;">欢迎登录 <%=ConfigurationManager.AppSettings["sitename"].ToString()%>后台管理系统！</span>
            </td>
        </tr>
    </table>
    <table cellspacing="0" cellpadding="0" width="100%" border="0">
        <tr bgcolor="#1c5db6" height="4">
            <td>
            </td>
        </tr>
    </table>
</body>
</html>
