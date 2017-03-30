<%@ Page Language="C#" AutoEventWireup="true" Codebehind="OnlineUser_Date.aspx.cs"
	Inherits="DataAnaly.Analy.Online.OnlineUser_Date" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>

	<script type="text/javascript">
		var ActionUrl = null; //定义本页的信息编辑页地址
		var Target = "_blank"; //定义信息编辑页打开方式，_self表示在当前页打开，即浮动出一个信息编辑页面层来。_blank表示在新页面打开
		var DialogWidth = 500; //定义浮动层的宽度，仅在Target="_self"时有效
		var DialogHeight = 300; //定义浮动层的高度，仅在Target="_self"时有效
	</script>

	<style type="text/css">
		#txtBeginDate { width: 90px; }
		#txtEndDate { width: 90px; }
		#txtTitle { width: 121px; }
	</style>
</head>
<body>
	<form id="form1" runat="server">
		<Bzw:Top runat="server" ID="top1" EnableViewState="false" />
		<div id="content">
			<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
			<div class="datalist">
				<div class="action" style="width: 50%;">
					<span onclick="ExportPage();">导出所选</span> <span onclick="Export();">导出全部</span>
				</div>
				<br />
				<div class="search" style="width: auto;">
					日期：<input type="text" name="txtBeginDate" id="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;&nbsp;
					到<input type="text" name="txtEndDate" id="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;&nbsp;<span
						onclick="OnSearch()">搜索</span>&nbsp;&nbsp;<span onclick="RefreshMe();">刷新</span>

					<script type="text/javascript">
					var bd=$("#txtBeginDate");
					var ed=$("#txtEndDate");

					bd.val(decodeURIComponent(GetRequest("bd", "")));
					ed.val(decodeURIComponent(GetRequest("ed", "")));

					function OnSearch()
					{
						var url = location.pathname;
						if (bd.val().Trim()==""||ed.val().Trim()=="")
						{
							Msg("请输入开始日期和结束日期", 200);
							return;
						}
						url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
						url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));
						LocationTo(url);
					}
					function Clear()
					{
						$("input[type='text']").val("");
					}
					</script>

				</div>
				<div class="clear">
				</div>
				<table id="tbContent">
					<tr>
						<th>
							<input type="checkbox" name="cbxAll" id="cbxAll" value="all" />
						</th>
						<th>
							序号
						</th>
						<th axis="ReportDate">
							日期
						</th>
						<th>
							当前在线
						</th>
						<th axis="AvgOnline">
							平均在线
						</th>
						<th axis="MaxOnline">
							最高在线
						</th>
						<th axis="MinOnline">
							最低在线
						</th>
						<th axis="LoginNum">
							登录人数
						</th>
						<th axis="ActiveNum">
							活跃人数
						</th>
						<th axis="ActiveGameCount">
							当天活跃用户标准（游戏局数）
						</th>
					</tr>
					<tbody id="tbdDataList">
						<asp:Repeater runat="server" ID="rptDataList">
							<ItemTemplate>
								<tr style="cursor: auto;">
									<td align="center">
										<%# "<input type='checkbox' name='cbxData' id='cbx_" + Container.ItemIndex.ToString() + "' value='" + Eval( "ID" ).ToString() + "' />"%>
									</td>
									<td align="center">
										<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
									</td>
									<td align="center">
										<a href="/Analy/Chart/Chart.aspx?date=<%# Eval( "ReportDate","{0:yyyy-MM-dd}" )%>&type=0&action=online&reurl=<%=Server.UrlEncode( Request.Url.AbsoluteUri ) %>"
											title="点击可查看当天在线人数变化曲线图" class="hrefColor">
											<%# Eval( "ReportDate","{0:yyyy-MM-dd}" )%>
										</a>
									</td>
									<td align="center">
										<%# Eval( "OnlineNum" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "AvgOnline" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "MaxOnline" ).ToString()%>
									</td>
									<td align="center">
										<%#Eval( "MinOnline" ).ToString()%>
									</td>
									<td align="center">
										<a href="/Analy/Records/UserLoginList.aspx?bd=<%# Eval( "ReportDate","{0:yyyy-MM-dd}" )%>&&ed=<%# Eval( "ReportDate","{0:yyyy-MM-dd}" )%>&reurl=<%=Server.UrlEncode( Request.Url.AbsoluteUri ) %>"
											title="点击可查看当天登录大厅详细列表" class="hrefColor">
											<%# Eval( "LoginNum" ).ToString()%>
										</a>
									</td>
									<td align="center">
										<a href="/Analy/Records/ActiveList.aspx?date=<%# Eval( "ReportDate","{0:yyyy-MM-dd}" )%>&reurl=<%=Server.UrlEncode( Request.Url.AbsoluteUri ) %>"
											title="点击可查看当天活跃用户列表" class="hrefColor"><%# Eval( "ActiveNum" )%></a>
									</td>
									<td align="center">
										<%# Eval( "ActiveGameCount" ).ToString()%>
									</td>
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>还没有任何数据。</td></tr>"></asp:Literal></tbody></table>
				<div class="pager">
					<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="共%PageCount%页，当前第%CurrentPageIndex%页，每页%PageSize%条，共%RecordCount%条。"
						FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
						PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
						SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True"
						PageSize="20">
					</webdiyer:AspNetPager>
				</div>
				<div class="clear">
				</div>
			</div>
		</div>
	</form>
</body>
</html>
