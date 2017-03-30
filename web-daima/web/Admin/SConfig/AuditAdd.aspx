<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AuditAdd.aspx.cs" Inherits="AuditAdd" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="/css/css.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        .admin_table { }
        .admin_table td { height: 30px; line-height: 30px; padding: 5px; }
    </style>
    <script src="/Public/js/jquery.js" type="text/javascript"></script>
</head>
<body>
    <form name="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tbody>
            <tr>
                <td colspan="2" class="title_03">
                    <strong>功能模块开关添加/修改</strong>
                </td>
            </tr>
            <tr>
                <td align="right">
                    模块名称：
                </td>
                <td align="left">
                    <asp:Label runat="server" ID="lbname"></asp:Label>
                    <asp:HiddenField runat="server" ID="hidKey" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    安卓：
                </td>
                <td align="left">
                    <asp:CheckBox runat="server" ID="chkAndroid" />
                    &nbsp;&nbsp;<label style="color: Red;">注意：保险箱里包含转账功能，转账开启，保险箱也默认开启</label>
                </td>
            </tr>
            <tr>
                <td align="right">
                    苹果：
                </td>
                <td align="left">
                    <asp:CheckBox runat="server" ID="chkIos" />
                    &nbsp;&nbsp;<label style="color: Red;">注意：保险箱里包含转账功能，转账开启，保险箱也默认开启</label>
                </td>
            </tr>
            <tr style='<%=ConfigurationManager.AppSettings["U3DButtons"] == "1"?"":"display:none" %>'>
                <td align="right">
                    U3d/PC：
                </td>
                <td align="left">
                    <asp:CheckBox runat="server" ID="chkPc" />
                    &nbsp;&nbsp;<label style="color: Red;">注意：保险箱里包含转账功能，转账开启，保险箱也默认开启（仅U3d平台的PC，关闭、开启功能方可有效）</label>
                </td>
            </tr>
            <tr>
                <td align="right">
                    &nbsp;
                </td>
                <td align="left">
                    <div style="color: Red;" runat="server" id="div_Rs">
                    </div>
                    <asp:Button ID="Button1" runat="server" Text="提交" OnClick="Button1_Click" />
                    &nbsp;&nbsp;<asp:Button ID="bat_back" runat="server" Text="返回" OnClick="bat_back_Click" />
                </td>
            </tr>
        </tbody>
    </table>
    </form>
    <script type="text/javascript">
        function MySubmit() {
            if (document.getElementById("txtname").value == '') {
                alert('温馨提示：\n\n请输入模块名称！');
                document.getElementById("txtname").focus();
                return false;
            }
            if (document.getElementById("txtkey").value == '') {
                alert('温馨提示：\n\n请输入模块KEY！');
                document.getElementById("txtkey").focus();
                return false;
            }
            $("#div_Rs").html("数据提交中，请耐心等待...");
            return true;
        }
    </script>
</body>
</html>
