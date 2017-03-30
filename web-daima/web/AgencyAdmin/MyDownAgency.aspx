<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MyDownAgency.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.MyDownAgency" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>我的下线代理</title>
	<script src="/Public/Js/jquery.js"></script>
	<script src="/Public/Js/public.js"></script>
	<style type="text/css">
		*{font-family:Arial,'宋体';}
	</style>
</head>
<body>
	<form id="form1" runat="server">
		<div style="text-align: center; font-size: 13px;">
        
        <span runat="server" id="span_title" style="color: Red"></span>
		
		</div>
		<div style="text-align: center; font-size: 13px;">
			<table border="1" cellpadding="3" style="width: 75%; border-collapse: collapse;">
				<tr>
					<td align="left">
						<input maxlength="50" type="text" id="txtKey" name="txtKey" size="27" />&nbsp;
						<input type="button" value="搜索" onclick="OnSearch();" />&nbsp;
						<input type="button" value="刷新" onclick="RefreshMe();" />
						<script>
						    var pkey = "请输入直属代理帐号或真实姓名";
						    var o = $("#txtKey");
						    o.val(decodeURIComponent(GetRequest("key", pkey)));
						    o.css("color", "gray");
						    o.focus(function () { if (o.val().Trim() == pkey) { o.css("color", "black"); o.val(""); } });
						    o.blur(function () { if (o.val().Trim() == "") { o.css("color", "gray"); o.val(pkey); } });

						    function OnSearch() {
						        if (o.val().Trim() == "" || o.val().Trim() == pkey) {
						            alert("请先输入要搜索的直属代理帐号或真实姓名。");
						            return;
						        }
						        LocationToMeParam("key=" + encodeURIComponent(o.val().Trim()));
						    }
						</script>
					</td>
				</tr>
				<tr>
					<td colspan="5">
						<table style="width: 100%; border-collapse: collapse; padding: 0; margin: 0;" border="1">
							<tr>
								<th>
									代理商帐号</th>
								<th>
									代理商姓名</th>
                                    <th>
									直属代理商</th>
								<th>
									帐上<%=UiCommon.StringConfig.MoneyName %></th>
                                    <th>
									账上钻石</th>
								<th>
									状态</th>
								<th>
									抽水比例</th>
								<th>
									功能
								</th>
							</tr>
							<asp:Repeater ID="rptDownAgencyList" runat="server">
								<ItemTemplate>
									<tr>
										<td>
											<%# Eval("AgencyName")%>
										</td>
										<td>
											<%# Eval("TrueName")%>
										</td>
                                        <td>
											<%# Eval("TrueName")%>
										</td>
										<td>
											<%# UiCommon.StringConfig.MoneyChu100(Eval("Account"))%>
										</td>
                                        <td>
											<%# UiCommon.StringConfig.MoneyChu100(Eval("Jewels"))%>
										</td>
										<td>
											<font style='color: <%# Convert.ToInt32(Eval("IsTaboo")) ==1?"black":"red"%>'>
												<%# Convert.ToInt32(Eval("IsTaboo")) ==1?"正常":"停用"%>
											</font>
										</td>
										<td>
											<%# Eval("SpareValue")%>%
										</td>
										<td>

                                         
											<%# Agency.Default.HasGiveToAgency(this.AgencyName) ? "<a href=\"AgencyToBank.aspx?typeID=1&stype=1&agencyName=" + Server.UrlEncode(Eval("AgencyName").ToString()) + "&trueName=" + Server.UrlEncode(Eval("TrueName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">充" + UiCommon.StringConfig.MoneyName + "</a>&nbsp;|&nbsp;" : ""%>
											<%# Agency.Default.HasPickUpCashToAgency(this.AgencyName) ? "<a href=\"BankToAgency.aspx?typeID=1&stype=1&agencyName=" + Server.UrlEncode(Eval("AgencyName").ToString()) + "&trueName=" + Server.UrlEncode(Eval("TrueName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">提" + UiCommon.StringConfig.MoneyName + "</a>&nbsp;|&nbsp;" : ""%>
                                            
                                            <%# Agency.Default.HasGiveToAgency(this.AgencyName) ? "<a href=\"AgencyToBank.aspx?typeID=1&stype=2&agencyName=" + Server.UrlEncode(Eval("AgencyName").ToString()) + "&trueName=" + Server.UrlEncode(Eval("TrueName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">充钻石</a>&nbsp;|&nbsp;" : ""%>
											<%# Agency.Default.HasPickUpCashToAgency(this.AgencyName) ? "<a href=\"BankToAgency.aspx?typeID=1&stype=2&agencyName=" + Server.UrlEncode(Eval("AgencyName").ToString()) + "&trueName=" + Server.UrlEncode(Eval("TrueName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">提钻石</a>&nbsp;|&nbsp;" : ""%>
											<%--<%# Convert.ToInt32(Eval("IsTaboo")) == 1 ? "<a href='MyDownAgency.aspx?action=taboo&taboo=0&agencyid=" + Eval("AgencyID").ToString() + "&url=" + Utility.Common.CurrentPageUrl + "'>禁用帐号</a>" : "禁用帐号"%>--%>
                                             <a href="<%# "MyDownAgency.aspx?action=zhstate&id=" + Eval("AgencyID")+ "&istaboo="+ Eval("IsTaboo") + "&url="+Utility.Common.CurrentPageUrl%>"><%# Convert.ToInt32(Eval("IsTaboo")) ==1? "禁用帐号":"启用帐号"%></a>
											&nbsp;|&nbsp;<a href="ChildAgencyDetail.aspx?ID=<%# Eval("AgencyID")%>">查看资料</a>
										</td>
									</tr>
								</ItemTemplate>
							</asp:Repeater>
							<tr>
								<td colspan="7" align="left">
									&nbsp;&nbsp;直属代理的<%=this.AgencyName%>金币总计：&nbsp;&nbsp;<span runat="server" id="sapn_sum" style="color: red">0</span>
                                     &nbsp;&nbsp;钻石总计:&nbsp;&nbsp;<span runat="server" id="Span_Jewels" style="color: red">0</span>
                                    </td>
                                   
							</tr>
						</table>
						<table width="100%" border="0">
							<tr>
								<td style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
									<webdiyer:AspNetPager PageSize="20" runat="server" ID="anpPageIndex" AlwaysShow="True" CustomInfoHTML="共%PageCount%页，当前为第%CurrentPageIndex%页，每页%PageSize%条，共%RecordCount%条。" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PagingButtonSpacing="10px" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
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
