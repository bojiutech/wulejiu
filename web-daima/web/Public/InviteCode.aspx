<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="InviteCode.aspx.cs" Inherits="HN.Web.Public.InviteCode" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div style="margin: 0 auto;">
        <h1>
            邀请码为：</h1>
        <big><b style="font-size: 28px; font-weight: bold;">
            <%=inviteCode%></b></big>
    </div>
    </form>
</body>
</html>
