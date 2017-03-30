<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="leftMianDetailByUser.aspx.cs"
    Inherits="Bzw.Web.AgencyAdmin.leftMianDetailByUser" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head2" runat="server">
    <title>我的下线代理</title>
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <style type="text/css">
        *
        {
            font-family: Arial, '宋体';
        }
    </style>
</head>
<body>
    <form id="form2" runat="server">
    <div style="text-align: center; font-size: 13px; padding: 5px;">
        <span runat="server" id="span_title" style="color: Red"></span>&nbsp;|&nbsp; <span
            runat="server" id="span1"></span>
    </div>
    <div style="text-align: center; font-size: 13px;">
        <table border="1" cellpadding="3" style="width: 75%; border-collapse: collapse;">
            <tr>
                <td>
                    <table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" style="font-size: 12px; font-family: 宋体;">
	<tr>
		
				<td style="padding-left:10px; height:30px; ">
					帐号:
                    <asp:Label runat="server" Text="" ID="lab_UserName"></asp:Label>
                 
				</td>
				<td>
					真实姓名:  <asp:Label runat="server" Text="" ID="lab_TrueName"></asp:Label>
				</td>
				
				<td>
					帐号金币:<span style="color: Red"><asp:Label runat="server" Text="" ID="lab_socre"></asp:Label></span>
                	
				</td>
				<td>
				    抽水比例: <span style="color: Red"><asp:Label runat="server" Text="" ID="lab_bfb"></asp:Label></span>%
				</td>
			
	
		<td>
                    给代理充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_DlSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_DlSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    给玩家充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_WjSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_WjSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    提代理充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TDlSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TDlSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    提玩家充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TWjSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TWjSum_Jewels"></asp:Label></span>
                </td>

	</tr>
</table>
                </td>
            </tr>
            <tr>
                <td>
                    <table border="1px;" cellpadding="3" style="width: 100%; border-collapse: collapse;
                        margin: 0;">
                        <tr>
                            <td align="left">
                                <input maxlength="50" type="text" id="txtKey" name="txtKey" size="32" />&nbsp;
                                <input type="button" value="搜索" onclick="OnSearch();" />&nbsp;
                                <input type="button" value="刷新" onclick="RefreshMe();" />
                                <script>
                                    var pkey = "请输入直属玩家帐号或真实姓名";
                                    var o = $("#txtKey");
                                    o.val(decodeURIComponent(GetRequest("key", pkey)));
                                    o.css("color", "gray");
                                    o.focus(function () { if (o.val().Trim() == pkey) { o.css("color", "black"); o.val(""); } });
                                    o.blur(function () { if (o.val().Trim() == "") { o.css("color", "gray"); o.val(pkey); } });

                                    function OnSearch() {
                                        if (o.val().Trim() == "" || o.val().Trim() == pkey) {
                                            alert("请先输入要搜索的直属玩家帐号或真实姓名。");
                                            return;
                                        }
                                        LocationToMeParam("key=" + encodeURIComponent(o.val().Trim()));
                                    }
                                </script>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <table style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px;
                                    padding: 0px;" border="1px;" id="TABLE1">
                                    <tr>
                                        <th>
                                            游戏帐号
                                        </th>
                                        <th>
                                            玩家昵称
                                        </th>
                                        <th>
                                            玩家姓名
                                        </th>
                                        <th>
                                            银行<%=UiCommon.StringConfig.MoneyName%>
                                        </th>
                                        <th>
                                            钱包<%=UiCommon.StringConfig.MoneyName %>
                                        </th>
                                        <th>
                                           钻石
                                        </th>
                                        <th>
                                            状态
                                        </th>
                                    </tr>
                                    <asp:Repeater ID="rptDataList" runat="server">
                                        <ItemTemplate>
                                            <tr>
                                                <td>
                                                    <%# Eval("UserName")%>
                                                </td>
                                                <td>
                                                    <%# Eval("NickName")%>
                                                </td>
                                                <td>
                                                    <%# Eval("TrueName")%>
                                                </td>
                                                <td>
                                                    <%#Eval("BankMoney") %>
                                                </td>
                                                <td>
                                                    <%# UiCommon.StringConfig.MoneyChu100(Eval("WalletMoney"))%>
                                                </td>
                                                <td>
                                                    <%# UiCommon.StringConfig.MoneyChu100(Eval("Jewels"))%>
                                                </td>
                                                <td>
                                                    <font style='color: <%# Convert.ToInt32(Eval("Disabled")) ==0?"black":"red"%>'>
                                                        <%# Convert.ToInt32( Eval( "Disabled" ) ) == 0 ? "正常" : "禁用"%>
                                                    </font>
                                                </td>
                                            </tr>
                                        </ItemTemplate>
                                    </asp:Repeater>
                                    <asp:Label ID="lbNonData" runat="server" Text="<tr><td colspan='6'>没有记录！</td></tr>"
                                        Visible="false"></asp:Label>
                                    <tr>
                                        <td colspan="6" align="left" style="padding: 5px;">
                                            直属玩家的金币总计为：<asp:Label ID="lab_sum" runat="server" Text="0"></asp:Label>
                                            钻石总计为：<asp:Label ID="LabJewels" runat="server" Text="0"></asp:Label>
                                        </td>
                                    </tr>
                                </table>
                                <table width="100%">
                                    <tr>
                                        <td colspan="2" style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
                                            <webdiyer:AspNetPager PageSize="15" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                                FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                                                PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                                                ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                                                AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
                                            </webdiyer:AspNetPager>
                                        </td>
                                    </tr>
                                </table>
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
