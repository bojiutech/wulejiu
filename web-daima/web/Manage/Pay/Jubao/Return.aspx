<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Return.aspx.cs" Inherits="Manage_Pay_Jubao_Return" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <br />
        <br />
        <asp:Label ID="Label1" runat="server">支付单号:</asp:Label>
        <asp:Label ID="lblPayid" runat="server"></asp:Label>(由商户生成，确保唯一)
        <br />
        <br />
        <asp:Label ID="Label2" runat="server">金额:</asp:Label>
        <asp:Label ID="lblAmount" runat="server"></asp:Label>(单位元，精确到分)
        <br />
        <br />
        <asp:Label ID="Label4" runat="server">备注:</asp:Label>
        <asp:Label ID="lblRemark" runat="server"></asp:Label>
        <br />
        <br />
        <asp:Label ID="Label6" runat="server">状态:</asp:Label>
        <asp:Label ID="lblState" runat="server"></asp:Label>
        <br />
        <br />
        <asp:Label ID="Label5" runat="server">支付成功时间:</asp:Label>
        <asp:Label ID="lblModifyTime" runat="server"></asp:Label>
    </div>
    </form>
</body>
</html>
