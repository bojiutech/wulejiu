<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_AgencyPayLog" Codebehind="AgencyPayLog.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>代理充值记录</title>
    <link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
    	<script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>

</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="F2F8FF" class="admin_table2" style="border-collapse: collapse; border: 1px solid;">
			<tr>
				<th align="left">
					代理充值记录列表</th>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
	        <tr>
	            <td>
	                订单号：<input type="text" id="txtOrder" name="txtOrder" maxlength="40" style="width:200px;" />
					&nbsp;代理帐号：<input type="text" id="txtKey" name="txtKey" maxlength="20" />
					&nbsp; <br />提交时间：从&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" size="8" />
					&nbsp;到&nbsp;<input type="text" readonly="readonly" id="txtEndDate" name="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" size="8" />&nbsp;
					<input type="button" value=" 搜 索 " class="put" onclick="OnSearch();" />&nbsp;<input type="button" class="put" onclick="RefreshMe();" value=" 刷 新 " />
                    &nbsp;&nbsp;<input type="button" class="put" value="按提交时间批量删除" onclick="return  ChkDel();" />
					<script type="text/javascript">
						var bd = $("#txtBeginDate");
						var ed = $("#txtEndDate");
						var o = $("#txtKey");
						var ord = $("#txtOrder");
						var pkey = "请输入代理帐号";
						
						//从地址的查询参数中赋值
						bd.val(decodeURIComponent(GetRequest("bd","")));
						ed.val(decodeURIComponent(GetRequest("ed","")));
						o.val(decodeURIComponent(GetRequest("key",""))); //o.val(decodeURIComponent(GetRequest("key",pkey)));
						ord.val(decodeURIComponent(GetRequest("ord","")));
						
						//搜索按钮
						function OnSearch()
						{
						    if(bd.val().Trim() != "" || ed.val().Trim() != "" || o.val().Trim() != "" || ord.val().Trim() != "")
							{
								var url = SetUrlParam(location.href,"key="+ encodeURIComponent(o.val().Trim()) );
								url = SetUrlParam(url,"bd="+encodeURIComponent(bd.val().Trim()));
								url = SetUrlParam(url,"ord="+encodeURIComponent(ord.val().Trim()));
								LocationTo(SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim())));
								return;
							}
							alert("请先输入您要搜索的订单号、代理帐号，或选择要查看的时段。");
						}
							
                        function ChkDel(){
                            var txtBegin = document.getElementById('txtBeginDate');
                            if(txtBegin.value.trim().length==0){
                                alert('批量删除前请选择提交时间的起始点！');
                                txtBegin.focus();
                                return false;
                            }

                            var txtEnd = document.getElementById('txtEndDate');
                            if(txtEnd.value.trim().length==0){
                                alert('批量删除前请选择提交时间的结束点！');
                                txtEnd.focus();
                                return false;
                            }

                            if(confirm('确定要进行批量删除记录吗？'))
                            {
                                window.location.href='AgencyPayLog.aspx?action=batchdel&bd='+txtBegin.value.trim()+'&ed='+txtEnd.value.trim();
                            }

                            return false;
                        }
					</script>
                    
	            </td>
	        </tr>
		</table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
           <tr align="center">
                <th>
                    订单号</th>
                <th>
                    代理帐号</th>
                <th>
                    金额</th>
                <th>
                    提交时间</th>
                <th>
                    返回结果时间</th>
                <th>
                    状态</th>
                <th>
                    操作</th>
            </tr>
            <asp:Repeater ID="rpList" runat="server">
                <ItemTemplate>
                    <%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
                        <td><%# Eval("OrderID")%></td>
                        <td><%# Eval("UserName")%></td>
                        <td><%# UiCommon.StringConfig.MoneyChu100(Eval("PayMoney"))%></td>
                        <td><%# Eval("AddTime")%></td>
                        <td><%#Eval("BackTime")%>&nbsp;</td>
                        <td><font color="red">已支付</font></td>
                        <td>
                           <a href='AgencyPayLog.aspx?action=del&id=<%# Eval("PayID") %>&ord=<%#Eval("OrderID") %>&url=<%=Utility.Common.CurrentPageUrl %>' onclick="javascript:return confirm('你确定要删除当前记录吗？删除后将不能恢复!!');">删除</a>
                        </td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Literal runat="server" ID="NoDataList" Text="<tr><td colspan='10' align='center' bgcolor='#ffffff'>暂无数据...</td></tr>"></asp:Literal>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" UrlPaging="True" runat="server" ID="WebPager1" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
    </form>
</body>
</html>
