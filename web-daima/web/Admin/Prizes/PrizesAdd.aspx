<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Prizes_PrizesAdd" CodeBehind="PrizesAdd.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <style type="text/css">
    <!--
    body {
	
	    margin-top: 0px;
    }
    .tip
    {
  color:Green; font-size:large;
        }
        .ttip
        {
            color:Red; font-weight:bold;
            }
    -->
    </style>
</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" style="font-size: 20px;
  line-height: 150%;
  margin-top:10px;
  margin-bottom: 0;">
                <strong>添加奖品资料</strong>&nbsp &nbsp<span class="ttip">图片大小一定要跟规则说明（宽X高）的一样，否则网站页面可能就乱掉了！</span>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                奖品名称：
            </td>
            <td width="83%" align="left">
                <input type="text" id="Award_Name" name="Award_Name" value="" class="put" maxlength="20" />
            </td>
        </tr>
        <tr style="">
            <td height="17%" align="right">
                奖品分类：
            </td>
            <td align="left">
                <asp:DropDownList runat="server" ID="ddlClass" DataTextField="ClassName" DataValueField="ID">
                </asp:DropDownList>
            </td>
        </tr>
                <tr style="">
            <td height="17%" align="right">
                奖品分类：
            </td>
            <td align="left">
                <select name="leitype">
                    <option value="1" selected="selected">虚拟类</option>
                    <option value="2">实物类</option>
                </select>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                奖品所需<%=UiCommon.StringConfig.GoldName %>数：
            </td>
            <td width="83%" align="left">
                <input type="text" id="Award_MoneyCost" name="Award_MoneyCost" value="1" maxlength="18"
                    class="put" />
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                奖品所需游戏时长数：
            </td>
            <td width="83%" align="left">
                <input type="text" id="Award_OnLineTime" name="Award_OnLineTime" value="0" maxlength="5"
                    class="put" />小时
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                奖品数量：
            </td>
            <td width="83%" align="left">
                <input type="text" id="Award_Num" name="Award_Num" value="1" maxlength="7" class="put" />
            </td>
        </tr>
        <tr>
            <td align="right">
                奖品图片(手机端)：
            </td>
            <td align="left">
                <asp:FileUpload runat="server" ID="fuImageUrl" />( <span class="tip">216 X 168</span>，允许的类型：jpg,jpeg,gif,png（必选项）)
              
            </td>
        </tr>
        <tr>
            <td align="right">
                奖品图片(PC端)：
            </td>
            <td align="left">
                <asp:FileUpload runat="server" ID="fuImageUrl2" />( <span class="tip">400 X 400</span>，允许的类型：jpg,jpeg,gif,png（必选项）)
              
            </td>
        </tr>
        <tr>
            <td align="right">
                奖品详情图：
            </td>
            <td align="left">
                <asp:FileUpload runat="server" ID="fuImgDetail" />(<span class="tip">700 X 700</span>，允许的类型：jpg,jpeg,gif,png（必选项）)
             
            </td>
        </tr>
        <tr style=" display:none;">
            <td align="right">
                是否上传导航栏：
            </td>
            <td align="left">
                <input type="radio" name="slide" value="1" class="put" onclick="document.getElementById('fuImgSlide').disabled=false;document.getElementById('fuBigImgSlide').disabled=false;" />
                是
                <input name="slide" type="radio" value="0" checked="checked" class="put" onclick="document.getElementById('fuImgSlide').disabled=true;document.getElementById('fuBigImgSlide').disabled=true;" />
                否
                <asp:FileUpload runat="server" ID="fuImgSlide" Enabled="false" /><span class="tip">980 X 443</span>&nbsp<asp:FileUpload runat="server" ID="fuBigImgSlide" Enabled="false" />(<span class="tip">1200 X 443</span>，允许的类型：jpg,jpeg,gif)
            </td>
        </tr>
        <tr>
         <td width="17%" align="right">
                奖品属性：
            </td>
            <td align="left">
                <asp:RadioButtonList runat="server" ID="rblPP"  RepeatDirection="Horizontal">
                    <asp:ListItem Value="0" Selected="True">普通</asp:ListItem>
                    <asp:ListItem Value="1">新款</asp:ListItem>
                    <asp:ListItem Value="2">热门</asp:ListItem>
                </asp:RadioButtonList>
            </td>
        </tr>
        <tr>
            <td align="right" valign="top">
                奖品介绍：
            </td>
            <td align="left" valign="top">
                <FCKeditorV2:FCKeditor ID="Award_Info" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                </FCKeditorV2:FCKeditor>
            </td>
        </tr>
        <tr>
            <td width="17%" align="right">
                &nbsp;
            </td>
            <td width="83%" align="left">
                <asp:Button ID="Button1" runat="server" Text=" 添 加 " class="put" OnClick="Prizes_Add" />
            </td>
        </tr>
    </table>
    <script type="text/javascript">
        <!--

        function onFormSubmit(f) {

            var msgfix = '温馨提示：\n\n[';
            var msgend = '] 请输入大于或等于零的数字！';

            if (!alertNull(document.getElementById("Award_Name"), '温馨提示：\n\n请输入奖品名称！')) {
                return false;
            }

            //----------
            if (!alertNonNegativeNumber($('#Award_MoneyCost')[0], msgfix + '奖品所需金币数' + msgend)) {
                return false;
            }

            //------document.getElementById('Award_OnLineTime') = $('#Award_OnLineTime')[0]
            if (!alertNonNegativeNumber($('#Award_OnLineTime')[0], msgfix + '奖品所需游戏时长数' + msgend)) {
                return false;
            }

            if (!alertNonNegativeNumber($('#Award_Num')[0], msgfix + '奖品数量' + msgend)) {
                return false;
            }

            return true;
        }
         //-->
    </script>
    </form>
</body>
</html>
