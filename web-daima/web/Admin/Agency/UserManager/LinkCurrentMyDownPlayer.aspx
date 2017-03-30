<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_LinkCurrentMyDownPlayer" Codebehind="LinkCurrentMyDownPlayer.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>我的游戏玩家</title>
	<link href="../../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<div style="text-align: center; font-size: 13px;">
			<table border="1px;" cellpadding="3" style="width: 98%; border-collapse: collapse; margin: 0;">
			    <tr>
			        <td align="left">
			            <a href="/Admin/Agency/UserManager/LinkCurrentDownAgency.aspx?AgencyName=<%=AgencyName%>&url=<%=Server.UrlEncode(Utility.Common.UrlValue) %>">直属代理</a>
			            &nbsp;&nbsp;<a href="/Admin/Agency/UserManager/LinkCurrentMyDownPlayer.aspx?AgencyName=<%=AgencyName%>&url=<%=Server.UrlEncode(Utility.Common.UrlValue) %>">直属玩家</a>
			        </td>
			    </tr>
			    <tr>
			        <td>
			            <font size="4"><b>代理商<span style="color: Red"><%=AgencyName%></span>的直属玩家</b></font>
			            &nbsp;&nbsp;<input id="btnBack" type="button" onclick="document.location.href='<%=Utility.Common.UrlValue %>'" class="put" value=" 返 回 "/>
			        </td>
			    </tr>
				<tr>
					<td align="left">
						<input maxlength="50" type="text" id="txtKey" name="txtKey" size="32" />&nbsp;
						<input type="button" class="put" value="搜索" onclick="OnSearch();" />&nbsp;
						<input type="button" class="put" value="刷新" onclick="RefreshMeDelParam('[&]?key=(\\S)+');" />

						<script>
							var pkey = "请输入直属玩家帐号或真实姓名";
							var o = $("#txtKey");
							o.val(decodeURIComponent(GetRequest("key",pkey)));
							o.css("color","gray");
							o.focus(function(){if(o.val().Trim() == pkey){o.css("color","black");o.val("");}});
							o.blur(function(){if(o.val().Trim() == ""){o.css("color","gray");o.val(pkey);}});
							
							function OnSearch()
							{
								if(o.val().Trim() == "" || o.val().Trim() == pkey)
								{
									alert("请先输入要搜索的直属玩家帐号或真实姓名。");
									return;
								}
								LocationToMeParam("key=" + encodeURIComponent(o.val().Trim()));
							}
						</script>

					</td>
				</tr>
				<tr>
					<td>
						<table style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px; padding: 0px;" border="1px;" id="TABLE1">
							<tr>
								<th>
									玩家帐号</th>
								<th>
									玩家姓名</th>
								<th>
									剩余金币</th>
								<th>
									状态</th>
								<th>
									操作
								</th>
							</tr>
							<asp:Repeater ID="rptDataList" runat="server">
								<ItemTemplate>
									<tr>
										<td>
											<%# Eval("UserName")%>
										</td>
										<td>
											<%# Eval("TrueName")%>
										</td>
										<td>
											<%# UiCommon.StringConfig.MoneyChu100( Convert.ToInt32( Eval( "WalletMoney" ) ) + Convert.ToInt32( Eval( "BankMoney" ) ) )%>
										</td>
										<td>
											<font style='color: <%# Convert.ToInt32(Eval("Disabled")) ==0?"black":"red"%>'>
												<%# Convert.ToInt32( Eval( "Disabled" ) ) == 0 ? "正常" : "禁用"%>
											</font>
										</td>
										<td>
											<a href="PlayerDetailDirect.aspx?userName=<%# Server.UrlEncode( Eval( "UserName" ).ToString() ) %>&url=<%=Utility.Common.CurrentPageUrl %>">查看资料</a>
										</td>
									</tr>
								</ItemTemplate>
							</asp:Repeater>
							<asp:Label ID="lbNonData" runat="server" Text="<tr><td colspan='5'>没有记录！</td></tr>" Visible="false"></asp:Label>
							<tr>
								<td colspan="6" align="left">
									直属玩家的金币总计：<span style="color: red"><%= UiCommon.StringConfig.MoneyChu100(TotalMoney) %></span>金币。</td>
							</tr>
						</table>
						<table width="100%">
							<tr>
								<td colspan="2" style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
									<webdiyer:AspNetPager PageSize="15" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
									</webdiyer:AspNetPager>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
</html>
