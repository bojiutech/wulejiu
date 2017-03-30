<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Manage_Pay_PointCard" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>
        <%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台
    </title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        html
        {
            overflow-x: hidden;
            overflow-y: auto;
        }
        .plus
        {
            margin-left: 220px;
            margin-top: -140px;
            width: 415px;
            _margin-left: 110px;
            _margin-top: -215px;
        }
        .plus a
        {
            display: inline-block;
            text-align: center;
            width: 95px;
            color: #0073cc;
            font-size: 11px;
            -webkit-text-size-adjust: none;
        }
        .plus a:hover
        {
            color: #000000;
        }
        .tabcz tr
        {
            height: 50px;
        }
    </style>
    <script type="text/javascript">
<!--

        function ClearInfo() {
            document.getElementById('txtUserName').value = '';
            document.getElementById('txtUserName2').value = '';
            document.getElementById('txtCardNo').value = '';
            document.getElementById('txtCardPwd').value = '';
            document.getElementById('txtValidCode').value = '';
        }

        function onFormSubmit(f) {

            var txtUserName = document.getElementById('txtUserName');
            var txtUserName2 = document.getElementById('txtUserName2');
            if (!alertNull(txtUserName, '请输入游戏帐号！（用户名）')) {
                return false;
            }

            if (txtUserName.value.trim() != txtUserName2.value.trim()) {
                alert('两次输入游戏帐号不一致！');
                txtUserName2.focus();
                return false;
            }

            var txtCardNo = document.getElementById('txtCardNo');
            if (!alertNull(txtCardNo, '请输入充值卡卡号！')) {
                return false;
            }

            var txtCardPwd = document.getElementById('txtCardPwd');
            if (!alertNull(txtCardPwd, '请输入充值卡密码！')) {
                return false;
            }

            var txtValidCode = document.getElementById('txtValidCode');
            if (!alertNull(txtValidCode, '请输入验证码！')) {
                return false;
            }

            return true;
        }
        function ChangeType() {

            if ($("#rblPayType").find("input[@checked]").val() == "point") {

                document.getElementById("ddlGameList").disabled = false;
            }
            else {

                document.getElementById("ddlGameList").disabled = true;
            }
        }
 //-->
    </script>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="Form1" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text" style="text-align: center;">
                            点卡充值
                        </div>
                    </div>
                    <div class="totalBd">
                        <div class="cz" style="width: 98%;">
                            <p>
                            <table summary="" border="0" class="tabcz" style="width: 300px; margin: 0px auto;">
                                <tbody>
                                    <tr>
                                        <th>
                                            &nbsp;
                                        </th>
                                        <td valign="middle" align="center">
                                            <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red" Font-Size="15"></asp:Label>&nbsp;
                                        </td>
                                    </tr>
                                    <tr>
                                        <th>
                                            游戏帐号
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtUserName" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id02">
                                                确认帐号</label>
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtUserName2" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <%if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1")
                                      { %>
                                    <tr style="display: none">
                                        <th height="30" align="right" scope="row">
                                            充值类型：
                                        </th>
                                        <td valign="middle">
                                            <asp:RadioButtonList ID="rblPayType" runat="server" RepeatDirection="Horizontal"
                                                onclick="ChangeType()">
                                                <asp:ListItem Text="龙币" Value="money" Selected="True"></asp:ListItem>
                                                <asp:ListItem Text="积分" Value="point"></asp:ListItem>
                                            </asp:RadioButtonList>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th height="30" align="right" scope="row">
                                            请选择游戏：
                                        </th>
                                        <td valign="middle">
                                            <asp:DropDownList ID="ddlGameList" runat="server" Enabled="false">
                                            </asp:DropDownList>
                                            &nbsp;充值<%=UiCommon.StringConfig.MoneyName %>不用选择游戏
                                        </td>
                                    </tr>
                                    <%} %>
                                    <tr>
                                        <th scope="row" class="style1">
                                            <label for="id03">
                                                充值卡卡号</label>
                                        </th>
                                        <td class="style1">
                                            <asp:TextBox ID="txtCardNo" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id04">
                                                充值卡密码</label>
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtCardPwd" runat="server" CssClass="in" TextMode="password" MaxLength="20"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id05">
                                                验证码</label>
                                        </th>
                                        <td>
                                            <p class="yzm01">
                                                <asp:TextBox ID="txtValidCode" runat="server" MaxLength="4" Width="54px"></asp:TextBox><span
                                                    class="red">*</span>
                                                <img src="/Public/Getcode.aspx" onclick="this.src='/Public/Getcode.aspx?token='+Math.random();"
                                                    alt="点击换一张图片" style="cursor: pointer; width: 50px; height: 17px; line-height: 17px;" />
                                        </td>
                                    </tr>
                                </tbody>
                            </table>
                            <p class="text06" style="text-align: center; padding: 5px; color: red;">
                                * 请正确的填写充值的游戏帐号（用户名），如填错，本棋牌游戏中心不负任何责任。</p>
                            <p class="cz_btn" style="text-align: center;">
                                <input type="submit" name="imageField2" id="imageField2" value="提&nbsp;交" class="btnbg"
                                    onserverclick="button5_ServerClick" runat="server" />&nbsp;&nbsp;&nbsp;&nbsp;
                                <input type="button" class="btnbg" onclick="ClearInfo()" value="重&nbsp;填" />
                                <br />
                                <img src="/Images/cont_tbl_img22.jpg" style="height: 220px; margin-top: 20px; display: none"
                                    alt="" />
                            </p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="mask" style="display: none;" id="mask">
            </div>
            <div class="serviceIbox popup png" style="display: none;" id="servicePopup">
                &nbsp;
            </div>
            <div class="rechargeIbox popup png" style="display: none;" id="rechargePopup">
            </div>
            <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
            <script src="/js/scroll.js" type="text/javascript"></script>
            <!--[if IE 6]>
    <script src="/js/DD_belatedPNG.js"></script>
    <script>
        fixPng();
        function fixPng()
        {
            DD_belatedPNG.fix('.png');
	        $(function(){
		        $('a.for56ie6 img,a.for68ie6 img,a.for32ie6 img').each(function(){
			        var $i = $('<i>');
			        $(this).replaceWith($i);
			        $i.attr('style', 'cursor:pointer;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod="scale",src="'+ $(this).attr('src') +'");background-image:none;');
		        });
	        });
        }
    </script>
    <![endif]-->
            </form>
        </div>
    </div>
</body>
</html>
