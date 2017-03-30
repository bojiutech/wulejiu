<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MobileHeadPic.aspx.cs"
    Inherits="HN.Admin.Admin.Mobile.MobileHeadPic" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <style type="text/css">
        body { margin-top: 0px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2">
                <strong>手游头像审核列表</strong>
            </td>
            <td colspan="9" align="right">
                搜索用户ID：<input type="text" value="请输入用户ID" size="30" id="txtKey" name="txtKey" />&nbsp;<input
                    type="button" value=" 搜 索 " onclick="OnSearch()" class="put" />
                &nbsp;<input type="button" value=" 清 空 " class="put" onclick="RefreshMe();" />
                <script type="text/javascript">
                    var info = "请输入用户ID";
                    var o = $("#txtKey");
                    o.css("color", "gray");
                    o.blur(
							function () {
							    var oo = $(this);
							    if (oo.val().Trim() == "") {
							        oo.val(info);
							        oo.css("color", "gray");
							    }
							}
						);
                    o.focus(
							function () {
							    var oo = $(this);
							    oo.css("color", "black");
							    if (oo.val().Trim() == info) {
							        oo.val("");
							    }
							}
						);

                    var k = decodeURIComponent(GetRequest("un", ""));
                    if (k != "") {
                        o.css("color", "black");
                        o.val(k);
                    }
                    function OnSearch() {
                        var sk = o.val().Trim();
                        if (sk == "" || sk == info) {
                            alert("请先输入搜索用户ID！");
                            o.focus();
                            return;
                        }
                        LocationToMeParam("un=" + encodeURIComponent(sk));
                    }
                </script>
            </td>
        </tr>
        <tr align="center">
            <td>
                序号
            </td>
            <td>
                用户ID
            </td>
            <td>
                头像
            </td>
            <td>
                状态
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="OkPrList" runat="server">
            <ItemTemplate>
                <tr align="center">
                    <td>
                        <%=TableID = TableID+1%>
                    </td>
                    <td>
                        <%#  Eval("UserID") %>
                    </td>
                    <td>
                        <img src='/Image/users/<%#  Eval("PicPosition") %>.png' alt="用户头像" width="100" height="100" />
                    </td>
                    <td>
                        <span <%#(Eval("IsAudit").ToString()=="0"?"style='color:red'":"") %>><%# RetStatus(Eval("IsAudit").ToString())%></span>
                    </td>
                    <td>
                        <a href='EditHeadPic.aspx?id=<%# Eval("id") %>'>修改</a>&nbsp;|&nbsp;<a href='DelHeadPic.aspx?id=<%# Eval("id") %>'
                            onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');"><font color="red">删除</font></a>
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="NoPrList" runat="server" Text="<tr><td colspan='11' align='center'>暂无任何记录！</td></tr>"
            Visible="false"></asp:Label><tr>
                <td colspan='11' align='right'>
                    <div id="page_link" class="page_link">
                        <webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                            FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                            PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                            ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到"
                            UrlPaging="True" AlwaysShow="True" PageSize="20">
                        </webdiyer:AspNetPager>
                    </div>
                </td>
            </tr>
    </table>
    </form>
</body>
</html>
