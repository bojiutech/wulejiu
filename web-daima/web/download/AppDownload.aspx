<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AppDownload.aspx.cs" Inherits="HN.Web.download.AppDownload" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style  type="text/css">
        .div_d{width:100%; height:100%; text-align:center; margin:100px; font-size:12px;}
        .div_d a{ display:block;width:100px; height:100px; text-align:center; font-size:15px;}
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div class="div_d">
        <asp:Literal ID="Literal1" runat="server"></asp:Literal>
    </div>
    </form>
</body>
</html>
