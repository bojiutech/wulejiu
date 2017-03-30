<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_UserPropEdit" Codebehind="UserPropEdit.aspx.cs" %>


<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
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
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table2">
        <tr>
            <th class="title_03">
                玩家<asp:Literal runat="server" ID="ltUserName"></asp:Literal>道具修改
            </th>
        </tr>
    </table>
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
            <td height="5">
                &nbsp;
            </td>
        </tr>
    </table>

    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bordercolor="#A4B6D7"
        bgcolor="#A4B6D7" class="admin_table">
        <tr bgcolor="#ffffff">
          
        </tr>
        <script type="text/javascript">
            var startStType = GetRequest("sttype", "");
            var startSortType = GetRequest("sorttype", "");
            var startUserType = GetRequest("usertype", "");

            var startGameNameId = GetRequest("nameid", "");
            var startKey = GetRequest("key", "");
            var key = $("#txtKey");
            key.val(startKey);
            if (startStType != "") {
                DropSetByValue("stType", startStType);
            }
            if (startSortType != "") {
                DropSetByValue("sortType", startSortType);
            }

            if (startUserType != "") {

                DropSetByValue("userType", startUserType);
            }
            else {
                DropSetByValue("userType", "realplayer");
            }
            if (startGameNameId != "") {
                DropSetByValue("nameId", startGameNameId);
            }
            function Search() {
                var st = $("#sortType option:selected");
                var sr = $("#stType option:selected");
                var su = $("#userType option:selected");
                var game = $("#nameId option:selected");
                var key1 = $("#txtKey");

                var url = location.href;
                url = SetUrlParam(url, "sorttype=" + st.val().Trim());
                url = SetUrlParam(url, "sttype=" + sr.val().Trim());
                url = SetUrlParam(url, "usertype=" + su.val().Trim());
                url = SetUrlParam(url, "nameid=" + game.val().Trim());
                url = SetUrlParam(url, "key=" + key1.val().Trim());
                location.href = url;
            }
        </script>
        <tr align="center" bgcolor="#ffffff">
            <td>
               道具
             </td>
            <td>
               数量
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="UserList" runat="server">
            <ItemTemplate>
                <tr align='center' bgcolor='#F7F8F8' onmouseout="this.style.backgroundColor='#F7F8F8'"
                    onmouseover="this.style.backgroundColor='#E1E1E1'" height='25px'>
               
                    <td>
                        <%# Eval("PropName")%>
                    </td>
                    <td>
                        <%# Eval("HoldCount")%>
                    </td>
                    <td>
                        <a href='UserPropUpdate.aspx?para=<%#Eval("PropID") %>&params=<%# Eval("UserName") %>'>修改</a>&nbsp;
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
    </table>
    <td align="left">
					<webdiyer:AspNetPager PageSize="10" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
				</td>
    <br />
    <%--<table width="100%" border="0" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        class="admin_table">
        <tr>
            <td class="title_03" align="center">
                <asp:Button runat="server" ID="btnSubmit" Text=" 修 改 " CssClass="put" OnClick="btnSubmit_Click" />&nbsp;&nbsp;&nbsp;&nbsp;<input
                    type="button" value="返 回" onclick="javascript:history.back()" class="put" />
            </td>
        </tr>
    </table>--%>
    </form>
</body>
</html>
