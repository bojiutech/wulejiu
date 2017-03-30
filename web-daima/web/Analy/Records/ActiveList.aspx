<%@ Page Language="C#" AutoEventWireup="true" Codebehind="ActiveList.aspx.cs" Inherits="DataAnaly.Analy.Records.ActiveList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>

	<script type="text/javascript">
		var ActionUrl = "/Analy/User/PlayerDetail.aspx"; //定义本页的信息编辑页地址
		var Target = "_blank"; //定义信息编辑页打开方式，_self表示在当前页打开，即浮动出一个信息编辑页面层来。_blank表示在新页面打开
		var DialogWidth = 500; //定义浮动层的宽度，仅在Target="_self"时有效
		var DialogHeight = 300; //定义浮动层的高度，仅在Target="_self"时有效
	</script>

</head>
<body>
	<form id="form1" runat="server">
		<Bzw:Top runat="server" ID="top1" EnableViewState="false" />
		<div id="content">
			<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" /><span style="color:Red;"> （<strong>注：</strong>活跃用户是指登录过游戏，游戏局数>=<strong><%=activeGameCount %>局</strong>的玩家个数）</span>
			<div class="datalist">
				<div class="action" style="width: 50%;">
					<span onclick="ExportPage();">导出所选</span> <span onclick="Export();">导出全部</span><%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
																					  {%>
					<span onclick="LocationTo(decodeURIComponent(GetRequest('reurl','OnlineUser_Date.aspx')));">
						返回</span>
					<%} %>
				</div>
				<br />
				<div class="search" style="width: auto;">
					指向：<input type="text" name="txtDate" id="txtDate" onchange="OnSearch();" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd'});" />&nbsp;&nbsp;&nbsp;&nbsp;<%--<span
						onclick="OnSearch()">搜索</span>&nbsp;&nbsp;--%><span onclick="Clear();">清空</span>

					<script type="text/javascript">
					var date=$("#txtDate");
					date.val(decodeURIComponent(GetRequest("date", "")));

					function OnSearch()
					{						
						if (date.val().Trim()=="")
						{
							return;
						}
						var url = location.pathname;
						url = SetUrlParam(url, "date=" + encodeURIComponent(date.val().Trim()));
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
				<div style="overflow-x:scroll;width:100%;height:100%">
					<table id="tbContent">
						<tr>
							<%=tableHeaders.ToString()%>
						</tr>
						<tbody id="tbdDataList">
							<%=tableList.ToString()%>
						</tbody>
					</table>
				</div>
				<asp:Literal runat="server" ID="ltNonData" Text="还没有任何数据。"></asp:Literal>
				<div class="pager">
					<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="共%PageCount%页，当前第%CurrentPageIndex%页，每页%PageSize%条，共%RecordCount%条。"
						FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
						PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
						SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True"
						PageSize="15">
					</webdiyer:AspNetPager>
				</div>
				<div class="clear">
				</div>
			</div>
		</div>
	</form>
</body>
</html>
