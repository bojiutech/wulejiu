<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GMAwardTypeSetEdit.aspx.cs" Inherits="Bzw.Web.Admin.SConfig.GMAwardTypeSetEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>�ޱ���ҳ</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {
	
	margin-top: 0px;
}
-->
</style>

    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script src="/Public/Js/ColorPicker.js"></script>
</head>
<body>
    <form id="Login" runat="server">
	 <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td style="text-align:left; font-weight:bold; height:5px">
                   GM���ͷ�������</td>
            </tr>
        </table>
         <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height:5px;"></td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td style="width:30%; text-align:right;">���ͽ������</td>
                <td  align="left">
					<asp:TextBox ID="txtMoney" runat="server"></asp:TextBox>
                &nbsp;<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtMoney" Display="Dynamic" ErrorMessage="���ͽ��������Ϊ��"></asp:RequiredFieldValidator>
					<asp:RangeValidator ID="RangeValidator1" runat="server" ControlToValidate="txtMoney" ErrorMessage="��Ϊ0-9��������" MaximumValue="900000000" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    ���͵���1��</td>
                <td style="text-align:left;">
					���ߣ�<asp:DropDownList ID="ddlProp1" runat="server">
						<asp:ListItem Value="0" Text="��ѡ"></asp:ListItem>
					</asp:DropDownList> 
				    ������<asp:TextBox ID="txtCount1" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator2" runat="server" ControlToValidate="txtCount1" ErrorMessage="��Ϊ0-999������" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
              
            </tr>
            <tr>
                <td align="right" valign="top">
                    ���͵���2��</td>
                <td align="left">
                 ���ߣ�<asp:DropDownList ID="ddlProp2" runat="server">
						<asp:ListItem Value="0" Text="��ѡ"></asp:ListItem>
					</asp:DropDownList>
				 ������<asp:TextBox ID="txtCount2" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator3" runat="server" ControlToValidate="txtCount2" ErrorMessage="��Ϊ0-999������" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
                
            </tr>
             <tr>
                <td align="right" valign="top">
                    ���͵���3��</td>
                <td align="left">
				 ���ߣ�<asp:DropDownList ID="ddlProp3" runat="server">
						<asp:ListItem Value="0" Text="��ѡ"></asp:ListItem>
					</asp:DropDownList>
				 ������<asp:TextBox ID="txtCount3" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator4" runat="server" ControlToValidate="txtCount3" ErrorMessage="��Ϊ0-999������" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
               
            </tr>
             <tr>
                <td align="right" valign="top">
                    ���͵���4��</td>
                <td align="left">
                 ���ߣ�<asp:DropDownList ID="ddlProp4" runat="server">
						<asp:ListItem Value="0" Text="��ѡ"></asp:ListItem>
					</asp:DropDownList>
				 ������<asp:TextBox ID="txtCount4" runat="server"></asp:TextBox>
                &nbsp;<asp:RangeValidator ID="RangeValidator5" runat="server" ControlToValidate="txtCount4" ErrorMessage="��Ϊ0-999������" MaximumValue="999" MinimumValue="0" Type="Integer"></asp:RangeValidator>
                </td>
              
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" �� �� " class="put" onclick="Button1_Click"/>
                    <input type="button" name="Submit2" value=" �� �� " class="put" onclick="javascript:location.href='GMAwardTypeSet.aspx';"/>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
