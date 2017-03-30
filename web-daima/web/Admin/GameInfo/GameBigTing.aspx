<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameBigTing"
    CodeBehind="GameBigTing.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <style type="text/css">
        body { margin-top: 0px; }
        .style1 { height: 30px; }
    </style>
    <script type="text/javascript" language="javascript">
        function MyFile(n) {
            if (n == 2) {
                var filename = document.getElementById("FileUpload_S")
                if (filename == null || filename.value == null || filename.value.length < 1) {
                    //  alert("请选择文件后再上传");
                    $("#span_rs2").html('请选择文件后再上传');
                    return false;
                } else {
                    $("#span_rs2").html('文件上传中....');
                    return true;
                }
            } else {
                var filename = document.getElementById("FileUploadAll")
                if (filename == null || filename.value == null || filename.value.length < 1) {

                    $("#span_rs1").html('请选择文件后再上传');
                    return false;
                } else {
                    $("#span_rs1").html('文件上传中....');
                    return true;
                }

            }
        }
        function FileJudge3() {
            var filename = document.getElementById("fuAndriod")
            if (filename == null || filename.value == null || filename.value.length < 1) {
                $("#span_rs3").html('请选择文件后再上传');
                return false;
            } else {
                $("#span_rs3").html('文件上传中....');
                return true;
            }
        }
        function FileJudge4() {
            var filename = document.getElementById("fuApple")
            if (filename == null || filename.value == null || filename.value.length < 1) {
                $("#span_rs4").html('请选择文件后再上传');
                return false;
            } else {
                $("#span_rs4").html('文件上传中....');
                return true;
            }
        }
    </script>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="2">
                <strong>游戏大厅信息管理</strong>
                <input runat="server" id="txt_mid" type="hidden" />
            </td>
        </tr>
        <tr style="display: none">
            <td width="20%" align="right">
                版本号：
            </td>
            <td width="80%" align="left">
                <input name="Main_copy" type="text" id="Main_copy" runat="server" value="" size="50"
                    maxlength="50" class="put" />
            </td>
        </tr>
        <tr style="display: none">
            <td align="right">
                应用平台：
            </td>
            <td align="left">
                <input name="Main_use" type="text" runat="server" id="Main_use" value="" size="50"
                    maxlength="100" class="put" />
            </td>
        </tr>
        <tr>
            <td align="right">
                下载地址：
            </td>
            <td align="left">
                <input name="Down_address" type="text" id="Down_address" value="" runat="server"
                    size="50" maxlength="100" class="put" />&nbsp;<asp:FileUpload ID="FileUploadAll"
                        runat="server" />
                &nbsp;
                <asp:Button ID="Button2" runat="server" Text="上传" OnClick="Button2_Click" OnClientClick="return MyFile(1)" />
                &nbsp;<span runat="server" id="span_rs1" style="color: Red;"></span>
            </td>
        </tr>
        <tr style="display: none">
            <td align="right">
                简洁版下载地址：
            </td>
            <td align="left">
                <input name="Down_saddress" type="text" id="Down_saddress" runat="server" value=""
                    size="50" maxlength="100" class="put" />
                <asp:FileUpload ID="FileUpload_S" runat="server" />
                &nbsp;
                <asp:Button ID="Button3" runat="server" Text="上传" OnClientClick="return MyFile(2)"
                    OnClick="Button3_Click" />&nbsp;<span runat="server" id="span_rs2" style="color: Red;"></span>
            </td>
        </tr>
        <tr>
            <td align="right">
                安卓版下载地址：
            </td>
            <td align="left">
                <input type="text" id="AndroidUrl" name="AndroidUrl" runat="server" value="/download/anzhuo.apk"/>
            </td>
        </tr>
        <tr>
            <td align="right">
                安卓版二维码地址：
            </td>
            <td align="left">
                <input type="text" id="AndroidCode" name="AndroidCode" runat="server" value="/download/qrcode.jpg"/>
            </td>
        </tr>
        <tr>
            <td align="right">
                苹果版下载地址：
            </td>
            <td align="left">
                <input type="text" id="AppleUrl" name="AppleUrl" runat="server" value="/download/apple.ipa"/>
            </td>
        </tr>
        <tr>
            <td align="right">
                苹果版二维码地址：
            </td>
            <td align="left">
                <input type="text" id="AppleCode" name="AppleCode" runat="server" value="/download/qrcode.jpg"/>
            </td>
        </tr>
        <tr style="display: none">
            <td align="right" class="style1">
                下载次数：
            </td>
            <td align="left" class="style1">
                <input name="Down_num" type="text" id="Down_num" value="" size="50" maxlength="50"
                    runat="server" class="put" />（必须输入一个数字!）
            </td>
        </tr>
        <tr>
            <td align="right">
                文件大小：
            </td>
            <td align="left">
                <input name="FileSize" type="text" id="FileSize" value="" size="50" maxlength="9"
                    runat="server" class="put" />（单位为KB,请不要加单位）
            </td>
        </tr>
        <tr style="display: none">
            <td align="right">
                图片地址：
            </td>
            <td align="left">
                <input name="Image_URL" type="text" id="Image_URL" value="" size="50" runat="server"
                    maxlength="50" class="put" />
            </td>
        </tr>
        <tr>
            <td align="right" valign="top">
                大厅介绍：
            </td>
            <td align="left">
                <textarea name="Main_info" cols="50" rows="10" id="Main_info" runat="server" class="put"></textarea>
                限500字符
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text="修改信息" class="put" OnClick="GameBigEdit" />
                <input type="hidden" name="action" value="edit" />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
