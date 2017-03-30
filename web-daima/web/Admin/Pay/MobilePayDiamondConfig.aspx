<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MobilePayDiamondConfig.aspx.cs" Inherits="HN.Admin.Admin.Pay.MobilePayDiamondConfig" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <caption>
            <font color='red'><strong>手游充值钻石配置</strong></font></caption>
        <tr>
            <th>
                ID
            </th>
            <th>
                充值RMB
            </th>
            <th>
                充值钻石
            </th>
            <th>
                备注
            </th>
            <th>
                操作
            </th>
        </tr>
        <asp:Repeater runat="server" ID="rptDataList">
            <ItemTemplate>
                <tr>
                    <td align="center">
                        <%# Eval( "ID" )%>
                    </td>
                    <td align="center">
                        <%# Eval("PayRMB").ToString()%>
                    </td>
                    <td align="center">
                        <%# Eval("PayChip").ToString()%>
                    </td>
                    <td align="center">
                        <%# Eval("Remark").ToString()%>
                    </td>
                    <td align="center">
                        <a href="MobilePayDiamondConfig.aspx?action=edit&GameType=<%=GameType %>&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>">
                            修改</a>&nbsp;&nbsp; <a href="MobilePayDiamondConfig.aspx?action=del&GameType=<%=GameType %>&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>"
                                onclick="javascript:return confirm('确定要删除吗？\r\n注意：删除后将不会恢复!');">刪除</a>
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="ltNonData" runat="server" Text="<tr><td colspan='3'>暂无任何数据！</td></tr>"></asp:Label>
        <tr>
            <td align="left" colspan="4">
                <webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                    FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                    PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                    ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                    UrlPaging="True" AlwaysShow="True" PageSize="20">
                </webdiyer:AspNetPager>
            </td>
        </tr>
    </table>
    <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table" style="margin-top: 25px;">
        <tr>
            <th colspan="2">
                添加/修改手游充值配置&nbsp;&nbsp;&nbsp;<a href="MobilePayDiamondConfig.aspx?GameType=<%=GameType %>">添加</a>
            </th>
        </tr>
        <tr>
            <th align="right">
                充值RMB：
            </th>
            <td align="left">
                <asp:TextBox runat="server" ID="txtPayRMB" CssClass="put"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtPayRMB"
                    Display="Dynamic" ErrorMessage="请输入充值RMB"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <th align="right">
                充值钻石：
            </th>
            <td align="left">
                <asp:TextBox runat="server" ID="txtPayChip" CssClass="put"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPayChip"
                    Display="Dynamic" ErrorMessage="请输入充值筹码"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <th align="right">
                备注：
            </th>
            <td align="left">
                <asp:TextBox runat="server" ID="txtRemark" CssClass="put"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <th align="right">
                &nbsp;
            </th>
            <td align="left">
                <asp:Button runat="server" ID="btnSubmit" CssClass="put" Text=" 添 加 " OnClick="btnSubmit_Click" />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>