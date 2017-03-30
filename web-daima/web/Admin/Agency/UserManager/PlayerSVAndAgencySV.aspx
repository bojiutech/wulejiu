<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_PlayerSVAndAgencySV" Codebehind="PlayerSVAndAgencySV.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>玩家抽水统计</title>
	<link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js"></script>
	<script src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form1" runat="server">
   <div style="text-align:center; font-size:13px;margin:0 auto; width:98%; border:1px solid;">    
        <div style="text-align:center; font-size:14px; vertical-align:middle;font-weight:bold;background-color: aliceblue;">
           玩家抽水统计
        </div>
        <table border="1px;" style="width:100%;border-collapse:collapse; padding:0; margin:0;"  align="center">
            <tr>
                <td colspan="4">
                    玩家帐号:<input type="text" id="tusername" name="tusername" />
                    &nbsp;&nbsp;&nbsp;所属代理商:<input type="text" id="tagencyname" name="tagencyname" />
                    <input type="button" value=" 查 询 " class="put" onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();" class="put" value=" 刷 新 " />
				    <script>
						    var bd = $("#tusername");
						    var ed = $("#tagencyname");
    						
						    bd.val(decodeURIComponent(GetRequest("bd","")));
						    ed.val(decodeURIComponent(GetRequest("ed","")));
    						
						    //搜索按钮
						    function OnSearch()
						    {
							    var url = SetUrlParam(location.href,"bd="+encodeURIComponent(bd.val().Trim()) );
							    LocationTo(SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim())));
							    return;
						    }
				    </script>
                </td>
            </tr>  
            <tr>
                <td colspan="4">
                <asp:Repeater runat="server" ID="rptDataList">
                    <HeaderTemplate>
                        <table style="width:100%;text-align:center;border-collapse:collapse;" border="1px;">
				        <tr>
					        <th>
						        序号</th>
					        <th>
					            玩家帐号</th>
					        <th>
                                总贡献抽水
                            </th>
					        <th>
						        所属代理商</th>
                            <%--<th>
						        操作</th>--%>					
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
								<%# Eval( "AgencyName" )%>
							</td>							
                            <%--td align="center">
								<asp:HyperLink id="hlHistorySpareValueRecord" runat="server" NavigateUrl='<%# "SpareValueHistory.aspx?nameId="+Eval("ID") %>'>历史分水记录</asp:HyperLink>
							</td>--%>
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
			    <webdiyer:AspNetPager ID="WebPager1" PageSize="20" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True" NumericButtonCount="5">
			    </webdiyer:AspNetPager>
        </div>         
    </div>
    </form>
</body>
</html>
