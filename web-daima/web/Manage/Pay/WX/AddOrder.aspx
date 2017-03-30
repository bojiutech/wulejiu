<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AddOrder.aspx.cs" Inherits="HN.Web.Manage.Pay.WX.AddOrder" %>

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
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
            <form id="Form1" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
            <!--头部开始-->
            <div class="totalContent">
                <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                    overflow: hidden; height: 62px;">
                    <i class="ico_67 i1 newsNotice png"></i>
                    <div id='noticetime' class="time">
                        <span></span>
                    </div>
                    <div class="text">
                        在线充值
                        <p>
                            微信充值</p>
                    </div>
                </div>
                <div class="totalBd">
                    <table border="0" cellpadding="0" cellspacing="0" class="tabcz">
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
                                <asp:TextBox ID="PayMoney" runat="server" MaxLength="9" CssClass="input" onkeyup="CalculationMoney()"></asp:TextBox>
                                * 金额请输入大于零的整数
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="35">
                                <span id="sp1">兑换成<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></span><span
                                    id="sp2" style="display: none;">兑换成积分</span>：
                            </th>
                            <td align="left">
                                <input type="text" id="ExchangeMoney" readonly="readonly" value="0" class="input" />
                            </td>
                        </tr>
                        <input type="hidden" value="1" id="moneyRate" runat="server">
                    </table>
                    <p class="cz_btn" style="text-align: center;">
                        <input type="submit" name="imageField2" id="imageField2" class="btnbg" value="提&nbsp;交"
                            onserverclick="Button1_Click" runat="server" />&nbsp;&nbsp;&nbsp;&nbsp;
                        <input type="reset" name="imageField3" id="imageField3" class="btnbg" value="重&nbsp;填"
                            onclick="ClearInfo()" />
                    </p>
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
            <script type="text/javascript">


                function CalculationMoney() {
                    var moneyRate = $("#moneyRate").val();
                    //KeyPressNum(this, $("#PayMoney").val());
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
            </script>
        </div>
        <!--页面主体结束-->
        <!--底部开始-->
        <!--底部结束-->
        </form>
    </div>
</body>
</html>
