<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgencyEarnMoneyDetail" Codebehind="AgencyEarnMoneyDetail.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>
	<style type="text/css">
		*{ font-size:12px; }
	</style>

</head>
<body>
	<form id="form1" runat="server">
		<div style="text-align: center; background-color: aliceblue; border: 1px outset; width: 98%; border-color: powderblue">
			<div style="text-align: center; font-size: 14px; font-weight: bold; line-height:150%;">
				直属代理商和玩家抽水统计 <input id="btnBack" type="button" onclick=" history.back()" value=" 返 回 "/></div>
		</div>
		<div style="border: 0px outset; background: #ffffff; width: 98%; text-align: center">

			<div style="font-size: 12px; width: 100%;">
				<table border="1" cellpadding="3" cellspacing="0" style="border-collapse: collapse;" bordercolor="#587073" width="100%">
					<tr>
						<th>
							序号</th>
						<th>
							代理或玩家帐号</th>
						<th>
							抽水</th>
					</tr>
					<asp:Repeater runat="server" ID="rptDataList">
						<ItemTemplate>
							<tr>
								<td align="center">
									<%= Rowid +=1 %>
								</td>
								<td align="center">
									<%# Convert.ToInt32(Eval("IsAgency"))==0?Eval("UserName")+" (玩家)":"<a href='AgencyEarnMoneyDetail.aspx?id="+Eval("UserID")+"'>"+Eval("UserName")+"</a> (代理)" %>
								</td>
								<td align="center">
									<%# UiCommon.StringConfig.MoneyChu100(Eval( "SpareMoney" ))%>
								</td>
							</tr>
						</ItemTemplate>
					</asp:Repeater>
					<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='20'>没有数据...</td></tr>"></asp:Literal></table>
			</div>
		</div>
		<%--<div style="text-align: center; font-size: 13px; margin-top: 5px; width: 98%">
			<webdiyer:AspNetPager ID="anpPageIndex" runat="server" PageSize="40" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" PageIndexBoxType="DropDownList" PagingButtonSpacing="10px" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
			</webdiyer:AspNetPager>
		</div>--%>
	</form>
</body>
</html>
