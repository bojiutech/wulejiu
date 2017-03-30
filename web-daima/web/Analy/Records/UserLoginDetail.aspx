<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserLoginDetail.aspx.cs" Inherits="DataAnaly.Analy.Records.UserLoginDetail" %>

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
</head>
<body>
	<form id="form1" runat="server">
		<Bzw:Top runat="server" ID="top1" EnableViewState="false" />
		<div id="content">
			<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
			<div class="datalist">
				<div class="action" style="width: 50%;">
					<span onclick="ExportPage();">导出所选</span> <span
						onclick="Export();">导出全部</span><%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
									   {%>
						<span onclick="LocationTo(decodeURIComponent(GetRequest('reurl','OnlineUser_Date.aspx')));">返回</span>
						<%} %>
				</div>
				<br />
				<div class="search" style="width: auto;">
					日期：<input type="text" name="txtBeginDate" id="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;&nbsp;
					到<input type="text" name="txtEndDate" id="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;&nbsp;用户名：<input type="text" name="txtUserName" id="txtUserName" );" />&nbsp;&nbsp;<span
								onclick="OnSearch()">搜索</span>&nbsp;&nbsp;<span onclick="Clear();">清空</span>

					<script type="text/javascript">
					var bd=$("#txtBeginDate");
					var ed=$("#txtEndDate");
					var o=$("#txtUserName");
					var pkey="请输入用户名";

					bd.val(decodeURIComponent(GetRequest("bd", "")));
					ed.val(decodeURIComponent(GetRequest("ed", "")));
					o.val(decodeURIComponent(GetRequest("un", "")));
					
					o.focus(function(){if(o.val().Trim() == pkey){o.val("");o.css("color","black");}});
					o.blur(function(){if(o.val().Trim() == ""){o.val(pkey);o.css("color","gray");}});

					function OnSearch()
					{
						var url = location.pathname;
						if (bd.val().Trim()==""&&ed.val().Trim()==""&&o.val().Trim()=="")
						{
							Msg("请输入搜索条件", 300);
							return;
						}
						url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
						url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));
						url = SetUrlParam(url, "un=" + encodeURIComponent(o.val().Trim()));
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
						<th axis="UserID">
							玩家ID
						</th>
						<th axis="UserName">
							用户名
						</th>
						<th axis="LastLoginTM">
							登录时间
						</th>
						<th>
							IP
						</th>
						<th>
							地区
						</th>
					</tr>
					<tbody id="tbdDataList">
						<asp:Repeater runat="server" ID="rptDataList">
							<ItemTemplate>
								<tr>
									<td align="center">
										<%# "<input type='checkbox' name='cbxData' id='cbx_" + Container.ItemIndex.ToString() + "' value='" + Eval( "UserID" ).ToString() + "' />"%>
									</td>
									<td align="center">
										<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
									</td>
									<td align="center">
										<%# Eval( "UserID" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "UserName" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "LastLoginTM","{0:yyyy-MM-dd HH:mm:ss}" )%>
									</td>
									<td align="center">
										<%# Eval( "LastLoginIP" ).ToString()%>
									</td>
									<td align="center">
										<%# Hebust.IpLocator.GetIpLocation( Eval( "LastLoginIP" ).ToString() ).Country + " " + Hebust.IpLocator.GetIpLocation( Eval( "LastLoginIP" ).ToString() ).City%>
									</td>
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='7'>还没有任何数据。</td></tr>"></asp:Literal></tbody></table>
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


