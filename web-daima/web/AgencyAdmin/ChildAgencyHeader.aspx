<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ChildAgencyHeader.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.ChildAgencyHeader" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
     <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" style="font-size: 12px; font-family: 宋体;">
	<tr>
		
				<td style="padding-left:10px; height:30px; ">
					帐号:
                    <asp:Label runat="server" Text="" ID="lab_UserName"></asp:Label>
                 
				</td>
				<td>
					真实姓名:  <asp:Label runat="server" Text="" ID="lab_TrueName"></asp:Label>
				</td>
				
				<td>
					帐号金币:<span style="color: Red"><asp:Label runat="server" Text="" ID="lab_socre"></asp:Label></span>
                	<a href="javascript:window.location.reload();">刷新</a>
				</td>
				<td>
				    抽水比例: <span style="color: Red"><asp:Label runat="server" Text="" ID="lab_bfb"></asp:Label></span>%
				</td>
			
		<td>
			<%--未结算抽水：0--%></td>
		<td>
			给代理充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_DlSum"></asp:Label></span></td>
		<td>
			给玩家充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_WjSum"></asp:Label></span></td>
	</tr>
</table>
    </div>
    </form>
</body>
</html>
