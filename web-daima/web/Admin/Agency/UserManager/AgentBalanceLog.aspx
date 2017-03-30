<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgentBalanceLog" Codebehind="AgentBalanceLog.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagPrefix="Bzw" TagName="MDNav" Src="~/Admin/Agency/UserManager/AgencyMoneyDetailNav.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link href="../../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="15">
					<Bzw:MDNav runat="server" ID="nav1" EnableViewState="false" />
				</td>
			</tr>
			<tr>
				<td class="title_03" colspan="2">
					<strong style="color: Red;">结算记录</strong></td>
				<td class="title_03" colspan="15" align="right">
					按玩家帐号：<input type="text" id="txtKey" name="txtKey" maxlength="50" />&nbsp; 按时段：从&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}',onpicked:function(){OnSearch();}});" size="8" />&nbsp;到&nbsp;<input type="text" readonly="readonly" id="txtEndDate" name="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd',onpicked:function(){OnSearch();}});" size="8" />&nbsp;
					<input type="button" value="搜索" class="put" onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();"  class="put" value="刷新" />

					<script>
							var bd = $("#txtBeginDate");
							var ed = $("#txtEndDate");
							var o = $("#txtKey");
							var pkey = "请输入代理玩家帐号";
							
							bd.val(decodeURIComponent(GetRequest("bd","")));
							ed.val(decodeURIComponent(GetRequest("ed","")));
							o.val(decodeURIComponent(GetRequest("key",pkey)));
							
							if(GetRequest("key","") == "")
							{
								o.css("color","gray");
							}
							else
							{
								o.css("color","black")
							}
							o.focus(function(){if(o.val().Trim() == pkey){o.css("color","black");o.val("");}});
							o.blur(function(){if(o.val().Trim() == ""){o.css("color","gray");o.val(pkey);}});
							
							//搜索按钮
							function OnSearch()
							{
								if(bd.val().Trim() != "" || ed.val().Trim() != "" || ( o.val().Trim() != pkey && o.val().Trim() != "" ))
								{
									var url = SetUrlParam(location.href,"key="+ ( ( o.val().Trim() != pkey && o.val().Trim() != "" ) ? encodeURIComponent(o.val().Trim()) : "" ) );
									url = SetUrlParam(url,"bd="+encodeURIComponent(bd.val().Trim()));
									LocationTo(SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim())));
									return;
								}
								alert("请先输入您要搜索的代理或玩家名，或选择要查看的时段。");
							}
					</script>

				</td>
			</tr>
			<tr>
				<th>
					序号</th>
				<th>
					代理商</th>
				<th>
					结算时间</th>
				<th>
					结算前金币</th>
				<th>
					结算金币</th>
				<th>
					结算后金币</th>
				<th>
					操作管理员</th>
				<th>
					操作</th>
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
					<tr>
						<td align="center">
							<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 )%>
						</td>
						<td align="center">
							<%# Eval( "AgencyName" )%>
						</td>
						<td align="center">
							<%# Eval( "AddTime","{0:yyyy-MM-dd HH:mm}" )%>
						</td>
						<td align="center">
							<%# UiCommon.StringConfig.MoneyChu100( Eval( "BaMoneyB" ) )%>
						</td>
						<td align="center">
							<%# UiCommon.StringConfig.MoneyChu100(Eval( "BaMoney" ))%>
						</td>
						<td align="center">
							<%# UiCommon.StringConfig.MoneyChu100( Eval( "BaMoneyA" ) )%>
						</td>
						<td align="center">
							<%# Eval( "AdminName" )%>
						</td>
						<td align="center">
							<%# "<a href='AgentBalanceLog.aspx?params=" + Eval( "BaID" ).ToString() + "&url=" + Server.UrlEncode( Request.Url.AbsoluteUri ) + "' onclick='return confirm(\"您确定要删除这条记录吗？\\r\\n注意：此操作不可恢复！\");'>删除</a>"%>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>暂无数据...</td></tr>"></asp:Literal>
			<tr>
				<td colspan='15' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
