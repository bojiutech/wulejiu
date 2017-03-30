<%@ Page Language="C#" AutoEventWireup="true" Codebehind="LoopMoneyReport.aspx.cs"
	Inherits="DataAnaly.Analy.Report.LoopMoneyReport" %>

<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<%@ Register Assembly="dotnetCHARTING" Namespace="dotnetCHARTING" TagPrefix="dotnetCHARTING" %>
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
			<div id="tabs">
				<div class="tab">
					<ul>
						<li class="active" onclick="SetForms(0)">金币流通统计</li>
					</ul>
					<div class="clear">
					</div>
				</div>
				<div class="forms">
					<ul class="formShow">
						<li style="text-align: center;">
							<br />
							统计日期从：<input type="text" id="txtBeginDate" class="put" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;
							到：<input type="text" id="txtEndDate" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;
							<input type="button" value="搜索" class="btnPublic" onclick="OnSearch();" />

							<script>
							var bd = $("#txtBeginDate");
							var ed = $("#txtEndDate");
							bd.val(decodeURIComponent(GetRequest("bd","")));
							ed.val(decodeURIComponent(GetRequest("ed","")));
							//搜索按钮
							function OnSearch()
							{
								if(bd.val().Trim() != "" || ed.val().Trim() != "" )
								{
									var url = location.href;
									url = SetUrlParam(url,"bd="+encodeURIComponent(bd.val().Trim()));
									url = SetUrlParam(url,"ed="+encodeURIComponent(ed.val().Trim()));
									LocationTo(url);
								}
								else
								{
								    Msg("请选择要日期的开始时段和结束时段",300);
								}
							}				
							</script>

						</li>
						<li>
							<table style="width: 60%;">
								<asp:Repeater ID="rptDataList" runat="server">
									<ItemTemplate>
										 
										<tr>
											<th align="right">
												玩家总金币数：
											</th>
											<td align="left">
												<%#UiCommon.StringConfig.MoneyChu100( Eval( "UserWalletSum" ) )%>
											</td>
										</tr>
										<tr>
											<th align="right">
												充值充入金币的总数：
											</th>
											<td align="left">
												<%#UiCommon.StringConfig.MoneyChu100(Eval( "PayMoneySum" ))%>
											</td>
										</tr>
										<tr>
											<th align="right">
												代理商充金币的总数
											</th>
											<td align="left">
												<%#UiCommon.StringConfig.MoneyChu100(Eval("BankToUserSum"))%>
											</td>
										</tr>
										<tr>
											<th align="right">
												代理商提金币的总数
											</th>
											<td align="left">
												<%#UiCommon.StringConfig.MoneyChu100(Eval("UserToBankSum"))%>
											</td>
										</tr>
									</ItemTemplate>
								</asp:Repeater>
							</table>
						</li>
					</ul>
				</div>
			</div>
			<div id="btns">
				<div>
					<%-- 下面的返回按钮记得修改返回路径 --%>
					<%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
	   {%>
					<input type="button" value="返回" class="btnPublic" onclick="LocationTo(decodeURIComponent(GetRequest('reurl','/Analy/Online/OnlineUser_Date.aspx')));" /><%} %>
				</div>
			</div>
		</div>
	</form>
</body>
</html>
