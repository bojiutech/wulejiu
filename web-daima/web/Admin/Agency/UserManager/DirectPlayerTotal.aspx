<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_DirectPlayerTotal" Codebehind="DirectPlayerTotal.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>直属玩家收益</title>
    <style type="text/css">
	*{font-family:Arial,'宋体'; font-size:12px;}
	</style>
</head>
<body>
    <form id="form1" runat="server">
		<table border="1px;" cellpadding="3" style="width: 100%; border-collapse: collapse;">
			<tr><th style="text-align: center; background-color:aliceblue;border-color: powderblue;">
			查看代理商<%=Utility.Common.GetStringOfUrl("n")%>在他直属玩家贡献的抽水中的收益
			&nbsp;&nbsp;统计时间从<%=Utility.Common.GetStringOfUrl("sd") %>至<%=Utility.Common.GetStringOfUrl("ed") %>
			&nbsp;&nbsp;<input id="Text1" type="button" value=" 返 回 " onclick="history.back();" /></th></tr>
			<tr>
				<td>
					<table cellpadding="3" style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px; padding: 0px;" border="1px;">
						<tr>
							<th>
								玩家帐号</th>
							<th>
								抽水贡献</th>
							<th>
								抽水比例</th>
							<th>
								收益</th>
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr>
									<td>
										<%# Eval("UserName")%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("SumMoney"))%>
									</td>
									<td>
										<%# Eval("MyPercent")%>%
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("MyMoney"))%>
									</td>
								</tr>
							</ItemTemplate>
							<FooterTemplate>
							    <tr>
									<td>
										合计
									</td>
									<td>
										<%=SumMoneyTotal %>
									</td>
									<td>
										-
									</td>
									<td>
										<%=MyMoneyTotal %>
									</td>
								</tr>
							</FooterTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='4'>暂无记录...</td></tr>"></asp:Literal>
					</table>
				</td>
			</tr>
		</table>
    </form>
</body>
</html>
