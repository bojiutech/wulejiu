<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameContestRank.aspx.cs"
    Inherits="Admin_Games_GameContestRank" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        class="admin_table2">
        <tr>
            <td align="center" bgcolor="F2F8FF" class="title_03">
                <strong>玩家比赛排行榜 </strong>&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <strong>比赛场次：</strong><asp:DropDownList
                    ID="ddlMatchID" runat="server">
                </asp:DropDownList>
                &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <strong>清理比赛数据：</strong>从<asp:TextBox
                    runat="server" ID="txtStartMatch">
                </asp:TextBox>
                到<asp:TextBox runat="server" ID="txtEndMatch">
                </asp:TextBox>&nbsp;&nbsp;&nbsp;<asp:Button runat="server" OnClientClick="javascript:if (!confirm('确认要删除？')) { window.event.returnValue = false; } "
                    ID="btnClearData" Text="立即清理" OnClick="btnClearData_Click" />
                &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<asp:Button runat="server" OnClientClick="javascript:if (!confirm('确认要删除全部数据？')) { window.event.returnValue = false; } "
                    ID="btnClearAllData" Text="清理全部" OnClick="btnClearAllData_Click" />
            </td>
            <script type="text/javascript">
                $(document).ready(function () {
                    var startSortField = GetRequest("matchid", "");
                    if (startSortField != "") {
                        DropSetByValue("ddlMatchID", startSortField);
                    }
                    $("#ddlMatchID").change(function () {
                        var st = $("#ddlMatchID option:selected");
                        var url = location.href;
                        url = SetUrlParam(url, "matchid=" + st.val().Trim());
                        location.href = url;
                    });
                })
            </script>
        </tr>
    </table>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <th>
                用户ID
            </th>
            <th>
                用户名
            </th>
            <th>
                排名
            </th>
            <th>
                游戏名
            </th>
        </tr>
        <asp:Repeater ID="rptDataList" runat="server">
            <ItemTemplate>
                <tr>
                    <td align="center" style="width: 5%;">
                        <%# Eval("UserID") %>
                    </td>
                    <td align="center" style="width: 10%;">
                        <%# Eval("UserName") %>
                    </td>
                    <td align="center" style="width: 10%;">
                        <%# Eval("RankNum")%>
                    </td>
                    <td align="center" style="width: 10%;">
                        <%# Eval("ComName")%>
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>暂无记录...</td></tr>"></asp:Literal>
        <tr>
            <td colspan="8">
                <div id="page_link" class="page_link">
                    <webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条"
                        FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                        PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                        ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                        UrlPaging="True" AlwaysShow="True" PageSize="20">
                    </webdiyer:AspNetPager>
                </div>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
