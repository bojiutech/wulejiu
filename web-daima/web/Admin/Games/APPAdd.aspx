<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="APPAdd.aspx.cs" Inherits="APPAdd" %>

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
                    <strong>手机游戏管理</strong>
                </td>
            </tr>
            <tr>
                <td align="right">
                    游戏名称
                </td>
                <td align="left">
                    <input name="txttitle" type="text" id="Gname" size="50" maxlength="50" runat="server"
                        class="put">
                </td>
            </tr>
            <tr style="">
                <td align="right">
                    游戏介绍
                </td>
                <td align="left">
                    <input name="txttitle" type="text" id="Gtitle" size="50" maxlength="50" value=""
                        runat="server" class="put">
                </td>
            </tr>
            <tr>
                <td align="right">
                    安卓地址：
                </td>
                <td align="left">
                    <input type="text" name="txtandroidname" id="txtandroidname" runat="server" class="put" size="50" />
                    <span style="color: red">请填写相对地址。如：/download/android.apk</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    安卓二维码地址：
                </td>
                <td align="left">
                    <input type="text" name="txtAndroidQrcode" id="txtAndroidQrcode" runat="server" class="put" size="50" />
                    <span style="color: red">请填写相对地址。如：/download/qrcode.jpg</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    苹果地址：
                </td>
                <td align="left">
                    <input type="text" name="txtapplename" id="txtapplename" runat="server" class="put" size="50" />
                    <span style="color: red">请填写相对地址。如：/download/apple.ipa</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    苹果二维码地址：
                </td>
                <td align="left">
                    <input type="text" name="txtAppleQrcode" id="txtAppleQrcode" runat="server" class="put" size="50" />
                    <span style="color: red">请填写相对地址。如：/download/qrcode.jpg</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    文件大小：
                </td>
                <td align="left">
                    <input name="txttitle" type="text" id="filesize" size="20" value="0" maxlength="50"
                        runat="server" class="put">MB
                </td>
            </tr>
            <tr>
                <td align="right">
                    图片地址：
                </td>
                <td align="left">
                    <asp:FileUpload ID="images" runat="server" />
                    <asp:Label ID="Label3" runat="server" Text=""></asp:Label><span style="font-size: 18px;
                        color: Red;">210 X 140</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    图片地址2：
                </td>
                <td align="left">
                    <asp:FileUpload ID="fuBigImg" runat="server" />
                    <asp:Label ID="Label4" runat="server" Text=""></asp:Label><span style="font-size: 18px;
                        color: Red;">420 X 150，显示在首页热门区</span>
                </td>
            </tr>
            <tr>
                <td align="right">
                    是否是热门游戏
                </td>
                <td align="left">
                    <asp:CheckBox ID="cbIsHot" runat="server" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    苹果App配置文件(.plist)：
                </td>
                <td align="left">
                    <input type="text" name="txtplist" id="txtplist" runat="server" class="put" size="50" />
                    <span style="color: red">请填写绝对地址。如：http://www.xxx.com/download/apple.plist</span>
                    <%--<asp:FileUpload ID="fload_Plist" runat="server" /><asp:Label ID="Label5" runat="server"
                        Text=""></asp:Label>--%>
                </td>
            </tr>
            <tr>
                <td align="right">
                    安卓版本号：
                </td>
                <td align="left">
                    <input name="txtapk" type="text" id="txtapk" size="50" maxlength="50" runat="server"
                        class="put" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    苹果版本号：
                </td>
                <td align="left">
                    <input name="txtios" type="text" id="txtios" size="50" maxlength="50" runat="server"
                        class="put" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    授权码：
                </td>
                <td align="left">
                    <input name="txtkey" type="text" id="txtkey" size="50" maxlength="50" runat="server"
                        class="put" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    是否自动更新：
                </td>
                <td align="left">
                    <asp:CheckBox runat="server" ID="chkUpdate" />
                </td>
            </tr>
            <tr>
                <td align="right">
                    &nbsp;
                </td>
                <td align="left">
                    <div style="color: Red;" runat="server" id="div_Rs">
                    </div>
                    <asp:Button ID="Button1" runat="server" Text="提交" OnClick="Button1_Click" OnClientClick=" return MySubmit()" />
                    &nbsp;&nbsp;<asp:Button ID="bat_back" runat="server" Text="返回" OnClick="bat_back_Click" />
            </tr>
        </tbody>
    </table>
    </form>
    <script type="text/javascript">
        function MySubmit() {
            $("#div_Rs").html("数据提交中，请耐心等待...");
            return true;
        }
    </script>
</body>
</html>
