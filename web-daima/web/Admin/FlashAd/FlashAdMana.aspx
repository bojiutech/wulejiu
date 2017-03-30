<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FlashAdMana.aspx.cs" Inherits="Bzw.Admin2.Admin.FlashAd.FlashAdMana" %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
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
                    <strong>幻灯片图片</strong></td>
            </tr>



            <tr>
                <td align="right">
                    类型：</td>
                <td align="left">
                   <asp:DropDownList ID="dr_type" runat="server" AutoPostBack="true" 
                        onselectedindexchanged="dr_type_SelectedIndexChanged" >
                   <asp:ListItem Text="头部" Value="1"></asp:ListItem>
                   <asp:ListItem Text="左边" Value="2"></asp:ListItem>
                   <asp:ListItem Text="中间" Value="3"></asp:ListItem>
                   <asp:ListItem Text="右边" Value="4"></asp:ListItem>
                   </asp:DropDownList>

                 &nbsp;  <span runat="server" id="span_rs" style=" color:Red;"></span>
                   </td>
            </tr>


            <tr>
                <td align="right">
                    显示标题：</td>
                <td align="left">
                    <input name="title" type="text" id="txttitle" size="50" value="" maxlength="50" runat="server" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    图片地址：</td>
                <td align="left">
      
                         <asp:FileUpload ID="FileUpload1" runat="server" size="50" class ="put"  Style="position: relative" />
                        （图片格式必须为jpg格式）
                        </td>
            </tr>
            <tr>
                <td align="right">
                    链接地址：</td>
                <td align="left">

                 <input  type="hidden" id="txtPic" size="50" value="" maxlength="50" runat="server" 
                        class="put" />

                    <input name="txturl" type="text" id="txturl" size="50" value="" maxlength="50" runat="server"
                        class="put" />
                         <span style=" color:Red;">&nbsp;&nbsp; 请输入“http://”&nbsp; 如：http://www.hn78.com</span> 
                        </td>
            </tr>

            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="提&nbsp;交 " class="put" OnClick="FlashEdits" />
                    <input type="reset" name="Submit2" value="清除重写" class="put" /></td>
            </tr>
        </table>
        <div>
     
        <img id="Image2" runat="server" style="position: relative" height="100"  src="" /></div>
    </form>
</body>
</html>
