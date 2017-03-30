<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>系统登录</title>
	<link href="/css/AgencyLogin.css" rel="Stylesheet" />
	<script>
	    function TopLocationToMe() {
	        document.getElementById("<%=txtUserName.ClientID %>").focus();
	        if (parent != null && parent.location.href != location.href)
	            top.location.href = location.href;
	    }
	</script>
</head>
<body onload="TopLocationToMe()">
	<form id="form1" runat="server">
		<div id="login">
			<div class="login_box">
				<table width="86%" height="118" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td colspan="3">
							<asp:Label ID="lbMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
					</tr>
					<tr>
						<td style="width: 114px">
							<div align="right">
								代理帐号：</div>
						</td>
						<td style="width: 136px">
							<asp:TextBox ID="txtUserName" runat="server" MaxLength="50" />
						</td>
						<td width="33%">
							<asp:RequiredFieldValidator ID="rfvUserName" runat="server" ErrorMessage="代理帐号不能为空!" ControlToValidate="txtUserName" ForeColor="red"  Font-Bold="True"/>
						</td>
					</tr>
					<tr>
						<td style="width: 114px">
							<div align="right">
								密&nbsp;&nbsp;码：</div>
						</td>
						<td style="width: 136px">
							<asp:TextBox ID="txtPassword" runat="server" TextMode="Password" MaxLength="50">*</asp:TextBox></td>
						<td>
							<asp:RequiredFieldValidator ID="rfvPassword" runat="server" ErrorMessage="密码不能为空!" ControlToValidate="txtPassword" ForeColor="red"  Font-Bold="True"/>
						</td>
					</tr>
					<tr>
						<td style="width: 114px">
							&nbsp;</td>
						<td style="width: 136px">
							<asp:Button ID="btnOk" runat="server" OnClick="btnOk_Click" class="input_log" /></td>
						<td>
							&nbsp;</td>
					</tr>
				</table>
			</div>
		</div>
	</form>
</body>
</html>
