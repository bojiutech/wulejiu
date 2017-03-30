<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Service" %>

<!doctype html>
<html>
<head>
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="keywords" content="斗地主,麻将,德州扑克,单机斗地主,欢乐斗地主,真人斗地主,斗地主手机版,四川麻将,dota,电子竞技,网页,游戏,大厅,免费下载,斗地主赢话费" />
    <meta name="description" content="斗地主，是全国最大的斗地主、麻将、德州扑克等棋牌类游戏在线竞技平台。以竞技为核心，通过组织比赛的形式，让您在紧张刺激中享受游戏的乐趣。除棋牌游戏之外，还涵盖了5599网页游戏平台、JJ-Dota对战平台、3399小游戏平台、无线应用等互联网业务" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Cache-Control" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    <title>用户中心</title>
    <link href="../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script src="../../hn_css/js/jquery.js" type="text/javascript"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
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
        .tabTXT
        {
            height: 28px;
            border: 1px solid #cfcece;
        }
        table th
        {
            line-height: 28px;
        }
        table tr
        {
            margin-bottom: 20px;
        }
        table label
        {
            font-size: 12px;
            font-weight: bold;
        }
        .btn_01
        {
            background-image: url(/images/btn_bg01.jpg);
            width: 62px;
            height: 43px;
            border: 0px;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <div class="jj_nav_hot jj_nav_hot_inner" id="jj_nav_hot">
            <div class="jj_nav_info">
                <div class="min_max_adap" id="min_max_adap">
                    <div class="usr" style="display: none;">
                        <span id="usr_loding"></span><span class='down' onmouseover="" onmouseout=""><span
                            class='jt'>快速通道</span>
                            <div class='li'>
                                <dl>
                                    <dt class="d1"><a href='http://pay.jj.cn/' target='_blank'>充值中心</a></dt>
                                    <dt class="d1"><a href='http://my.jj.cn/account/account.php' target='_blank'>我的账号</a></dt>
                                    <dt class="d2"><a href='http://club.jj.cn/interface.php' target='_blank'>我的公社</a></dt>
                                    <dt class="d3"><a href='http://my.jj.cn/account/honour.php' target='_blank'>我的荣誉室</a></dt>
                                    <dt class="d3"><a href='http://shop.jj.cn/' target='_blank'>商 城</a></dt>
                                    <dt><a href='http://bbs.jj.cn/' target='_blank'>论 坛</a></dt>
                                </dl>
                            </div>
                        </span>
                    </div>
                    <script type="text/javascript" src="../../hn_css/js/www/uer_loding_15.js"></script>
                    <div class="logo">
                        <a href="/index.aspx">
                            <img src="../../hn_img/www/hn/hn_logo.png" /></a></div>
                    <ul class="nav">
                        <li><a href="/index.aspx"><span class="s1"></span>首 页</a></li>
                        <li><a href="/Down.aspx" title="下载中心"><span class="s2"></span>下载中心</a></li>
                        <li><a href="/Manage/Pay/Yeepay2/default.aspx" title="游戏充值"><span class="s3"></span>
                            游戏充值</a></li>
                        <li><a href="/PrizeList.aspx"><span class="s4"></span>积分商城</a></li>
                    </ul>
                </div>
            </div>
        </div>
        <div class="prize_inner_bg">
        </div>
        <div class="min_max_adap">
            <form id="Form1" runat="server" onsubmit="return onFormSubmit(this);">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalBd">
                        <div id="sub_nr">
                            <div class="cz" style="text-align: center; margin: 0 auto;">
                                <div style="width: 100%; border: 0px; height: 229px; background-image: url(/Images/servicesqq.jpg);
                                    background-repeat: no-repeat; background-position: center; overflow: hidden;">
                                    <div style="position: absolute; left: 370px; top: 60px; font-size: 20px; font-weight: 700;
                                        color: #000">
                                        <%= SiteConfig.GetParaValue("客服电话")%>
                                    </div>
                                    <div style="position: absolute; left: 720px; top: 60px; font-size: 20px; font-weight: 700;
                                        color: #000">
                                        <a style="color: #000;" href="http://wpa.qq.com/msgrd?v=3&amp;uin=<%= SiteConfig.GetParaValue("CustomServiceqq1")%>&amp;site=qq&amp;menu=yes"
                                            target="_blank" title="点击在线咨询">
                                            <%= SiteConfig.GetParaValue("CustomServiceqq1")%></a>
                                    </div>
                                </div>
                                <p style="color: #000; margin: 5px;">
                                    严禁制用、转载、链接色情的，危害国家安全与社会安定的、危害民族或宗教团结等违法内容；一经发现将立即关闭；情节严<br />
                                    重者直接移交相关部门处理。</p>
                                <table cellpadding="0" cellspacing="0" class="tabcz" style="margin: 0 auto;">
                                    <tr>
                                        <th scope="row">
                                            <label for="id01">
                                                * 您的名字</label>
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtName" runat="server" MaxLength="15" CssClass="tabTXT"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id02">
                                                * 电子邮箱</label>
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtEmail" runat="server" MaxLength="25" CssClass="tabTXT"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id03">
                                                * 留言标题</label>
                                        </th>
                                        <td>
                                            <asp:TextBox ID="txtTitle" runat="server" MaxLength="25" CssClass="tabTXT"></asp:TextBox>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th scope="row">
                                            <label for="id04">
                                                * 留言内容</label>
                                        </th>
                                        <td style="padding: 7px 0 7px 10px;">
                                            <asp:TextBox ID="txtContent" runat="server" CssClass="tabTXT" Height="94px" TextMode="MultiLine"
                                                Width="336px" /><br />
                                            <span class="text06">*（留言内容不能超过200位，一个汉字为2位。）</span>
                                        </td>
                                    </tr>
                                    <tr>
                                        <th height="30" align="right" scope="row">
                                            * 验证码：
                                        </th>
                                        <td>
                                            <asp:TextBox ID="VerifyCode" runat="server" MaxLength="4" CssClass="tabTXT" Width="50"></asp:TextBox>
                                            <img id="imgValidCode" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                                alt="点击换一张图片" src="/Public/Getcode.aspx" style="vertical-align: top; cursor: pointer;
                                                width: 60px; height: 30px" />
                                            <span class="red">*</span>
                                        </td>
                                    </tr>
                                </table>
                                <p class="cz_btn" style="text-align: center; margin: 10px 0px 20px 0px;">
                                    <input type="submit" name="imageField2" class="btn_01" value="提&nbsp;交" onserverclick="button5_ServerClick"
                                        runat="server" id="imageField2" />&nbsp;&nbsp;&nbsp;&nbsp;
                                    <input type="button" name="imageField3" class="btn_01" value="重&nbsp;填" onclick="ClearInfo()"
                                        id="imageField3" />
                                </p>
                                <p>
                                    <span id="spanMsg"></span>
                                </p>
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
            <script type="text/javascript">
<!--
                function ClearInfo() {
                    document.getElementById('txtName').value = '';
                    document.getElementById('txtEmail').value = '';
                    document.getElementById('txtTitle').value = '';
                    document.getElementById('txtContent').value = '';
                }

                function onFormSubmit(f) {
                    var txtName = document.getElementById('txtName');
                    if (!alertNull(txtName, '请输入您的名字！')) {
                        return false;
                    }

                    var txtEmail = document.getElementById('txtEmail');
                    if (!alertNull(txtEmail, '请输入您的电子邮箱！')) {
                        return false;
                    } else if (!isEmail(txtEmail.value)) { //if(!/^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/.test(txt.value)){
                        alert('请输入正确格式的电子邮箱!');
                        txtEmail.focus();
                        return false;
                    }

                    var txtTitle = document.getElementById('txtTitle');
                    if (!alertNull(txtTitle, '请输入留言的标题！')) {
                        return false;
                    }

                    var txtContent = document.getElementById('txtContent');
                    if (!alertNull(txtContent, '请输入留言的内容！')) {
                        return false;
                    }
                    else {
                        var strLen = 0;
                        for (i = 0; i < txtContent.value.length; i++) {
                            if (txtContent.value.charCodeAt(i) > 255) {
                                strLen += 2; //是汉字则加2
                            }
                            else {
                                strLen++; //非汉字则加1
                            }
                        }

                        if (strLen > 200) {
                            alert('留言内容不能超过200位,您输入了' + strLen + '位！(一个汉字为2位)');
                            txtContent.focus();
                            return false;
                        }
                    }
                    var verify = document.getElementById('VerifyCode');
                    if (verify.value.length != 4) {
                        alert('请输入四位验证码！');
                        verify.focus();
                        return false;
                    }

                    return true;
                }
//-->
            </script>
            <script>
                var x = location.search;
                if (x != "") {
                    if (x.replace("?", "").toLowerCase() == "success")
                        document.getElementById("spanMsg").innerHTML = '<strong style="color:red;">提交成功！</strong>';
                    else
                        document.getElementById("spanMsg").innerHTML = '<strong style="color:red;">提交失败！</strong>';
                }
            </script>
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
</body>
</html>
