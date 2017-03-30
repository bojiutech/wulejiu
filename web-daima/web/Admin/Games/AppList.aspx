<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AppList.aspx.cs" Inherits="AppList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>HttpFileCollection Example</title>
    <link href="/css/css.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        .admin_table { }
        .admin_table td { text-align: center; }
        .admin_table td { height: 30px; line-height: 30px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="11">
                <strong>手机应用管理</strong>
            </td>
        </tr>
        <tr>
            <td class="title_03" colspan="7">
                &nbsp;<a href="APPAdd.aspx">添加</a>
            </td>
        </tr>
        <tr>
            <td>
                序号
            </td>
            <td>
                游戏名称
            </td>
            <td>
                安卓地址
            </td>
            <td>
                苹果地址
            </td>
            <td>
                文件大小
            </td>
            <td>
                图片地址
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="GameTypesList" runat="server">
            <ItemTemplate>
                <tr>
                    <td>
                        <%# Container.ItemIndex + 1%>
                    </td>
                    <td>
                        <%# Eval("Gname")%>
                    </td>
                    <td>
                        <%# Eval("AndroidName")%>
                    </td>
                    <td>
                        <%# Eval("AppleName")%>
                    </td>
                    <td>
                        <%# Eval("Filesize")%>
                    </td>
                    <td>
                        <%# Eval("images")%>
                    </td>
                    <td>
                        <a href='APPAdd.aspx?type=edit&id=<%# Eval("id") %>'>修改</a>&nbsp;&nbsp; <a href='APPAdd.aspx?type=del&id=<%# Eval("id") %>'
                            onclick="return confirm('确定删除？');">删除</a>
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
    </table>
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
            <td height="5">
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
