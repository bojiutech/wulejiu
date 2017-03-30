<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FamilyAdd.aspx.cs" Inherits="HN.Admin.Admin.FamilyAd.FamilyAdd" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
      <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
        <style type="text/css">
<!--
body {
	
	margin-top: 0px;
}
-->
</style>
</head>
<body>
    <form id="form1" runat="server">
     <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>添加家族</strong></td>
            </tr>
            <tr>
                <td align="right">
                    显示标题：</td>
                <td align="left">
                    <asp:TextBox ID="title" runat="server" CssClass="put" MaxLength="50" size="50"></asp:TextBox>
                    </td>
            </tr>
            <tr>
                <td align="right">
                    图片地址：</td>
                <td align="left">
                        <!--预览end-->
                        <asp:FileUpload ID="FileUploadimg" size="50" class ="put" runat="server"/>
                         
                        </td>
            </tr>
            <tr>
                <td align="right">
                    内容：</td>
                <td align="left">
                    <asp:TextBox ID="content" runat="server" CssClass="put" MaxLength="50" size="50"></asp:TextBox>
                   </td>
            </tr>


            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="填好提交" class="put"   OnClick="FlashAdds"/>
                    <asp:Button ID="Button2" runat="server" Text="清除重写" CssClass="put" 
                        onclick="Button2_Click" />
            </tr>
        </table>
    </form>
</body>
</html>
