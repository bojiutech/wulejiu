<%@ Page Language="C#" AutoEventWireup="true" Codebehind="OnlineUsers.aspx.cs" Inherits="DataAnaly.Analy.Online.OnlineUsers" %>

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
			<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
			<div class="datalist">
				<div class="action" style="width: 50%;">
					<span onclick="Edit();">查看资料</span> <span onclick="ExportPage();">导出所选</span> <span
						onclick="Export();">导出全部</span><%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
									   {%>
					<span onclick="LocationTo(decodeURIComponent(GetRequest('reurl','OnlineUser_Date.aspx')));">
						返回</span>
					<%} %><span onclick="javascript:location.href=location.href;">刷新</span>
				</div>
				<br />
				<div class="search" style="width: auto;">
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
						<th>
							用户名
						</th>
						<th>
							真实姓名
						</th>
						<th axis="WalletMoney">
							总<%=UiCommon.StringConfig.MoneyName %>数
						</th>
						<th>
							QQ
						</th>
						<th axis="RegisterTM">
							注册时间
						</th>
						<th>
							注册所在地
						</th>
						<th axis="RoomName">
							游戏房间
						</th>
						<th axis="GameCount">
							游戏局数
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
										<%# Eval( "RealName" ).ToString()%>
									</td>
									<td align="center">
										<%#UiCommon.StringConfig.MoneyChu100(Eval( "SumMoney" ))%>
									</td>
									<td align="center">
										<%# Eval( "QQNum" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "RegisterTM","{0:yyyy-MM-dd HH:mm:ss}" )%>
									</td>
									<td align="center">
										<%# Eval( "IsRobot" ).ToString() == "1" ? Eval( "RegisterIP" ) : Hebust.IpLocator.GetIpLocation( Eval( "RegisterIP" ).ToString() ).Country + " " + Hebust.IpLocator.GetIpLocation( Eval( "RegisterIP" ).ToString() ).City%>
									</td>
									<td align="center">
										<%# Eval( "RoomName" ).ToString()%>
									</td>
									<td align="center">
										<a href="/Analy/Records/GameRecord.aspx?bd=<%=HN.Common.CommonManager.Web.RequestUrlDecode( "bd", "" ) %>&ed=<%=HN.Common.CommonManager.Web.RequestUrlDecode( "ed", "" )%>&un=<%# Eval( "UserName" ).ToString()%>&reurl=<%=Server.UrlEncode( Request.Url.AbsoluteUri ) %>"
											title="点击可查看<%# Eval( "UserName" ).ToString()%>游戏记录信息" class="hrefColor">
											<%# Eval( "GameCount").ToString()%>
										</a>
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
