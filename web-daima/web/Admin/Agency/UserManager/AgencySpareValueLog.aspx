<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgencySpareValueLog" Codebehind="AgencySpareValueLog.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js"></script>

    <script src="/Public/Js/public.js"></script>

    <script src="/Public/Js/DatePicker/WdatePicker.js"></script>
    <style type="text/css">
    <!--
    body {
	   
	    margin-top: 0px;
    }
    -->
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="11">
                    <strong>代理抽水比例修改日志</strong></td>
            </tr>
            <tr>
                <td colspan="11">
					<!--select id="selReceiverType" name="selReceiverType" onchange="OnTypeSelected(this);">
						<option value="none">=状态=</option>
						<option value="0">未处理</option>
						<option value="1">已处理</option>
					</select-->
					&nbsp;代理帐号：<input type="text" id="txtKey" name="txtKey" maxlength="20" />
					&nbsp; 操作时间：从&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" size="8" />
					&nbsp;到&nbsp;<input type="text" readonly="readonly" id="txtEndDate" name="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" size="8" />&nbsp;
					<input type="button" value=" 搜 索 " class="put" onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();" class="put" value=" 刷 新 " />

					<script type="text/javascript">
							var bd = $("#txtBeginDate");
							var ed = $("#txtEndDate");
							var o = $("#txtKey");
							var pkey = "请输入代理帐号";
							
							bd.val(decodeURIComponent(GetRequest("bd","")));
							ed.val(decodeURIComponent(GetRequest("ed","")));
							o.val(decodeURIComponent(GetRequest("key",pkey)));
							//DropSetByValue("selReceiverType",GetRequest("type","none"));
							
							if(GetRequest("key","") == "")
							{
								o.css("color","gray");
							}
							else
							{
								o.css("color","black")
							}
							o.focus(function(){if(o.val().Trim() == pkey){o.css("color","black");o.val("");}});
							o.blur(function(){if(o.val().Trim() == ""){o.css("color","gray");o.val(pkey);}});
							
							//搜索按钮
							function OnSearch()
							{
								if(bd.val().Trim() != "" || ed.val().Trim() != "" || ( o.val().Trim() != pkey && o.val().Trim() != "" ))
								{
									var url = SetUrlParam(location.href,"key="+ ( ( o.val().Trim() != pkey && o.val().Trim() != "" ) ? encodeURIComponent(o.val().Trim()) : "" ) );
									url = SetUrlParam(url,"bd="+encodeURIComponent(bd.val().Trim()));
									LocationTo(SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim())));
									return;
								}
								alert("请先输入您要搜索的代理帐号，或选择要查看的时段。");
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
					</script>
                </td>
            </tr>
            <tr>
                <th>
                    序号</th>
                <th>
                    操作人</th>
                <th>
                    代理帐号</th>
                <th>
                    操作前</th>
                <th>变动幅度</th>
                <th>
                    操作后</th>
                <th>
                    操作时间</th> 
                <th>
                    操作</th>
            </tr>
            
          <asp:Repeater ID="rptDataList" runat="server">
          <ItemTemplate>
            <tr>
                <td align="center">
                    <%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 )%></td>
                <td align="center">
                    <%# Eval("UserName")%></td>
                <td align="center">
                    <%# Eval("AgencyName") %></td>
                <td align="center">
                    <%# Eval("BPercent")%>%</td>
                <td align="center">
                   <%# Eval("Change")%></td>
                <td align="center">
                    <%# Eval("APercent")%>%</td>
                <td align="center">
                    <%# Eval("AddTime")%></td>
                <td align="center">
                    <a href='AgencySpareValueLog.aspx?params=<%# Eval("ID")+"&url="+Utility.Common.CurrentPageUrl %>' onclick="javascript:return confirm('你确定要删除这条记录吗？');">删除</a></td>
            </tr>
         </ItemTemplate>
           </asp:Repeater>
            <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='12'>暂无数据...</td></tr>"></asp:Literal>
            <tr>
                <td colspan="12" align="right">
                    <div id="page_link" class="page_link">
                        <webdiyer:AspNetPager PageSize="20" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
						</webdiyer:AspNetPager>
                    </div> 
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
