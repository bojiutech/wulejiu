<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_DataManager_EveryDaySpareValueList" Codebehind="EveryDaySpareValueList.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>每天抽水详细</title>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
    	<script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center; font-size:13px;margin:0 auto; width:98%; border:1px solid;">    
        <div style="text-align:center; font-size:14px; vertical-align:middle;font-weight:bold;background-color: aliceblue;">
           每天抽水详细&nbsp;&nbsp;
           <input id="Text1" type="button" value=" 返 回 " onclick="document.location.href='/Admin/Agency/DataManager/ByPlayerSpareValueCount.aspx?btm=<%=HN.Common.CommonManager.Web.Request("btm", "") %>&etm=<%=HN.Common.CommonManager.Web.Request("etm", "") %>'" />
        </div>
        <table border="1px;" style="width:100%;border-collapse:collapse; padding:0; margin:0;"  align="center">
            <tr>
                <td colspan="4">
                <asp:Repeater runat="server" ID="rptDataList">
                    <HeaderTemplate>
                        <table style="width:100%;text-align:center;border-collapse:collapse;" border="1px;">
				        <tr style="background-color:#F5F5F5;">
					        <th>
						        序号</th>
					        <th>
					            玩家</th>
					        <th>
                                抽水</th>
					        <th>
						        时间</th>				
				        </tr>
                    </HeaderTemplate>
					<ItemTemplate>
						<tr>
							<td align="center">
								<%# WebPager1.PageSize * (WebPager1.CurrentPageIndex - 1) + (Container.ItemIndex + 1)%>
							</td>
							<td align="center">
								<%# Eval("UserName")%>
							</td>
							<td align="center">
								<%# UiCommon.StringConfig.MoneyChu100(Eval("SpareMoney"))%>
							</td>
							<td align="center">
								<%# Eval( "CountTime","{0:yyyy-MM-dd HH:mm:ss}" )%>
							</td>							
						</tr>
					</ItemTemplate>
					<FooterTemplate>
                        </table>                      
                    </FooterTemplate>
				</asp:Repeater>
                </td>
            </tr>
            <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>暂无数据...</td></tr>"></asp:Literal>
        </table> 
        <div style="text-align: right;width:100%; border:1px;">
			    <webdiyer:AspNetPager ID="WebPager1" PageSize="20" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" OnPageChanging="WebPager1_PageChanging">
			    </webdiyer:AspNetPager>
        </div>         
    </div>
    </form>
</body>
</html>
