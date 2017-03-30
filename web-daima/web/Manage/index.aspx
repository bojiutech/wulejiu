<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="index.aspx.cs" Inherits="Bzw.Web.Manage.index" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!doctype html>
<html>
<head>
    <meta name="keywords" content="斗地主,麻将,德州扑克,单机斗地主,欢乐斗地主,真人斗地主,斗地主手机版,麻将,网页,游戏,大厅,免费下载" />
    <meta name="description" content="斗地主，是全国最大的斗地主、麻将、德州扑克等棋牌类游戏在线竞技平台。以竞技为核心，通过组织比赛的形式，让您在紧张刺激中享受游戏的乐趣。" />
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
        .php_ul2
        {
            background-color: #fff;
            height: 670px;
        }
        .php_ul2 li
        {
            margin-top: 0px;
            line-height: 30px;
            height: 40px;
            cursor: pointer;
            margin-bottom: 10px;
        }
        .php_ul2 li a
        {
            width: 200px;
            height: 40px;
            line-height: 39px;
            display: block;
            text-align: center;
            background: url('/Images/cont_bg03.jpg') no-repeat;
            font-size: 14px;
        }
        
        .php_ul2 li a:hover
        {
            background-color: #fff;
            font-weight: 500;
            background-color: #bedff6;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="form1" runat="server">
            <div class="wrap" style="margin-top: 20px;">
                <div class="totalContent">
                    <div class="totalBd">
                        <div style="height: 505px; margin-left: 10px; float: left;">
                            <ul class="php_ul2" style="border-top: 2px solid #fff;">
                                <li><a target="ifm" href="/Manage/default.aspx" class="link04 cheka">基本信息</a></li>
                                <li><a target="ifm" href="/Manage/EditBaseInfo.aspx" title="修改资料" class="link04">修改资料</a></li>
                                <li><a target="ifm" href="/Manage/TwoPass.aspx" title="银行密保" class="link04">银行密保</a></li>
                                <%--           <li><a target="ifm" href="/Manage/Album.aspx" class="link04">相册管理 </a></li>--%>
                                <li><a target="ifm" href="/Manage/BankAccess.aspx" title="银行取款" class="link04">银行取款</a></li>
                                <%-- <li><a target="ifm" href="/Manage/BankTrans.aspx" class="link04">用户转账</a></li>
                                <li><a target="ifm" href="/Manage/ApplyVipRoom.aspx" class="link04">租赁房间</a></li>
                                <li><a target="ifm" href="/Manage/MyRoom.aspx" class="link04">我的房间</a></li>
                                <li><a target="ifm" href="/Manage/FasciExchange.aspx" class="link04">魅力值兑换</a></li>
                        <li><a target="ifm" href="/Manage/PropClearFasci.aspx" class="link04">购买魅力值清零道具</a></li>--%>
                                <li><a target="ifm" href="/Manage/Pay/PointCardLog.aspx" title="交易记录" class="link04">
                                    交易记录 </a></li>
                                <li><a target="ifm" href="/Manage/AwardLog.aspx" title="兑奖记录" class="link04">兑奖记录</a></li>
                                <%-- <li><a target="ifm" href="/Manage/MyLoterryJP.aspx" class="link04">抽奖奖品记录 </a></li>--%>
                                <li><a target="ifm" href="/Manage/VipApply.aspx" title="VIP申请" class="link04">VIP申请</a></li>
                                <li><a target="ifm" href="/Manage/Promotion2.aspx" title="游戏推广员" class="link04">游戏推广员</a></li>
                                <li><a target="ifm" href="/Manage/FineryIDManage.aspx" title="靓号管理" class="link04">靓号管理</a></li>
                                <li><a target="ifm" href="/Manage/FeedBacks.aspx" title="查看留言" class="link04">查看留言 </a>
                                </li>
                                <li><a target="_blank" href="/Service.aspx" title="在线留言" class="link04">在线留言 </a>
                                </li>
                                <li><a target="_blank" href="/daoju.aspx" title="道具商城" class="link04">道具商城</a></li>
                                <li><a href="/Public/Logout.aspx" class="link04">退出</a></li>
                            </ul>
                        </div>
                        <%--页面内容--%>
                        <div id="content01" style="margin: 0px 0px 0px 0px; padding: 0px; padding-top: 2px; float: left;
                            width: 710px; height: 670px; background-color: #fff; overflow: hidden;">
                            <script language="javascript" type="text/javascript">
                                function dyniframesize(down) {
                                    var pTar = null;
                                    if (document.getElementById) {
                                        pTar = document.getElementById(down);
                                    }
                                    else {
                                        eval('pTar = ' + down + ';');
                                    }
                                    if (pTar && !window.opera) {
                                        //begin resizing iframe 
                                        pTar.style.display = "block"
                                        if (pTar.contentDocument && pTar.contentDocument.body.offsetHeight) {
                                            //ns6 syntax 
                                            pTar.height = pTar.contentDocument.body.offsetHeight + 20;
                                            pTar.width = pTar.contentDocument.body.scrollWidth + 20;
                                        }
                                        else if (pTar.Document && pTar.Document.body.scrollHeight) {
                                            //ie5+ syntax 
                                            pTar.height = pTar.Document.body.scrollHeight;
                                            pTar.width = pTar.Document.body.scrollWidth;
                                        }
                                    }
                                } 
                            </script>
                            <iframe src="/manage/default.aspx" frameborder="0" marginheight="0" marginwidth="0"
                                frameborder="0" scrolling="no" id="ifm" name="ifm" onload="javascript:dyniframesize('ifm');"
                                width="100%" height="670px"></iframe>
                        </div>
                        <%--页面内容end--%>
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
    <div style="margin: 0 auto; display: none;">
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
