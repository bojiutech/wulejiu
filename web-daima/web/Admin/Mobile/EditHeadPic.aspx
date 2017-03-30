<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="EditHeadPic.aspx.cs" Inherits="HN.Admin.Admin.Mobile.EditHeadPic" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <style type="text/css">
        body { margin-top: 0px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>用户头像审核</strong>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                用户ID：
            </td>
            <td width="83%" align="left">
                <font color="red">
                    <%=UserID %></font>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                用户头像：
            </td>
            <td width="83%" align="left">
                <img src="/Image/users/<%#  Eval("PicPosition") %>.png" alt="用户头像" width="200" height="200" />
            </td>
        </tr>
        <tr>
            <td align="right">
                是否审核：
            </td>
            <td align="left">
                <input type="radio" name="CheckState" value="0" class="put" <%= (IsAudit.ToString().ToLower()=="0" ? "CHECKED" : "") %> />未审核
                <input type="radio" name="CheckState" value="1" class="put" <%= (IsAudit.ToString().ToLower()=="1" ? "CHECKED" : "") %> />审核通过
            </td>
        </tr>
        <tr>
            <td align="right">
                &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text="确认修改" class="put" OnClick="PrEd" />
                <input type="reset" name="Submit2" value="还原设置" class="put" />
                <input type="button" name="Submit2" onclick="javascript:history.back();" value="返回上一页"
                    class="put" />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
