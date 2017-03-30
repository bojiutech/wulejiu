<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="EditMe.aspx.cs" Inherits="DataAnaly.Analy.EditMe" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>
</head>
<body>
	<form id="form1" runat="server">
	<div id="content">
		<div id="form">
			<table>
				<tr>
					<th align="right">
						当前密码：
					</th>
					<td align="left">
						<asp:TextBox runat="server" ID="txtCurrentPassword" TextMode="Password" Width="150px" MaxLength="100"></asp:TextBox>
						<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtCurrentPassword" Display="Dynamic" ErrorMessage="请输入当前密码"></asp:RequiredFieldValidator>
					</td>
				</tr>
				<tr>
					<th align="right">
						新密码：
					</th>
					<td align="left">
						<asp:TextBox runat="server" ID="txtNewPassword" TextMode="Password" Width="150px" MaxLength="100"></asp:TextBox>
						<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtNewPassword" Display="Dynamic" ErrorMessage="请输入新密码"></asp:RequiredFieldValidator>
					</td>
				</tr>
				<tr>
					<th align="right">
						确认新密码：
					</th>
					<td align="left">
						<asp:TextBox runat="server" ID="txtNewPassword2" TextMode="Password" Width="150px" MaxLength="100"></asp:TextBox>
						<asp:CompareValidator ID="CompareValidator1" runat="server" ControlToCompare="txtNewPassword" ControlToValidate="txtNewPassword2" Display="Dynamic" ErrorMessage="两次输入的密码不一致"></asp:CompareValidator>
					</td>
				</tr>
			</table>
		</div>
		<div id="btns">
			<div>
				<asp:Button runat="server" ID="btnSubmit" CssClass="btnPublic" Text="提交" OnClick="btnSubmit_Click" />
			</div>
		</div>
	</div>
	</form>
</body>
</html>
