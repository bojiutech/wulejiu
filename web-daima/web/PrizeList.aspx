<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PrizeList.aspx.cs" Inherits="HN.Web.PrizeList" %>
<%@ Register Src="/Public/NewFooter.ascx" TagName="NewFooter" TagPrefix="uc1" %>
<!doctype html>
<html>
<head>
    <meta name="keywords" content="斗地主,麻将,德州扑克,单机斗地主,欢乐斗地主,真人斗地主,斗地主手机版,麻将,网页,游戏,大厅,免费下载" />
    <meta name="description" content="斗地主，是全国最大的斗地主、麻将、德州扑克等棋牌类游戏在线竞技平台。以竞技为核心，通过组织比赛的形式，让您在紧张刺激中享受游戏的乐趣。" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Cache-Control" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    <title>奖品中心</title>
    <link href="../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script src="../../hn_css/js/jquery.js" type="text/javascript"></script>
    <style type="text/css">
        
    </style>
</head>
<body>
    <div id="min_max_width">
        <div class="jj_nav_hot jj_nav_hot_inner" id="jj_nav_hot">
            <div class="jj_nav_info">
                <div class="min_max_adap" id="min_max_adap">
                    <div class="usr" style="display: none;">
                        <span id="usr_loding"></span><span class='down' onmouseover="javascript:this.className='down down_hov';"
                            onmouseout="javascript:this.className='down';"><span class='jt'>快速通道</span>
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
            <div class="inner_top_nav">
                <a href="/index.aspx">首页</a> <span class="s">></span> <a href="/PrizeList.aspx">
                    奖品中心</a> <span class="s">></span> <span id="P_ClassName" >奖品分类</span>
            </div>
            <div class="inner_hot_img">
                <ul id="inner_hot_img">
                    <asp:Repeater ID="rptHotImg" runat="server">
                        <ItemTemplate>
                            <li class="jp_li inner_li1"
                            ><a target="_blank"
                                href="/PrizeDetail.aspx?id=<%#Eval("Award_ID") %>">
                                <img class="hd_new_hot" src="../../hn_img/www/prize/1.gif"><span class="im"><img
                                    title="<%#Eval("Award_Name")%>" src="<%#Eval("Award_Pic")%>"></span><span class="ma"
                                        title="<%#Eval("Award_Name")%>"><%#Eval("Award_Name")%></span><span class="qc">所需
                                            <%=UiCommon.StringConfig.GoldName %>：<%#Eval("Award_MoneyCost")%></span></a></li>
                        </ItemTemplate>
                    </asp:Repeater>
                </ul>
            </div>
        </div>
        <div class="h_30px">
        </div>
        <div class="min_max_adap" id="min_max_adap_right_nav">
            <div class="inner_tow_left" id="inner_tow_left">
                <div class="inner_tow_left_top">
                </div>
                <ul class="innert_prize_list" id="innert_prize_list">
                    <asp:Repeater ID="rptList" runat="server">
                        <ItemTemplate>
                            <li class="jp_li"><a target="_blank" href="/PrizeDetail.aspx?id=<%#Eval("Award_ID") %>">
                               <%#CssHandler(Eval("AwardProP").ToString())%><span class="im">
                                    <img title="<%#Eval("Award_Name")%>" src="<%#Eval("Award_Pic")%>"></span><span class="ma"
                                        title="<%#Eval("Award_Name")%>"><%#Eval("Award_Name")%></span><span class="qc">所需<%=UiCommon.StringConfig.GoldName %>：<%#Eval("Award_MoneyCost")%></span></a></li>
                        </ItemTemplate>
                    </asp:Repeater>
                </ul>
            </div>
            <div class="inner_tow_right" id="inner_tow_right">
                <ul class="inner_tow_right_nav">
                    <asp:Repeater ID="rptClass" runat="server">
                        <ItemTemplate>
                            <li id="<%#Eval("ID","cs{0}") %>"><a href="/PrizeList.aspx?classid=<%#Eval("ID") %>"><span class="co" <%#Eval("ClassBgimg","style=background:url({0})")%>></span>
                                <%#Eval("ClassName")%></a></li>
                        </ItemTemplate>
                    </asp:Repeater>
                </ul>
            </div>
            <div class="h_1px">
            </div>
        </div>
        <div class="min_max_adap">
            <div class="inner_tow_left">
                <div class="inner_Load_more">
                    <span>加载中...</span>
                </div>
            </div>
            <div class="h_1px">
            </div>
        </div>
    </div>
<uc1:NewFooter runat="server" id="new1" />
    <script type="text/javascript" src="../../hn_css/js/www/www.jj.cn_pub_15.js"></script>
    <script type="text/javascript" src="../../hn_css/js/www/jj.cn_prize.js" charset="gb2312"></script>
    <script type="text/javascript">
        String.prototype.trim = function () {
            return this.replace(/^\s\s*/, '').replace(/\s\s*$/, '');
        }
        function getQueryString(name) {
            var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)", "i");
            var r = window.location.search.substr(1).match(reg);
            if (r != null) return unescape(r[2]); return null;
        }
        $(document).ready()
        {
            var classid = getQueryString("classid");
            if (classid != null && classid.length > 0) {
                $("#cs" + classid).addClass("hov");
                $("#P_ClassName").html($("#cs" + classid).find("a").eq(0).text().trim());
            }
         }
    </script>
</body>
</html>
