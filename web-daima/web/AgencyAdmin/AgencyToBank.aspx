<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AgencyToBank.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.AgencyToBank" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>给代理充</title>

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<div style="text-align: center; margin-top: 30px; font-size: 12px;">
			<table width="60%" style="border-collapse: collapse; text-align: center;" border="1px;">
				<tr>
					<td colspan="2">
						<span runat="server" id="span_Title" style="color: Red; font-size: 14px;"></span>&nbsp; 
                             </td>
				</tr>
				<tr>
					<td align="right">
						&nbsp;&nbsp;帐&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;号：</td>
					<td align="left">
						<span style="color: Red">
							<asp:TextBox ID="lab_ToUserName" runat="server" MaxLength="19" style="width:135px;"/>
						</span>
					</td>
				</tr>
				<tr>
					<td align="right">
						&nbsp;&nbsp;姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名：</td>
					<td align="left">
						<span style="color: Red">
						<asp:Label ID="lab_toTrueName2" runat="server"
                            Text=""></asp:Label>
						</span>
					</td>
				</tr>
                <tr>
					<td align="right">
						&nbsp;&nbsp;<asp:Label ID="Label1" runat="server" Text="您当前可用金币数："></asp:Label></td>
                    
					<td align="left"><span style="color: Red">
						<asp:Label ID="lab_Score" runat="server"
                            Text=""></asp:Label></span>
						</td>
				</tr>
				<tr>
					<td align="right">
						&nbsp;&nbsp;充值的数量：</td>
					<td align="left">
						<asp:TextBox ID="tbxEnrich" runat="server" MaxLength="19" style="width:135px;" onkeyup="if(this.value.length==1){this.value=this.value.replace(/[^1-9]/g,'')}else{this.value=this.value.replace(/\D/g,'')}" onafterpaste="if(this.value.length==1){this.value=this.value.replace(/[^1-9]/g,'')}else{this.value=this.value.replace(/\D/g,'')}"/>
						</td>
				</tr>
				<tr>
					<td colspan="2">
						<asp:Button ID="btnEnrich" runat="server" Text="充值"  OnClick="btnEnrich_Click" />
					<asp:Button ID="btn_back" runat="server" Text="返回"  OnClick="btn_back_Click" />
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
</html>
