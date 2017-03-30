<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="HN.Web.Manage.Login" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!doctype html>
<html>
<head>
    <meta name="keywords" content="斗地主,麻将,德州扑克,单机斗地主,欢乐斗地主,真人斗地主,斗地主手机版,麻将,网页,游戏,大厅,免费下载" />
    <meta name="description" content="斗地主，是全国最大的斗地主、麻将、德州扑克等棋牌类游戏在线竞技平台。以竞技为核心，通过组织比赛的形式，让您在紧张刺激中享受游戏的乐趣。" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Cache-Control" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    <title>登录中心</title>
    <link href="../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script src="../../hn_css/js/jquery.js" type="text/javascript"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript">
        function onFormSubmit(f) {
            if (!alertNull(f.txtAccount, '请输入用户名！')) {
                return false;
            }

            if (!alertNull(f.txtPwd, '请输入登录密码！')) {
                return false;
            }

            var txtValidCode = document.getElementById('txtValidCode');
            if (!alertNull(txtValidCode, '请输入验证码！')) {
                return false;
            }

            return true;
        }
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
        .tabTXT
        {
            height: 28px;
            border: 1px solid #cfcece;
            margin-bottom: 10px;
        }
        table th
        {
            height: 28px;
        }
        table label
        {
            font-size: 14px;
            font-weight: bold;
        }
        .btn_01
        {
            background-image: url(/Images/cont_btn12.jpg);
            width: 62px;
            height: 43px;
            border: 0px;
            cursor: pointer;
        }
    </style>
    <script type="text/javascript">
        if (window != top)
            top.location.href = location.href; 
    </script>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="form2" runat="server" onsubmit="return onFormSubmit(this);">
            <div>
                <div class="totalContent">
                    <div style="background-image: none; overflow: hidden; height: 62px;">
                        <div class="text">
                        </div>
                    </div>
                    <div class="totalBd" style="width: 860px; overflow: hidden; margin: 0 auto;">
                        <table cellpadding="0" cellspacing="0" class="login" style="width: 400px; margin: 0 auto;">
                            <tr>
                                <th>
                                    用户名：
                                </th>
                                <td>
                                    <asp:TextBox ID="txtAccount" runat="server" CssClass="tabTXT" MaxLength="15"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th>
                                    密码：
                                </th>
                                <td>
                                    <asp:TextBox ID="txtPwd" runat="server" TextMode="Password" CssClass="tabTXT" MaxLength="20"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th>
                                    验证码：
                                </th>
                                <td>
                                    <asp:TextBox ID="txtValidCode" runat="server" Width="60px" MaxLength="4" CssClass="tabTXT"></asp:TextBox>&nbsp;<img
                                        src="/Public/Getcode.aspx" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                        alt="点击换一张图片" style="cursor: pointer; width: 60px; height: 30px; margin-bottom: -10px;" />
                                </td>
                            </tr>
                            <tr>
                                <th>
                                    &nbsp;
                                </th>
                                <td>
                                    <asp:Button ID="imageField" runat="server" OnClick="btnSubmit_Click" Text=" " CssClass="btn_01" />
                                    &nbsp;&nbsp;<a href="/Register.aspx" style="color: #f26522; font-size: 14px; font-weight: bold;">注册</a>&nbsp;|&nbsp;
                                    <a style="color: red; font-size: 14px; font-weight: bold;" href="/Manage/GetPass.aspx">
                                        忘记密码?</a>
                                </td>
                            </tr>
                            <tr>
                                <th>
                                    &nbsp;
                                </th>
                                <td>
                                    <asp:Label ID="lbMsg" ForeColor="red" runat="server"></asp:Label>
                                </td>
                            </tr>
                        </table>
                    </div>
                </div>
            </div>
            <div class="mask" style="display: none;" id="Div2">
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
    <div style="position: absolute; bottom: 5%; text-align: center; width: 1024px; margin: 0 auto;
        left: 20%; display: none;">
        <p class="fl">
            <a target="_blank" href="/index.aspx">
                <img alt="65游戏平台" src="../hnfooter/static/images/f_logo.jpg" class="fl"></a></p>
        <p class=" fl">
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
