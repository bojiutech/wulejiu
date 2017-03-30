<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PhoneExchange.aspx.cs"
    Inherits="Bzw.Admin.Admin.Pay.PhoneExchange" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
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
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="11">
                <strong><font color="red">手游金币购买设置</font></strong>
            </td>
        </tr>
        <tr>
            <td>
                序号
            </td>
            <td>
                商品KEY
            </td>
            <td>
                所需RMB
            </td>
            <td>
                金币
            </td>
            <td>
                描述
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="PrizesHList" runat="server">
            <ItemTemplate>
                <tr>
                    <td>
                        <%=TableId=TableId+1 %>
                    </td>
                    <td>
                        <%# Eval("ExKey")%>
                    </td>
                    <td>
                        <%# Eval("CostMoney")%>
                    </td>
                    <td>
                        <%# Eval("CoinCount")%>
                    </td>
                    <td>
                        <%# Eval("ExCaption")%>
                    </td>
                    <td>
                        &nbsp;<a href='PhoneExEdit.aspx?id=<%# Eval("ID") %>'> 修改</a>&nbsp;<a href='PhoneExDel.aspx?id=<%# Eval("ID") %>'
                            onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');"><font color="red">删除</font></a>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="NoPrizesHList" runat="server" Text="<tr><td colspan='8' align='center'>暂无任何记录！</td></tr>"
            Visible="false"></asp:Label>
        <tr>
            <td colspan='11' align='right'>
                <div id="page_link" class="page_link">
                    <webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                        FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                        PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                        ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                        UrlPaging="True" AlwaysShow="True" PageSize="20">
                    </webdiyer:AspNetPager>
                </div>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
