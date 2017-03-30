<%@ Page Language="C#" AutoEventWireup="true" Codebehind="GameRecord.aspx.cs" Inherits="DataAnaly.Analy.Records.GameRecord" %>

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
					<span onclick="ExportPage();">导出所选</span> <span onclick="Export();">导出全部</span><%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
																					  {%>
					<span onclick="LocationTo(decodeURIComponent(GetRequest('reurl','OnlineUser_Date.aspx')));">
						返回</span>
					<%} %>
				</div>
				<div class="search" style="width: auto;">
					<select id="selEnableType" name="selEnableType" onchange="OnTypeSelected(this);">
						<option value="none">=请选择=</option>
						<%=gameList.ToString()%>
					</select>
					&nbsp;&nbsp;<input type="text" name="txtUserName" id="txtUserName" />&nbsp;&nbsp;<input
						type="text" name="txtUserID" id="txtUserID" />&nbsp;&nbsp;日期：<input type="text" name="txtBeginDate"
							id="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;&nbsp;
					到<input type="text" name="txtEndDate" id="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;&nbsp;<span
						onclick="OnSearch()">搜索</span>&nbsp;&nbsp;<span onclick="Clear();">清空</span>

					<script type="text/javascript">
					var bd=$("#txtBeginDate");
					var ed=$("#txtEndDate");
					var un=$("#txtUserName");
					var uid=$("#txtUserID");
					
					var ukey = "请输入用户名";
					var okey = "请输入玩家ID号";
					
					bd.val(decodeURIComponent(GetRequest("bd", "")));
					ed.val(decodeURIComponent(GetRequest("ed", "")));
					var uval = decodeURIComponent(GetRequest("un", ""));
					var oval = decodeURIComponent(GetRequest("uid", ""));
					DropSetByValue("selEnableType",GetRequest("gid","none"));
					
					if (uval != "")
					{
						un.val(uval);
						un.css("color", "black");
					}
					else
					{
						un.val(ukey);
						un.css("color", "gray");
					}
					if (oval != "")
					{
						uid.val(oval);
						uid.css("color", "black");
					}
					else
					{
						uid.val(okey);
						uid.css("color", "gray");
					}
					un.focus(
								function()
								{
									if (un.val().Trim() == ukey)
									{
										un.val("");
										un.css("color", "black");
									}
								}
							);
					un.blur(
								function()
								{
									if (un.val().Trim() == "")
									{
										un.val(ukey);
										un.css("color", "gray");
									}
								}
							);
							
					uid.focus(
								function()
								{
									if (uid.val().Trim() == okey)
									{
										uid.val("");
										uid.css("color", "black");
									}
								}
							);
					uid.blur(
								function()
								{
									if (uid.val().Trim() == "")
									{
										uid.val(okey);
										uid.css("color", "gray");
									}
								}
							);
					
					function OnSearch()
					{
						var url = location.pathname;
						if ((bd.val().Trim()==""||ed.val().Trim()=="")&&(un.val().Trim() == "" ||un.val().Trim() == ukey)&&(uid.val().Trim() == "" || uid.val().Trim() == okey))
						{
							Msg("请输入搜索条件", 200);
							return;
						}
						url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
						url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));
						if(un.val().Trim() != "" &&un.val().Trim() != ukey)
						{
							url = SetUrlParam(url, "un=" +encodeURIComponent(un.val().Trim()));
						}
						if(uid.val().Trim() != "" &&uid.val().Trim() != okey)
						{
							url = SetUrlParam(url, "uid=" + encodeURIComponent(uid.val().Trim()));
						}
						LocationTo(url);
					}
					function Clear()
					{
						$("input[type='text']").val("");
					}
					//按类型搜索事件
					function OnTypeSelected(obj)
					{
						var value = obj.options[obj.selectedIndex].value;
						if(value == "none")
						{
							RefreshMeDelParam("(&)?gid=(\\d+)");
						}
						else
						{
							LocationToMeParam("gid=" + value);
						}
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
						<th axis="ID">
							牌局号</th>
						<th axis="RoomName">
							房间</th>
						<th axis="UserID">
							ID号</th>
						<th axis="UserName">
							用户名</th>
						<th axis="srcMoney">
							开始金币</th>
						<th axis="ChangeMoney">
							输赢金币</th>
					    <th axis="srcPoint">开始积分</th>
					    <th axis="ChangePoint">变化积分</th>
						<th axis="ChangeTax">
							贡献金币</th>
					 
						<th axis="EndTime">
							结束时间</th>
					</tr>
					<tbody id="tbdDataList">
						<asp:Repeater runat="server" ID="rptDataList">
							<ItemTemplate>
								<tr>
									<td align="center">
										<%# "<input type='checkbox' name='cbxData' id='cbx_" + Container.ItemIndex.ToString() + "' value='" + Eval( "ID" ).ToString() + "' />"%>
									</td>
									<td align="center">
										<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
									</td>
									<td align="center">
										<%# Eval( "ID" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "RoomName" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "UserID" ).ToString()%>
									</td>
									<td align="center">
										<%# Eval( "UserName" ).ToString()%>
									</td>
									<td align="center">
										<%#UiCommon.StringConfig.MoneyChu100(Eval( "srcMoney" ))%>
									</td>
									<td align="center">
										<%# UiCommon.StringConfig.MoneyChu100(Eval( "ChangeMoney" ))%>
									</td>
									<td align="center"><%#Eval("srcPoint") %></td>
									<td align="center"><%#Eval("ChangePoint") %></td>
									<td align="center">
										<%# UiCommon.StringConfig.MoneyChu100(Eval( "ChangeTax" ))%>
									</td>
									
									<td align="center">
										<%# Eval( "EndTime","{0:yyyy-MM-dd HH:mm:ss}" )%>
									</td>
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='12'>还没有任何数据。</td></tr>"></asp:Literal></tbody></table>
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
