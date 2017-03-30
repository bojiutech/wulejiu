<%@ Page Language="C#" AutoEventWireup="true" Codebehind="DateChart.aspx.cs" Inherits="DataAnaly.Analy.Chart.DateChart" %>

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
						<li class="active" onclick="SetForms(0)"><%=type == "1" ? "新玩家每日图形数据分析" : "每日图形数据分析" %></li>
					</ul>
					<div class="clear">
					</div>
				</div>
				<div class="forms">
					<ul class="formShow">
						<li style="text-align: center;">
							<br />
							&nbsp;&nbsp;<input type="checkbox" name="ctype" id="cbxReg" title="按注册人数" value="1" /><label
								for="cbxreg" style="cursor: pointer;">按注册人数</label>
							&nbsp;&nbsp;<input type="checkbox" name="ctype" id="cbxLogin" title="按登录人数" value="1" />
							<label for="cbxLogin" style="cursor: pointer;">
								按登录人数</label>&nbsp;&nbsp;<input type="checkbox" id="cbxOnline" name="ctype" title="按平均在线人数"
									value="1" /><label for="cbxOnline" style="cursor: pointer;">按平均在线人数</label>&nbsp;&nbsp;<input
										type="checkbox" name="ctype" id="cbxPay" title="按充值人数" value="1" /><label for="cbxPay"
											style="cursor: pointer;">按充值人数</label>&nbsp;&nbsp;<%if( type == "0" )
															   {%>
							<input type="checkbox" name="ctype" id="cbx24A" title="注册24小时后登录游戏的人数" value="1" /><label
								for="cbx24A" style="cursor: pointer;">注册24小时后登录游戏的人数</label>
							&nbsp;&nbsp;<input type="checkbox" name="ctype" id="cbx24B" title="注册24小时内登录游戏的人数"
								value="1" />
							<label for="cbx24B" style="cursor: pointer;">
								注册24小时内登录游戏的人数</label><br />
							<span style="margin-left: 150px;">
								<%}
		  else
		  { %>
								<span>
									<%} %>
									日期：<input type="text" name="txtBeginDate" id="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;&nbsp;
					到<input type="text" name="txtEndDate" id="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />
									&nbsp;&nbsp;<input type="radio" id="rdLine" name="chart" title="曲线图" value="line" /><label
										for="rdLine" style="cursor: pointer;">曲线图</label>&nbsp;&nbsp;<input type="radio"
											id="rdPillar" name="chart" title="柱状图" value="pillar" /><label for="rdPillar" style="cursor: pointer;">柱状图</label>&nbsp;&nbsp;<input
												type="button" onclick="OnSearch()" value="确定" class="btnPublic" />&nbsp;&nbsp;<input
													type="button" class="btnPublic" value="清空" onclick="Clear();"></span>

								<script type="text/javascript">
								
								var bd=$("#txtBeginDate");
								var ed=$("#txtEndDate");
								bd.val(decodeURIComponent(GetRequest("bd", "")));
								ed.val(decodeURIComponent(GetRequest("ed", "")));
								var rg=decodeURIComponent(GetRequest("rg", "0"));//注册
								var ln=decodeURIComponent(GetRequest("ln", "0"));//登录
								var ol=decodeURIComponent(GetRequest("ol", "0"));//平均在线
								var pa=decodeURIComponent(GetRequest("pa", "0"));//充值
								var ha=decodeURIComponent(GetRequest("ha", "0"));//注册24小时后
								var hb=decodeURIComponent(GetRequest("hb", "0"));//注册24小时内
								var ct=decodeURIComponent(GetRequest("ct", "line"));
								if(rg=="1")
								{
									$("#cbxReg").attr("checked",true);
								}
								if(ln=="1")
								{
									$("#cbxLogin").attr("checked",true);
								}
								if(ol=="1")
								{
									$("#cbxOnline").attr("checked",true);
								}
								if(pa=="1")
								{
									$("#cbxPay").attr("checked",true);
								}
								if(hb=="1"&&$("#cbx24B").length>0)
								{
									$("#cbx24B").attr("checked",true);
								}
								if(ha=="1"&&$("#cbx24A").length>0)
								{
									$("#cbx24A").attr("checked",true);
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
									if (bd.val().Trim()==""||ed.val().Trim()==""||$("input[type='checkbox'][name='ctype']:checked").length<=0||$("input[type='radio'][name='chart']:checked").length<=0)
									{
										Msg("请输入查看的开始日期和结束日期并选择查看图形功能（如按注册、按登录等）、图形类型（如曲线图或柱状图）！", 300);
										return;
									}
									url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
									url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));									
									if($("#cbxLogin").is(":checked"))
									{
										url = SetUrlParam(url, "ln=1");
									}
									if($("#cbxPay").is(":checked"))
									{
										url = SetUrlParam(url, "pa=1");
									}
									if($("#cbxOnline").is(":checked"))
									{
										url = SetUrlParam(url, "ol=1");
									}
									if($("#cbxReg").is(":checked"))
									{
										url = SetUrlParam(url, "rg=1");
									}
									if($("#cbx24B").length>0&&$("#cbx24B").is(":checked"))
									{
										url = SetUrlParam(url, "hb=1");
									}
									if($("#cbx24A").length>0&&$("#cbx24A").is(":checked"))
									{
										url = SetUrlParam(url, "ha=1");
									}
									var ct;
									if($("#rdPillar").is(":checked"))
									{
										ct=encodeURIComponent($("#rdPillar").val().Trim())
									}
									else
									{
										ct=encodeURIComponent($("#rdLine").val().Trim())
									}
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
								</script></li>
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
