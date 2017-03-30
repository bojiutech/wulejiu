<%@ Page Language="C#" AutoEventWireup="true" Codebehind="Chart.aspx.cs" Inherits="DataAnaly.Analy.Chart.Chart" %>

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
						<li class="active" onclick="SetForms(0)"><%=type == "1" ? "新玩家每日时间点图形数据分析" : "每日时间点图形数据分析" %></li>
					</ul>
					<div class="clear">
					</div>
				</div>
				<div class="forms">
					<ul class="formShow">
						<li style="text-align: center;">
							<br />
							&nbsp;&nbsp;<input type="radio" id="rdReg" name="type" title="按注册人数" value="reg" /><label
								for="rdreg" style="cursor:pointer;">按注册人数</label>
							&nbsp;&nbsp;<input type="radio" name="type" id="rdLogin" title="按登录人数" value="login" />
							<label for="rdLogin" style="cursor:pointer;">
								按登录人数</label>&nbsp;&nbsp;<input type="radio" id="rdOnline" name="type" title="按在线人数"
									value="online" /><label for="rdOnline" style="cursor:pointer;">按在线人数</label>&nbsp;&nbsp;<input type="radio"
										name="type" id="rdPay" title="按充值人数" value="pay" /><label for="rdPay" style="cursor:pointer;">按充值人数</label>&nbsp;&nbsp&nbsp;&nbsp;指向：<input
											type="text" id="txtDate" onclick="WdatePicker({dateFmt:'yyyy-MM-dd'});" />
							&nbsp;&nbsp;<input type="radio" id="rdLine" name="chart" title="曲线图" value="line" /><label
								for="rdLine" style="cursor:pointer;">曲线图</label>&nbsp;&nbsp;<input type="radio" id="rdPillar" name="chart"
									title="柱状图" value="pillar" /><label for="rdPillar" style="cursor:pointer;">柱状图</label>&nbsp;&nbsp;<input
										type="button" onclick="OnSearch()" value="确定" class="btnPublic" />&nbsp;&nbsp;<input type="button" class="btnPublic" value="清空"
											onclick="Clear();"><br /><strong> 备注：注册、登录、充值是按照时间段统计，在线是按照时间点统计。</strong>

							<script type="text/javascript">
								
								var date=$("#txtDate");

								date.val(decodeURIComponent(GetRequest("date", "")));
								var action=decodeURIComponent(GetRequest("action", "reg"));
								var ct=decodeURIComponent(GetRequest("ct", "line"));
								if(action=="login")
								{
									$("#rdLogin").attr("checked",true);
								}
								else if(action=="online")
								{
									$("#rdOnline").attr("checked",true);
								}
								else if(action=="pay")
								{
									$("#rdPay").attr("checked",true);
								}
								else
								{
									$("#rdReg").attr("checked",true);
								}
								
								if(ct=="pillar")
								{
									$("#rdPillar").attr("checked",true);
								}
								else
								{
									$("#rdLine").attr("checked",true);
								}

								function OnSearch()
								{
									var url = location.pathname;
									if (date.val().Trim()==""||$("input[type='radio'][name='type']:checked").length<=0||$("input[type='radio'][name='chart']:checked").length<=0)
									{
										Msg("请输入查看日期并选择查看图形功能（如按注册、按登录等）和图形类型（如曲线图或柱状图）！", 300);
										return;
									}
									if($("input[type='radio'][name='type']:checked").length!=1||$("input[type='radio'][name='chart']:checked").length!=1)
									{
										Msg("查看图形功能（如按注册、按登录等）或图形类型（如曲线图或柱状图）只能单选！", 300);
										return;
									}
									url = SetUrlParam(url, "date=" + encodeURIComponent(date.val().Trim()));
									var action,ct;
									if($("#rdLogin").is(":checked"))
									{
										action=encodeURIComponent($("#rdLogin").val().Trim())
									}
									else if($("#rdPay").is(":checked"))
									{
										action=encodeURIComponent($("#rdPay").val().Trim())
									}
									else if($("#rdOnline").is(":checked"))
									{
										action=encodeURIComponent($("#rdOnline").val().Trim())
									}
									else
									{
										action=encodeURIComponent($("#rdReg").val().Trim())
									}
									if($("#rdPillar").is(":checked"))
									{
										ct=encodeURIComponent($("#rdPillar").val().Trim())
									}
									else
									{
										ct=encodeURIComponent($("#rdLine").val().Trim())
									}
									url = SetUrlParam(url, "action=" + action);
									url = SetUrlParam(url, "ct=" + ct);
									LocationTo(url);
								}
								function Clear()
								{
									$("input[type='text']").val("");
								}
							</script>

							<div id="divchart1" runat="server" style="overflow-x: scroll; width: 100%; height: 100%;">
								<dotnetCHARTING:Chart ID="Chart1" runat="server">
								</dotnetCHARTING:Chart>
							</div>
							<asp:Literal runat="server" ID="ltNonData" Text="<div style='color:blue;font-weight:bold;'><br/><br/><br/>无任何数据。</div>"></asp:Literal>

							<script type="text/javascript"> 
									$("map").remove();
							</script>

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
