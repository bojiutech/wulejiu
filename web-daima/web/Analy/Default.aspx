<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="DataAnaly.Analy.Default" %>

<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>
</head>
<body>
	<form id="form1" runat="server">
	<Bzw:Top runat="server" ID="top1" EnableViewState="false" />
	<div id="content">
		<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
		<div id="form">
			<table border="0" width="60%">
				<tr>
					<th align="center" colspan="2">
						欢迎您使用<%= SiteName %>运营数据分析系统
					</th>
				</tr>
				<tr>
					<th align="right">
						您的登录名称：
					</th>
					<td align="left">
						<asp:Literal ID="ltlUserName" runat="server"></asp:Literal></td>
				</tr>
				<tr>
					<th align="right">
						登录时间：
					</th>
					<td align="left">
						<asp:Literal ID="ltlLoginTime" runat="server"></asp:Literal>
					</td>
				</tr>
				<tr>
					<th align="right">
						登录IP：
					</th>
					<td align="left">
						<asp:Literal ID="ltlIP" runat="server"></asp:Literal>
					</td>
				</tr>
				<tr>
					<th align="right">
						登录次数：
					</th>
					<td align="left">
						<asp:Literal ID="ltlLoginCount" runat="server"></asp:Literal>
						次
					</td>
				</tr>
				<tr>
					<th align="right">
						网站路径：
					</th>
					<td align="left">
						<%=Request.ServerVariables["Appl_Physical_Path"]%>
					</td>
				</tr>
				<tr>
					<th align="right">
						网站大小：
					</th>
					<td align="left">
						<%=( (float)HN.Common.CommonManager.File.GetDirectorySize( HN.Common.CommonManager.File.GetFilePath( "/" ) ) / 1024 / 1024 ).ToString( "F2" )%>
						M
					</td>
				</tr>
			</table>
		</div>
	</div>
	</form>
</body>
</html>
