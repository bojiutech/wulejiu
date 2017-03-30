<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LinkAdd.aspx.cs" Inherits="Bzw.Admin.Admin.SConfig.LinkAdd" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
</head>
<body>
    <form id="form1" runat="server" >
    <table border="1" align="left" width="60%" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        style="margin-bottom: 20px;" bgcolor="F2F8FF">
        <tr>
            <td>
                *友链站名：
            </td>
            <td>
                <input type="text" id="txtLink" name="txtLink" maxlength="20" class="put" />
            </td>
        </tr>
        <br />
        <tr>
            <td>
                *友链地址：
            </td>
            <td>
                <input type="text" id="txtUrl" name="txtUrl" class="put" /><span>例子：http://www.baidu.com</span>
            </td>
        </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Button ID="btnAdd" runat="server" Text=" 添 加 " OnClick="btnAdd_Click" class="put" />
            </td>
        </tr>
    </table>
    <br />
    <br />
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="11">
                <strong><font color="red">管理友情链接</font></strong>
            </td>
        </tr>
        <tr>
            <td>
                序号
            </td>
            <td>
                名称
            </td>
            <td>
                地址
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
                        <%# Eval("LinkDes")%>
                    </td>
                    <td>
                        <%# Eval("Link")%>
                    </td>
                    <td>
                        <asp:LinkButton ID="LinkButton1" runat="server" CommandArgument='<%#Eval("ID") %>'
                            OnClientClick="return confirm('是否删除')" OnClick="Del">删除</asp:LinkButton>
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
    <script type="text/javascript">
        <!--
        function onFormSubmit(f) {

            var msgfix = '温馨提示：\n\n[';
            var msgend = '] 请输入大于或等于零的数字！';

            if (!alertNull(document.getElementById("txtLink"), '温馨提示：\n\n请输入友链名称！')) {
                return false;
            }
            if (!alertNull(document.getElementById("txtUrl"), '温馨提示：\n\n请输入友链地址！')) {
                return false;
            }
            return true;
        }
         //-->
    </script>
    </form>
</body>
</html>
