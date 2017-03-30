<%@ Page Language="C#" AutoEventWireup="true" Inherits="AwardSet" CodeBehind="AwardSet.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <style type="text/css">
    <!--
    body {
	   
	    margin-top: 0px;
    }
    -->
</style>
</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table2">
        <tr>
            <td class="title_03">
                <strong>分享邀请参数设置</strong>
            </td>
        </tr>
    </table>
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
            <td height="5">
            </td>
        </tr>
    </table>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" style="height: 25px; font-weight: bold">
                分享参数设置
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                每日分享次数限制：
            </td>
            <td align="left">
                <input type="text" id="DayShareLmt" name="DayShareLmt" value="<%=DayShareLmt %>"
                    maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                每次分享成功的奖励：
            </td>
            <td align="left">
                <input type="text" id="TimeShareAmt" name="TimeShareAmt" value="<%=TimeShareAmt %>"
                    maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                分享累计奖励次数上限：
            </td>
            <td align="left">
                <input type="text" id="TotalShareLmt" name="TotalShareLmt" value="<%=TotalShareLmt %>"
                    maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td colspan="2" style="height: 25px; font-weight: bold">
                邀请参数设置
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                邀请次数限制：
            </td>
            <td align="left">
                <input type="text" id="DayInviteLmt" name="DayInviteLmt" value="<%=DayInviteLmt %>"
                    maxlength="9" class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                每次邀请成功的奖励：
            </td>
            <td align="left">
                <input type="text" id="TimeInviteAmt" name="TimeInviteAmt" value="<%=TimeInviteAmt%>" maxlength="9"
                    class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                邀请成功的次数限制：
            </td>
            <td align="left">
                <input type="text" id="TotalInviteLmt" name="TotalInviteLmt" value="<%=TotalInviteLmt%>" maxlength="9"
                    class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                填邀请码玩家所得的奖励：
            </td>
            <td align="left">
                <input type="text" id="SuccessBeInvAmt" name="SuccessBeInvAmt" value="<%=SuccessBeInvAmt%>" maxlength="9"
                    class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td align="right" width="25%">
                发起邀请链接的玩家所获奖励：
            </td>
            <td align="left">
                <input type="text" id="SuccessInvAmt" name="SuccessInvAmt" value="<%=SuccessInvAmt%>" maxlength="9"
                    class="put">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditPric" />
            </td>
        </tr>
    </table>
    <script type="text/javascript">
        <!--
        function onFormSubmit(f) {

            var msgfix = '温馨提示：\n\n[';
            var msgend = '] 请输入大于零的数字！';

            //----------
            var DayShareLmt = document.getElementById('DayShareLmt');
            if (!alertNonNegativeNumber(DayShareLmt, msgfix + '每日分享次数限制' + msgend)) {
                return false;
            }

            var TimeShareAmt = document.getElementById('TimeShareAmt');
            if (!alertNonNegativeNumber(TimeShareAmt, msgfix + '每次分享成功的奖励' + msgend)) {
                return false;
            }

            var TotalShareLmt = document.getElementById('TotalShareLmt');
            if (!alertNonNegativeNumber(TotalShareLmt, msgfix + '分享累计奖励次数上限' + msgend)) {
                return false;
            }

            var DayInviteLmt = document.getElementById('DayInviteLmt');
            if (!alertNonNegativeNumber(DayInviteLmt, msgfix + '邀请次数限制' + msgend)) {
                return false;
            }

            var TimeInviteAmt = document.getElementById('TimeInviteAmt');
            if (!alertNonNegativeNumber(TimeInviteAmt, msgfix + '每次邀请成功的奖励' + msgend)) {
                return false;
            }

            var TotalInviteLmt = document.getElementById('TotalInviteLmt');
            if (!alertNonNegativeNumber(TotalInviteLmt, msgfix + '邀请成功的次数限制' + msgend)) {
                return false;
            }

            var SuccessBeInvAmt = document.getElementById('SuccessBeInvAmt');
            if (!alertNonNegativeNumber(SuccessBeInvAmt, msgfix + '填邀请码玩家所得的奖励' + msgend)) {
                return false;
            }

            var SuccessInvAmt = document.getElementById('SuccessInvAmt');
            if (!alertNonNegativeNumber(SuccessInvAmt, msgfix + '发起邀请链接的玩家所获奖励' + msgend)) {
                return false;
            }
            return true;
        }
         //-->
    </script>
    </form>
</body>
</html>
