<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJuZS" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>大恐龙网络游戏世界___最专业的棋牌游戏平台</title>
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
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="frmzs" action="" method="get" class="democss" onsubmit="return OnFormSubmit(this)">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text" style="text-align: left;">
                            <a href="/daoju.aspx" style="color: #000; font-size: 14px; font-weight: 500">道具商城</a>
                            &nbsp;|&nbsp; <a style="font-size: 14px;" href="/Manage/Finerylist.aspx">精品ID</a>
                        </div>
                    </div>
                    <div class="totalBd" style="background-color: #bedff6;">
                        <div class="cz" style="padding-top: 15px;">
                            <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                                <tr>
                                    <td width="42%" align="right" valign="middle">
                                        <img src="/Image/DaoJu/<%=PropID %>.gif" width="136" height="82" />
                                    </td>
                                    <td width="58%" class="prize_info">
                                        <strong>道具名称：<%=PropName %></strong><br />
                                        道具介绍：<span class="textgray"><%=PropDesc %></span>
                                    </td>
                                </tr>
                            </table>
                            <div class="cz" style="padding-top: 15px;">
                                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                    <tr>
                                        <th width="34%" height="30" align="right">
                                            赠送游戏账号：
                                        </th>
                                        <td width="66%">
                                            <input name="txtUserName" type="text" id="txtUserName" maxlength="20" class="fr_input" />
                                        </td>
                                    </tr>
                                    <tr>
                                        <th height="30" align="right">
                                            确认游戏账号：
                                        </th>
                                        <td>
                                            <input name="txtUserName2" type="text" id="txtUserName2" maxlength="20" class="fr_input" />
                                        </td>
                                    </tr>
                                    <tr>
                                        <th height="30" align="right">
                                            赠送数量：
                                        </th>
                                        <td>
                                            <input name="txtCount" type="text" id="txtCount" value="1" maxlength="3" size="5"
                                                class="fr_input" />
                                        </td>
                                    </tr>
                                    <tr>
                                        <td height="38" scope="row">
                                        </td>
                                        <td>
                                            <input type="submit" name="button5" id="button5" value="确认赠送" class="but_011" />
                                        </td>
                                    </tr>
                                </table>
                            </div>
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
            </form>
        </div>
    </div>
    <script type="text/javascript">
    <!--
        function OnFormSubmit(f) {
            var djid = '<%=PropID %>';
            var djname = '<%=PropName %>';
            var msgfix = '赠送道具：' + djname + "\n\n";
            //--------
            var username = document.getElementById('txtUserName');
            var username2 = document.getElementById('txtUserName2');
            if (!alertNull(username, msgfix + '请输入赠送用户名！')) {
                username.focus();
                return false;
            }
            //----------
            if (username.value.toLowerCase().trim() != username2.value.toLowerCase().trim()) {
                alert(msgfix + '两次输入的赠送用户名不一致！');
                username2.focus();
                return false;
            }

            //--------
            var txt = document.getElementById('txtCount');
            if (!alertNull(txt, msgfix + '赠送数量不能为空！')) {
                txt.focus();
                return false;
            }
            else if (!/^([0-9])[0-9]*(\.\w*)?$/.test(txt.value.trim())) {
                alert(msgfix + '赠送数量必须是数字，并且大于零！');
                txt.focus();
                return false;
            } else if (parseInt(txt.value.trim()) == 0) {
                alert(msgfix + '赠送数量必须是数字，并且大于零！');
                txt.focus();
                return false;
            }


            //1.判断用户是否登录了，否就提示登录  //2.判断输入的用户名是不是存在，是不是自己(不允许是自己)  //3.判断自己的道具库里是否有这个道具，数量是否足够  //4.确认赠送
            var urlData = '/Public/XmlHttpUser.aspx?type=islogin';
            //alert(urlData);
            var strReturn = AjaxCall(urlData);
            //alert(strReturn);
            if (strReturn == "0") {
                alert(msgfix + '对不起，请您登录后再赠送。');
                return false;
            }

            //--------
            if (!confirm(msgfix + '确认赠送该道具给[' + username.value + ']吗？')) {
                return false;
            }

            //2.根据数量乘于价格的结果，判断用户是否有足够的金币（银行或钱包）buydaoju
            urlData = '/Public/XmlHttpUser.aspx?type=zsdaoju&id=' + djid;
            urlData += '&targetname=' + escape(username.value.trim());
            urlData += '&count=' + txt.value.trim();
            //alert(urlData);
            strReturn = AjaxCall(urlData);
            //alert(strReturn);
            if (strReturn == "myself") {
                alert(msgfix + '抱歉，您不能把道具赠送给自己。');
            }
            else if (strReturn == "nouser") {
                alert(msgfix + '抱歉，被赠送用户不存在！');
            }
            else if (strReturn == "nodaoju") {
                alert(msgfix + '抱歉，您的道具库里没有这个道具或数量不够！');
            }
            else if (strReturn == "zsdjcg") {
                alert(msgfix + '道具赠送成功,您可以告诉您的好朋友[' + username.value + ']使用这个道具了！');
                username.value = '';
                username2.value = '';
                txt.value = 1;
            } else {
                alert(msgfix + '抱歉，道具赠送失败，可能是服务器繁忙，请稍候再试！');
            }

            return false;
        }
    //-->
    </script>
</body>
</html>
