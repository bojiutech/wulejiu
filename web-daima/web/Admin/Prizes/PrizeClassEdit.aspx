<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PrizeClassEdit.aspx.cs"
    Inherits="Bzw.Admin.Admin.Prizes.PrizeClassEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
    <table border="1" align="left" width="60%" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF">
        <tr>
            <td>
                类别名称：
            </td>
            <td>
                <input type="text" id="txtClass" name="txtClass" maxlength="20" class="put" value="<%=name %>" />
            </td>
        </tr>
        <br />
        <tr>
            <td>
                类别描述：
            </td>
            <td>
                <input type="text" id="txtDes" name="txtDes" class="put" value="<%=dec %>" />
            </td>
        </tr>
                    <tr>
                <td >
                    图片地址2：
                </td>
                <td >
                    <asp:FileUpload ID="fuImg" runat="server" />
                    <asp:Label ID="lbimg" runat="server"></asp:Label><span style="font-size: 18px;
                        color: Red;">52 X 52，背景透明PNG</span>
                </td>
            </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Button ID="btnEdit" runat="server" Text=" 修  改 " OnClick="btnEdit_Click" class="put" />
            </td>
        </tr>
    </table>
    <script type="text/javascript">
        <!--
        function onFormSubmit(f) {

            var msgfix = '温馨提示：\n\n[';
            var msgend = '] 请输入大于或等于零的数字！';

            if (!alertNull(document.getElementById("txtClass"), '温馨提示：\n\n请输入分类名称！')) {
                return false;
            }

            return true;
        }
         //-->
    </script>
    </form>
</body>
</html>
