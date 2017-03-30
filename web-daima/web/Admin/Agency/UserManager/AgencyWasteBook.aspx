<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgencyWasteBook" Codebehind="AgencyWasteBook.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>代理收支流水账列表</title>
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
					代理收支流水账列表</th>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
	        <tr>
	            <td>
	                <select id="selType" name="selType" onchange="OnTypeSelected(this);">
						<option value="none">=类型=</option>
						<option value="0">充值</option>
						<option value="1">抽水结算</option>
						<!--option value="2">兑换申请</option>
						<option value="3">拒绝兑换</option-->
						<option value="4">充金币</option>
						<option value="5">被充金币</option>
						<option value="6">提金币</option>
						<option value="7">被提金币</option>
						<option value="8">管理员改金币</option>
					</select>
	                &nbsp;代理ID：<input type="text" id="txtId" name="txtId" maxlength="20" />
					&nbsp;代理帐号：<input type="text" id="txtKey" name="txtKey" maxlength="20" />
					&nbsp; 记录时间：从&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" size="8" />
					&nbsp;到&nbsp;<input type="text" readonly="readonly" id="txtEndDate" name="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" size="8" />
					&nbsp;<input type="button" value=" 搜 索 " class="put" onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();" class="put" value=" 刷 新 " />
                    &nbsp;&nbsp;<input type="button" class="put" value="按记录时间批量删除" onclick="return  ChkDel();" />
					<script type="text/javascript">
						var bd = $("#txtBeginDate");
						var ed = $("#txtEndDate");
						var o = $("#txtKey");
						var uid = $("#txtId");
						var pkey = "请输入代理帐号";
						
						//从地址的查询参数中赋值
						bd.val(decodeURIComponent(GetRequest("bd","")));
						ed.val(decodeURIComponent(GetRequest("ed","")));
						o.val(decodeURIComponent(GetRequest("key",""))); //o.val(decodeURIComponent(GetRequest("key",pkey)));
						uid.val(decodeURIComponent(GetRequest("uid","")));
						DropSetByValue("selType",GetRequest("type","none"));
						
						//搜索按钮
						function OnSearch()
						{
						    if(bd.val().Trim() != "" || ed.val().Trim() != "" || o.val().Trim() != "" || uid.val().Trim() != "")
							{
								var url = SetUrlParam(location.href,"key="+ encodeURIComponent(o.val().Trim()) );
								url = SetUrlParam(url,"bd="+encodeURIComponent(bd.val().Trim()));
								url = SetUrlParam(url,"uid="+encodeURIComponent(uid.val().Trim()));
								LocationTo(SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim())));
								return;
							}
							alert("请先输入您要搜索的代理ID、代理帐号，或选择要查看的时段。");
						}
					    
					    //按类型搜索事件
						function OnTypeSelected(obj)
						{
							var value = obj.options[obj.selectedIndex].value;
							if(value == "none")
							{
								RefreshMeDelParam("(&)?type=(\\d+)");
							}
							else
							{
								LocationToMeParam("type=" + value);
							}
						}
							
                        function ChkDel(){
                            var txtBegin = document.getElementById('txtBeginDate');
                            if(txtBegin.value.trim().length==0){
                                alert('批量删除前请选择记录时间的起始点！');
                                txtBegin.focus();
                                return false;
                            }

                            var txtEnd = document.getElementById('txtEndDate');
                            if(txtEnd.value.trim().length==0){
                                alert('批量删除前请选择记录时间的结束点！');
                                txtEnd.focus();
                                return false;
                            }

                            if(confirm('确定要进行批量删除记录吗？删除后将不能恢复!!'))
                            {
                                window.location.href='AgencyWasteBook.aspx?action=batchdel&bd='+txtBegin.value.trim()+'&ed='+txtEnd.value.trim();
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
                    记录号</th>
                <th>
                    记录时间</th>
                <th>
                    类型</th>
                <th>
                    代理ID</th>
                <th>
                    代理帐号</th>
                <th>
                    操作前金币</th>
                <th>
                    变化金币</th>
                <th>
                    操作后金币</th>
                <th>
                    备注</th>
                <th>
                    操作</th>
            </tr>
            <asp:Repeater ID="rpList" runat="server">
                <ItemTemplate>
                    <%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
                        <td><%# Eval("ID")%></td>
                        <td><%# Eval("AddTime")%></td>
                        <td><%# Eval("TypeDesc")%></td>
                        <td><%# Eval("AgencyID")%></td>
                        <td><%# Eval("AgencyName")%></td>
                        <td><%# UiCommon.StringConfig.MoneyChu100(Eval("MoneyB"))%></td>
                        <td><%# UiCommon.StringConfig.MoneyChu100(Eval("ChangeMoney"))%></td>
                        <td><%# UiCommon.StringConfig.MoneyChu100(Eval("MoneyA"))%></td>
						<td><%# Eval("Remark")%>&nbsp;</td>
                        <td>
                           <a href='AgencyWasteBook.aspx?action=del&id=<%# Eval("ID") %>&url=<%=Utility.Common.CurrentPageUrl %>' onclick="javascript:return confirm('你确定要删除当前记录吗？删除后将不能恢复!!');">删除</a>
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
						<webdiyer:AspNetPager PageSize="20" UrlPaging="True" runat="server" ID="WebPager1" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
        
    </form>
</body>
</html>
