<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PayUpdate.aspx.cs" Inherits="Bzw.Admin.Admin.Pay.PayUpdate" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
		<!
		-- body
		{
			
			margin-top: 0px;
		}
		.red
		{
			color: red;
		}
		-- ></style>
</head>
<body>
	  <form id="form1" runat="server">
	<input type="hidden" name="act" id="act" value="post" />
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
		bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				修改充值卡类型</td>
		</tr>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td style="height: 5px">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
		bgcolor="F2F8FF" class="admin_table">
		
		<tr>
			<td align="right" width="40%" style="height:20px;">
				道具名称：
			</td>
			<td align="left"  style="height:20px;">

			                  <asp:DropDownList ID="ddlVipType" runat="server">
											<asp:ListItem Value="0" Text="普通卡"></asp:ListItem>
											<asp:ListItem Value="1" Text="新手卡"></asp:ListItem>
								</asp:DropDownList>
                				&nbsp;&nbsp;&nbsp;&nbsp;
                				<asp:Button ID="CreateUser" runat="server" Text=" 修改 " CssClass="put" 
                    onclick="CreateUser_Click" />
			
			</td>
		</tr>

	</table>
	
      
	 </form>
	
</body>
</html>
