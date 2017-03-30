<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Post.aspx.cs" Inherits="Manage_Pay_Jubao_Post" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <script type="text/javascript">
        function Post() {
            document.getElementById("form1").submit();
        }
    </script>
</head>
<body>
    <form id="form1" runat="server" method="post" action="http://www.jubaopay.com/apipay.htm">
    <div>
        <asp:HiddenField ID="message" runat="server" />
        <asp:HiddenField ID="signature" runat="server" />
        <asp:HiddenField ID="payMethod" runat="server" />
    </div>
    </form>
</body>
</html>
