<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetPassAnswer" %>

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
    <link href="../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script src="../../hn_css/js/jquery.js" type="text/javascript"></script>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/password_check.js"></script>
    <script type="text/javascript">
    <!--

        function onFormSubmit(f) {

            var txtUserName = document.getElementById('txtUserName');
            if (!alertNull(txtUserName, '请输入注册时填写的用户名')) {
                return false;
            }

            var txtValidCode = document.getElementById('txtValidCode');
            if (!alertNull(txtValidCode, '请输入验证码！')) {
                return false;
            }

            return true;
        }
     //-->
    </script>
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
        input
        {
            border: 1px solid #cfcece;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1
        newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text">
                        </div>
                    </div>
                    <div class="totalBd">
                        <div id="content01" style="width: 862px; margin: 0px auto;">
                            <div id="title01">
                                <h3 class="fl">
                                    密码找回</h3>
                                <p class="dqwz">
                                    当前位置：首页 > 找回密码
                                </p>
                            </div>
                            <div id="sub_nr">
                                <div class="cz">
                                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                                        <tr>
                                            <th colspan="2" style="height: 40px; font-size: 14px;">
                                                第二步：输入身份证号
                                            </th>
                                        </tr>
                                        <tr style="display: none;">
                                            <th width="40%" height="30" align="right" scope="row">
                                                证件类型：
                                            </th>
                                            <td width="60%" valign="middle">
                                                <asp:DropDownList ID="ddlCardType" runat="server" Enabled="False">
                                                </asp:DropDownList>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" height="30" scope="row" width="40%">
                                                身份证号：
                                            </th>
                                            <td valign="middle" width="60%">
                                                <asp:TextBox ID="txtCardNo" runat="server" CssClass="pro_input" MaxLength="18"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr style="display: none;">
                                            <th align="right" height="30" scope="row" width="40%">
                                                提示问题：
                                            </th>
                                            <td valign="middle" width="60%">
                                                <asp:DropDownList ID="ddlQuestion" runat="server" Enabled="False">
                                                </asp:DropDownList>
                                            </td>
                                        </tr>
                                        <tr style="display: none;">
                                            <th align="right" height="30" scope="row" width="40%">
                                                问题答案：
                                            </th>
                                            <td valign="middle" width="60%">
                                                <asp:TextBox ID="txtAnwer" runat="server" CssClass="pro_input"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr style="display: none;">
                                            <th align="right" height="30" scope="row" width="40%">
                                                银行密码：
                                            </th>
                                            <td valign="middle" width="60%">
                                                <asp:TextBox ID="txtTwoPass" runat="server" TextMode="Password" CssClass="pro_input"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td colspan="2" valign="middle" align="center">
                                                <br />
                                                <!--注意：输入以上三个问题，只要其中有二个问题回答正确即可找回密码！-->
                                                <br />
                                                <input class="but_011" type="submit" name="button5" id="button5" value="下一步" onserverclick="button5_ServerClick"
                                                    runat="server" />
                                                <input class="but_022" type="reset" name="reset" id="Submit1" value="重置" />
                                                <input class="but_011" type="button" name="button1" id="button1" value="上一步" onclick="history.go(-1)" />
                                            </td>
                                        </tr>
                                        <tr>
                                            <td colspan="2" align="center" valign="middle">
                                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                                            </td>
                                        </tr>
                                    </table>
                                    <script type="text/javascript"> <!--
                                        function onFormSubmit(f) {
                                            //证件号码-----------
                                            var ZJ_Number = document.getElementById('txtCardNo');
                                            if (!alertNull(ZJ_Number, '请输入身份证号！')) {
                                                return false;
                                            }
                                            //                                    //问题答案-----------
                                            //                                    var Answer = document.getElementById('txtAnwer');
                                            //                                    if (!alertNull(Answer, '请输入问题答案！'))
                                            //                                    { return false; }
                                            //                                    //银行密码-----------
                                            //                                    var pass = document.getElementById('txtTwoPass');
                                            //                                    if (!alertNull(pass, '请输入银行密码！')) {
                                            //                                        return false;
                                            //                                    } 
                                            return true;
                                        } //-->
                                    </script>
                                </div>
                                <div class="clear">
                                </div>
                            </div>
                            <p>
                                &nbsp;</p>
                            <!--right End-->
                        </div>
                        <!--right
        End-->
                    </div>
                </div>
            </div>
            <div class="mask" style="display: none;" id="mask">
            </div>
            <div class="serviceIbox
    popup png" style="display: none;" id="servicePopup">
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
            <!--[if IE 6]> <script
    src="/js/DD_belatedPNG.js"></script> <script> fixPng(); function fixPng()
    { DD_belatedPNG.fix('.png'); $(function(){ $('a.for56ie6 img,a.for68ie6 img,a.for32ie6
    img').each(function(){ var $i = $('<i>'); $(this).replaceWith($i); $i.attr('style',
    'cursor:pointer;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod="scale",src="'+
    $(this).attr('src') +'");background-image:none;'); }); }); } </script> <![endif]-->
            </form>
        </div>
    </div>
    <div class="wrap clear footer_info" style="margin: 0 auto; display: none;">
        <p class="fl">
            <a target="_blank" href="/index.aspx">
                <img alt="65游戏平台" src="../hnfooter/static/images/f_logo.jpg" class="fl"></a></p>
        <p class=" f_p">
            健康游戏忠告：抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当 适度游戏益脑 沉迷游戏伤身 合理安排 时间享受健康生活<br />
            <a rel="nofollow" href="../hnlogin/images/65wangwen.jpg" target="_blank">粤网文：[2013]0808-208号</a>
            <a rel="nofollow" href="http://www.miibeian.gov.cn/" target="_blank">粤ICP备16800008号</a>
            <a rel="nofollow" href="../hnlogin/images/65icp.jpg" target="_blank">增值电信业务经营许可证：粤B2-20130776</a><br />
            广东计算机系统股份有限公司 Copyright &copy; 2013-2015 版权所有 未经授权禁止转载、摘编、复制或建立镜像
        </p>
    </div>
    <script type="text/javascript" src="../../hn_css/js/www/www.jj.cn_pub_15.js"></script>
</body>
</html>
