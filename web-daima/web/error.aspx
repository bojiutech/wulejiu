<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="error.aspx.cs" Inherits="Bzw.Web.error" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>出错啦！</title>
</head>
<body>
    <form runat="server" id="form1">
    <div style="width: 500px; padding: auto 25px; margin: auto;">
        <p>
            我们正在对系统升级维护。</p>
        <p>
            维护期间，可能随时中止服务，给您带来不便，抱歉！</p>
        <div style="color: White;">
            <asp:Literal runat="server" ID="lit_rs"></asp:Literal>
        </div>
    </div>
    </form>
</body>
</html>
