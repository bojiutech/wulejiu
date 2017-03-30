<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="HN.Web.Manage.Pay.PCard.Default" %>

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
    </style>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu2" runat="server" />
        <div class="min_max_adap">
            <form id="Form2" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
            <div class="totalContent">
                <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                    overflow: hidden; height: 62px;">
                    <i class="ico_67 i1 newsNotice png"></i>
                    <div id='noticetime' class="time">
                        <span></span>
                    </div>
                    <div class="text" style="text-align: left;">
                        在线充值
                        <p>
                            点卡支付</p>
                    </div>
                </div>
                <div class="totalBd" style="background-color: #bedff6; padding-bottom: 20px;">
                    <asp:HiddenField ID="hidType" runat="server" Value="" />
                    <table border="0" cellpadding="0" cellspacing="0" class="tab02p">
                        <tr>
                            <td colspan="2">
                                &nbsp;
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                游戏帐号(用户名)：
                            </th>
                            <td align="left">
                                <asp:TextBox ID="txtUserName" runat="server" MaxLength="20" CssClass="input"></asp:TextBox>
                                *
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                确认帐号：
                            </th>
                            <td align="left">
                                <asp:TextBox ID="txtUserName2" runat="server" MaxLength="20" CssClass="input"></asp:TextBox>
                                *
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                金额：
                            </th>
                            <td align="left">
                                <asp:TextBox ID="PayMoney" runat="server" MaxLength="9" CssClass="input" onkeypress="return KeyPressNum(this,event);"
                                    onkeyup="CalculationMoney()"></asp:TextBox>
                                * 金额请输入大于零的整数
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                <span id="sp1">兑换成<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></span><span
                                    id="sp2" style="display: none;">兑换成积分</span>：
                            </th>
                            <td>
                                <input type="text" id="ExchangeMoney" readonly="readonly" value="0" class="input" />
                            </td>
                        </tr>
                        <tr>
                            <th>
                                点卡类型
                            </th>
                            <td style="text-align: left; padding: 5px 5px;">
                                <asp:RadioButtonList ID="rtype" runat="server">
                                    <asp:ListItem Text="QQ币卡" Value="qqb"></asp:ListItem>
                                    <asp:ListItem Text="盛大一卡通" Value="sdk"></asp:ListItem>
                                    <asp:ListItem Text="骏网一卡通" Value="jwk"></asp:ListItem>
                                    <asp:ListItem Text="完美一卡通" Value="wmk"></asp:ListItem>
                                    <asp:ListItem Text="搜狐一卡通" Value="shk"></asp:ListItem>
                                    <asp:ListItem Text="征途游戏卡" Value="ztk"></asp:ListItem>
                                    <asp:ListItem Text="久游一卡通" Value="jyk"></asp:ListItem>
                                    <asp:ListItem Text="网易一卡通" Value="wyk"></asp:ListItem>
                                    <asp:ListItem Text="电信充值卡" Value="dxk"></asp:ListItem>
                                    <asp:ListItem Text="神州行充值卡" Value="szx"></asp:ListItem>
                                    <asp:ListItem Text="联通充值卡" Value="ltk"></asp:ListItem>
                                    <asp:ListItem Text="光宇一卡通" Value="gyk"></asp:ListItem>
                                    <asp:ListItem Text="天下一卡通" Value="txk"></asp:ListItem>
                                    <asp:ListItem Text="天宏一卡通" Value="thk"></asp:ListItem>
                                    <asp:ListItem Text="纵游一卡通" Value="zyk"></asp:ListItem>
                                    <asp:ListItem Text="星启天卡" Value="zfk"></asp:ListItem>
                                </asp:RadioButtonList>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                点卡号：
                            </th>
                            <td align="left">
                                <asp:TextBox ID="txtcardNO" runat="server" MaxLength="16" CssClass="input"></asp:TextBox>
                                * 必填项
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                点卡密码：
                            </th>
                            <td align="left">
                                <asp:TextBox ID="txtcarPwd" TextMode="Password" runat="server" MaxLength="8" CssClass="input"></asp:TextBox>
                                * 必填项
                            </td>
                        </tr>
                        <input type="hidden" value="967" id="txt_payType" runat="server">
                        <input type="hidden" value="1" id="moneyRate" runat="server">
                        <tr>
                            <th height="65" scope="row" height="35">
                                &nbsp;
                            </th>
                            <td style="padding: 15px;">
                                <input type="submit" name="imageField2" id="imageField2" class="btnbg" value="提&nbsp;交"
                                    onserverclick="Button1_Click" runat="server" />&nbsp;&nbsp;
                                <input type="reset" name="imageField3" id="imageField3" class="btnbg" value="重&nbsp;填"
                                    onclick="ClearInfo()" />
                            </td>
                        </tr>
                    </table>
                </div>
            </div>
        </div>
        <div class="mask" style="display: none;" id="mask">
        </div>
        <div class="serviceIbox popup png" style="display: none;" id="servicePopup">
            <div class="service">
                <div class="iboxClose">
                    <a class="popupCloseTrigger png" href="javascript:;"></a>
                </div>
                <div class="serviceQQ">
                    &nbsp;
                </div>
            </div>
            <div class="serviceBottom">
            </div>
        </div>
        <div class="rechargeIbox popup png" style="display: none;" id="rechargePopup">
        </div>
        <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
        <script src="/js/scroll.js" type="text/javascript"></script>
        <!--[if IE 6]>
    <script src="/Content/js/DD_belatedPNG.js"></script>
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
        <script type="text/javascript">
            $().ready(function () {
                $(".payType").click(function () {
                    $(".payType").each(function () {
                        if ($(this).attr("checked") == "checked") {
                            $("#txt_payType").val($(this).val());
                        }
                    });

                });
            });
            var type = document.getElementById("hidType").value;

            if (type == "Bank") {
                $("#Bank").show();

            }
            if (type != "Bank" && type != "SZX-NET" && type != "UNICOM-NET") {
                $("#Card").show();

            }
            function CalculationMoney() {
                var moneyRate = $("#moneyRate").val();
                KeyPressNum(this, $("#PayMoney").val());
                if (isNaN($("#PayMoney").val())) {
                    $("#ExchangeMoney").val("0");
                    return false;

                } else {
                    //if ($("#rblPayType").find("input[@checked]").val() == "point") 


                    $("#ExchangeMoney").val($("#PayMoney").val() * moneyRate);


                }
            }
            function ClearInfo() {
                document.getElementById('txtUserName').value = '';
                document.getElementById('txtUserName2').value = '';
            }

            function onFormSubmit(f) {

                var txtUserName = document.getElementById('txtUserName');
                var txtUserName2 = document.getElementById('txtUserName2');
                if (!alertNull(txtUserName, '请输入游戏帐号！（用户名）')) {
                    return false;
                }

                var urlData = '/Public/XmlHttpUser.aspx?type=nameexist&username=' + escape(txtUserName.value.trim());
                //alert(urlData);
                var strReturn = AjaxCall(urlData);
                //alert(strReturn);
                if (strReturn == "0") {
                    alert('对不起，您输入的游戏帐号！（用户名）不存在。');
                    txtUserName.focus();
                    return false;
                }
                //strReturn=="1" 存在

                if (txtUserName.value.trim() != txtUserName2.value.trim()) {
                    alert('两次输入游戏帐号不一致！');
                    txtUserName2.focus();
                    return false;
                }

                var pmsg = '金额请输入大于零的整数！';
                var PayMoney = document.getElementById('PayMoney');
                if (!alertNonNegativeNumber(PayMoney, pmsg)) {
                    return false;
                } else if (parseInt(PayMoney.value.trim()) <= 0) {
                    alert(pmsg);
                    PayMoney.focus();
                    return false;
                }
                //////////////////
                if (!haveChecked()) {
                    alert("请选择点卡类型！");
                    return false;
                }

                var cardno = document.getElementById('txtcardNO');
                var pwd = document.getElementById('txtcarPwd');
                if (!alertNull(cardno, '请输入点卡号！')) {

                    return false;
                }
                if (!alertNull(pwd, '请输入点卡密码！')) {

                    return false;
                }

                return true;
            }
            function ChangeType() {
                CalculationMoney();
                //  if ($("#rblPayType").find("input[@checked]").val() == "point") {
                if ($("#rblPayType_0").attr("checked")) {

                    document.getElementById("sp1").style.display = "none";
                    document.getElementById("sp2").style.display = "";

                    document.getElementById("ddlGameList").disabled = false;
                }
                else {
                    document.getElementById("sp1").style.display = "";
                    document.getElementById("sp2").style.display = "none";
                    document.getElementById("ddlGameList").disabled = true;
                }
            }
            function haveChecked() {
                var rbl = document.getElementById('<%=rtype.ClientID %>');
                var rbls = rbl.getElementsByTagName('input');
                for (var i = 0; i < rbls.length; i++) {
                    if (rbls[i].type == 'radio')
                        if (rbls[i].checked) return true;
                }
                return false;
            }
        </script>
        </form>
    </div>
</body>
</html>
