<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="RewardRankEdit.aspx.cs" Inherits="Bzw.Admin.Admin.SConfig.RewardRankEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
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
                <td colspan="2" class="title_03">
                    <strong>修改各阶层奖励</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    层级：</td>
                <td width="83%" align="left">
                    <%=Rank %></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    类别：</td>
                <td width="83%" align="left">
                    <%=(RewardType=="1"? "分享":"邀请")%></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    数量条件：
                </td>
                <td width="83%" align="left">
                    <input type="text" value="<%=RankLimit %>" id="RankLimit" name="RankLimit" class="put"
                        maxlength="10" />
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖励：
                </td>
                <td width="83%" align="left">
                    <input type="text" id="Reward" name="Reward" value="<%=Reward %>" class="put" maxlength="10" />
                </td>
            </tr>
             <tr>
                <td width="17%" align="right">
                   备注：</td>
                <td width="83%" align="left"><%=RewardDes%>
                </td>
            </tr>

            <tr>
                <td width="17%" align="right">
                    <input type="hidden" name="action2" value="edit" /></td>
                <td width="83%" align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 "  OnClick="Reward_Edit" class="put"/>
                    <input id="button" type="button" value="返 回" onclick="javascript:history.back();" class="put" />
                    </td>
            </tr>
        </table>
    </form>
</body>
</html>

