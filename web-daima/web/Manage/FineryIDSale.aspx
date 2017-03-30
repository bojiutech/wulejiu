<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.FineryIDSale" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta name="Description" content="大恐龙游戏平台是中国最专业的网络棋牌游戏中心之一，是大恐龙网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,大恐龙游戏,大恐龙,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <link href="../../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet"
        type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/DaoJu.js"></script>
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
        
        /*------------#prize And #props-----------------*/#prize, #props
        {
            padding: 15px 15px 0;
            float: left;
        }
        #prize dl, #props dl
        {
            width: 110px;
            height: 280px;
            float: left;
            overflow: hidden;
            text-align: center;
            border-bottom: 1px solid #cbecfb;
            margin-bottom: 20px;
        }
        #props dl
        {
            height: 150px;
        }
        #prize dt, #props dt
        {
            height: 12px;
            padding-top: 2px;
        }
        #props dd
        {
            margin-bottom: 10px;
        }
        #prize strong, #props strong
        {
            display: block;
            padding-top: 5px;
        }
        #prize dd img, #props img
        {
            width: 100px;
            height: 100px;
            overflow: hidden border: 1px solid #b6d6ec;
        }
        .btn
        {
            display: block;
            width: 106px;
            height: 34px;
            line-height: 34px;
            color: White;
            margin: 0 auto;
            background: url(/images/sub_btn01.jpg) no-repeat left top;
        }
        .red
        {
            color: Red;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu2" runat="server" />
        <div class="min_max_adap">
            <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text" style="text-align: left;">
                            靓号购买
                        </div>
                    </div>
                    <div class="totalBd" style="background-color: #bedff6;">
                        <div id="content01" style="width: 803px; margin: 0px; padding: 0px; clear: both;
                            overflow: hidden; text-align: left; float: left;">
                            <div id="sub_nr" style="margin-top: 10px;">
                                <div class="cz">
                                    <table width="100%" border="0">
                                        <tr>
                                            <th colspan="2" scope="row">
                                                &nbsp;
                                            </th>
                                        </tr>
                                        <tr>
                                            <th width="24%" height="35" align="right" scope="row">
                                                靓&nbsp;号&nbsp;ID：
                                            </th>
                                            <td width="76%">
                                                <asp:Label ID="fineryLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th height="35" align="right" scope="row">
                                                靓号价格：
                                            </th>
                                            <td>
                                                <asp:Label ID="priceLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>&nbsp;&nbsp;<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th height="35" align="right" scope="row">
                                                靓号描述：
                                            </th>
                                            <td>
                                                <asp:Label ID="explainLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" valign="middle">
                                                <strong>靓号密码：</strong>
                                            </th>
                                            <td align="left" valign="middle">
                                                <input name="pwd" type="password" id="pwd" maxlength="20" onblur="chkPwd()" style="width: 149px;" />
                                                <span class="red">*设定您的靓号密码，并请您牢记</span><br />
                                                <span class="note" id="pwdspan">密码由6-20个英文字母或数字组成，请牢记您的靓号密码</span>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" valign="middle">
                                                <strong>密码确认：</strong>
                                            </th>
                                            <td align="left" valign="middle">
                                                <input name="pwd2" type="password" id="pwd2" maxlength="20" onblur="chkPwd2()" style="width: 149px;" />
                                                <span class="red">*</span>
                                                <br />
                                                <span class="note" id="pwd2span">请再次输入您的密码，保证无误。 </span>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th colspan="2" align="center">
                                                <asp:Panel ID="Panel1" runat="server" Visible="false">
                                                    <a href="/Manage/BankAccess.aspx">去存款 >></a>&nbsp;&nbsp;&nbsp;&nbsp;<a href="/Manage/Pay/Default.aspx">去充值
                                                        >></a>
                                                </asp:Panel>
                                            </th>
                                        </tr>
                                        <tr>
                                            <td colspan="2" align="center">
                                                <input id="Submit1" type="submit" name="submit" value="购买 " runat="server" onserverclick="Button1_Click"
                                                    class="but_011" onclick="javascript:if(!confirm('您确定购买吗')){return false};" />
                                            </td>
                                        </tr>
                                    </table>
                                </div>
                                <div class="clear">
                                </div>
                            </div>
                            <p>
                                &nbsp;</p>
                        </div>
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
                /*===Check Pwd========================*/
                function chkPwd() {
                    var txt = document.getElementById('pwd');
                    var tip = document.getElementById("pwdspan");

                    //valid is null--------------
                    if (txt.value.trim().length == 0) {
                        tip.className = "note_no";
                        return false;
                    }
                    //valid regx-----------------
                    if (!/^[0-9a-zA-Z]{6,20}$/.test(txt.value)) {
                        tip.className = "note_no";
                        return false;
                    }

                    tip.className = "note_yes";
                    tip.innerHTML = "恭喜您！密码通过验证，请牢记您的靓号密码";
                    return true;
                }

                /*===Check Pwd2========================*/
                function chkPwd2() {
                    var txt = document.getElementById('pwd');
                    var txt2 = document.getElementById('pwd2');
                    var tip = document.getElementById("pwd2span");

                    if (txt.value.trim().length < 6 || txt.value.trim().length > 20) {
                        txt.focus();
                        return false;
                    }

                    if (txt.value.trim() != txt2.value.trim()) {
                        tip.className = "note_no";
                        tip.innerText = '两次输入密码不一致，请重新输入。';
                        return false;
                    }

                    tip.className = "note_yes";
                    tip.innerText = '恭喜您，密码检测通过。';
                    return true;
                }
                function onFormSubmit(f) {
                    if (!chkPwd()) {
                        document.getElementById('pwd').focus();
                        return false;
                    }

                    if (!chkPwd2()) {
                        document.getElementById('pwd2').focus();
                        return false;
                    }
                    return true;
                }
            </script>
            </form>
        </div>
    </div>
</body>
</html>
