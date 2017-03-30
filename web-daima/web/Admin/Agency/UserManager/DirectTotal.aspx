<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_DirectTotal" Codebehind="DirectTotal.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>直属代理和玩家收益合计</title>
    <style type="text/css">
	*{font-family:Arial,'宋体'; font-size:12px;}
	</style>
</head>
<body>
    <form id="form1" runat="server">
		<table border="1px;" cellpadding="3" style="width: 100%; border-collapse: collapse;">
		    <tr><th style="text-align: center; background-color:aliceblue;border-color: powderblue;">
		    查看代理商<%=Utility.Common.GetStringOfUrl("n")%>在他直属代理和玩家贡献的抽水中的收益合计
		    &nbsp;&nbsp;统计时间从<%=Utility.Common.GetStringOfUrl("sd") %>至<%=Utility.Common.GetStringOfUrl("ed") %>
		    &nbsp;&nbsp;<input id="Text1" type="button" value=" 返 回 " onclick="history.back();" /></th></tr>
			<tr>
				<td>
					<table cellpadding="3" style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px; padding: 0px;" border="1px;">
						<tr>
							<th>
								合计类型</th>
							<th>
								抽水贡献</th>
							<th>
								应得佣金</th>
							<th>
								应付佣金</th>
							<th>
								收益</th>
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr>
									<td>
										<%# Eval("UserSort").ToString() == "直属代理" ? "<a href='DirectAgencyTotal.aspx?id=" + Utility.Common.GetStringOfUrl("id") + "&n=" + Utility.Common.GetStringOfUrl("n") + "&sd=" + GetStartTM() + "&ed=" + GetEndTM() + "' title='点击进入直属代理统计页面'>直属代理</a>" : "<a href='DirectPlayerTotal.aspx?id=" + Utility.Common.GetStringOfUrl("id") + "&n=" + Utility.Common.GetStringOfUrl("n") + "&sd=" + GetStartTM() + "&ed=" + GetEndTM() + "' title='点击进入直属玩家统计页面'>直属玩家</a>"%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("SumMoney"))%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("MySumMoney"))%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("PayMoney"))%>
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
										<%=MySumMoneyTotal %>
									</td>
									<td>
										<%=PayMoneyTotal %>
									</td>
									<td>
										<%=MyMoneyTotal %>
									</td>
								</tr>
							</FooterTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='5'>暂无记录...</td></tr>"></asp:Literal>
					</table>
				</td>
			</tr>
		</table>
    </form>
</body>
</html>
