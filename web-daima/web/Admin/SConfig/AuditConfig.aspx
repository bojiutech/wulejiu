<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AuditConfig.aspx.cs" Inherits="AuditConfig" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        .admin_table { }
        .admin_table td { text-align: center; }
        .admin_table td { height: 30px; line-height: 30px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="11">
                <strong>功能开关管理</strong>
            </td>
        </tr>
        <tr>
            <td class="title_03" colspan="6" style="display: none;">
                &nbsp;<a href="AuditAdd.aspx">添加</a>
            </td>
        </tr>
        <tr>
            <td>
                序号
            </td>
            <td>
                模块名称
            </td>
            <td>
                安卓（开关）
            </td>
            <td>
                苹果（开关）
            </td>
            <%if (ConfigurationManager.AppSettings["U3DButtons"] == "1")
              { %>
            <td>
                PC（开关）
            </td>
            <%} %>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="rptAudit" runat="server">
            <ItemTemplate>
                <tr>
                    <td>
                        <%# Container.ItemIndex + 1%>
                    </td>
                    <td>
                        <%# Eval("AttrName")%>
                    </td>
                    <td>
                        <%#Convert.ToBoolean(Eval("AdrOpen")) ? "开" : "关"%>
                    </td>
                    <td>
                        <%#Convert.ToBoolean(Eval("IosOpen")) ? "开" : "关"%>
                    </td>
                    <%if (ConfigurationManager.AppSettings["U3DButtons"] == "1")
                      { %>
                    <td>
                        <%#Convert.ToBoolean(Eval("PcOpen")) ? "开" : "关"%>
                    </td>
                    <%} %>
                    <td>
                        <a href='AuditAdd.aspx?type=edit&id=<%# Eval("ID") %>'>修改</a>
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
    </table>
    <h3 style="color: Red;">
        注意：根据苹果审核政策的原因，部分功能请审核通过后也不要开启，否则如因此导致的app下架或者开发者账号被封导致人民币无法取出，本公司概不负责</h3>
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
            <td height="5">
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
