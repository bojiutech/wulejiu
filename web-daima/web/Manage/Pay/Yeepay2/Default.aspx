<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Yeepay2.Manage_Pay_Yeepay2_Default" %>

<%@ Register Src="/Public/NewFooter.ascx" TagName="NewFooter" TagPrefix="uc1" %>
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
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="/hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="/hnlogin/www/css/style.css" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
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
        /*footer*/
        .footcopy
        {
            background: #F3F3F3 none repeat scroll 0% 0%;
            border-top: 1px solid #E8E8E8;
            min-width: 1190px;
            overflow: hidden;
            padding-bottom: 10px;
        }
        .footcooper
        {
            width: 1190px;
        }
        .footcooper a
        {
            height: 50px;
            line-height: 50px;
            font-size: 14px;
            margin: 0px 0px 0px 22px;
            text-align: left;
            overflow: hidden;
        }
        .link
        {
            background: #edeeee;
            border-radius: 5px;
            padding: 20px 0px 30px 0px !important;
            width: 1190px;
            text-align: center;
        }
        .link_l
        {
            width: 72px;
            padding-left: 10px;
        }
        .link_r
        {
            width: 1100px;
        }
        .link_r a
        {
            color: #525252;
            display: block;
            float: left; /*margin: 0 10px 10px 10px;*/
            white-space: nowrap;
        }
        .footer_info .f_p
        {
            margin-left: 20px;
            line-height: 23px;
        }
        .footer_info
        {
            padding: 20px 0px;
            width: 1190px;
        }
        .menulist a
        {
            font-size: 18px !important;
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <form id="form1" runat="server">
            <div class="wrap">
                <div class="totalContent">
                    <div class="totalHd png" style="background-image: none; background-color: #9bceed;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text" style="text-align: left; display: none;">
                            在线充值
                        </div>
                    </div>
                    <div class="totalBd" style="background-color: #fff; height: auto; overflow: hidden;">
                        <ul class="zhcz" style="height: 780px; padding-left: 90px; overflow-y:auto; overflow-x:hidden; margin-top: 20px;">
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/Images/cont_tbl_img20.jpg" alt="" /></div>
                                <strong class="text05">点卡充值</strong><br />
                                使用点卡充值卡，在官网上进行<br />
                                充值。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/PointCard.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%  if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["HC_MD5key"]))
                                {
                            %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/huichao.png" alt="" title="汇潮网银" width="106px" height="84px" /></div>
                                <strong class="text05">网上银行充值</strong><br />
                                支持工商、招商、农业、建设、等
                                <br />
                                国内银行和信用卡。
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/HS/AddOrder.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <% }%>
                            <%  if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["merchant_code"]))
                                {
                            %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/zhifu.png" alt="" title="智付网银" width="106px" height="84px" /></div>
                                <strong class="text05">网上银行充值</strong><br />
                                支持工商、招商、农业、建设、等
                                <br />
                                国内银行和信用卡。
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/Zhifu/default.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/jw2.jpg" title="智付点卡" width="106px" height="84px" /></div>
                                <strong class="text05">智付点卡充值</strong><br />
                                全国骏网一卡通盛大卡、神州行、征途卡、Q币卡、联通卡....充值、
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Zhifu/CardPay.aspx" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <% }%>
                            <%if (UiCommon.StringConfig.YeepayMerID != "")
                              { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/yeepay.png" alt="" title="易宝网银" width="106px" height="84px" /></div>
                                <strong class="text05">网上银行充值</strong><br />
                                支持工商、招商、农业、建设、等
                                <br />
                                国内银行和信用卡。
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=Bank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <% }%>
                            <%if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["merhantId"]))
                              { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/jw2.jpg" title="易宝点卡" width="106px" height="84px" /></div>
                                <strong class="text05">易宝点卡充值</strong><br />
                                全国骏网一卡通盛大卡、神州行、征途卡、Q币卡、联通卡....充值、
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/req.aspx" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                            <!--<li>
                       <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/jftpay.gif" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">聚付通在线支付</strong><br />
                        支持工商、招商、农业、建设等<br />
                        国内20家银行卡充值
                        <p style="padding-top: 15px;">
                            <a href="/Manage/Pay/JFTpay/Default.aspx" target="_blank">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>-->
                            <%--<li style="display: none;">
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/Images/pay/pay_05.jpg" alt="" width="106px" height="84px" /></div>
                                <strong class="text05">神州行充值卡充值</strong><br />
                                仅限移动用户，用神州行充值<br />
                                卡面额进行充值。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=SZX-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li style="display: none;">
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/Images/pay/czk.jpg" alt="" width="106px" height="84px" /></div>
                                <strong class="text05">联通卡充值</strong><br />
                                用联通卡充值卡面额进行充值。<br />
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=UNICOM-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li style="display: none;">
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/pay/zt.jpg" alt="征途游戏卡充值" width="106px" height="84px" /></div>
                                <strong class="text05">征途游戏卡充值</strong><br />
                                用征途游戏卡充值。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=ZHENGTU-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/pay/qq.jpg" alt="Q币支付充值" width="106px" height="84px" /></div>
                                <strong class="text05">Q币支付充值</strong><br />
                                Q币支付充值。<br />
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=QQCARD-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/jw.jpg" alt="全国骏网一卡通充值" width="106px" height="84px" /></div>
                                <strong class="text05">全国骏网一卡通充值</strong><br />
                                全国骏网一卡通充值。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=JUNNET-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/pay/sd.jpg" alt="盛大游戏卡充值" width="106px" height="84px" /></div>
                                <strong class="text05">盛大游戏卡充值</strong><br />
                                盛大游戏卡充值。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=SNDACARD-NET" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>--%>
                            <% if (UiCommon.StringConfig.AlipayPartnerID != "")
                              { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/Images/pay/zfb.jpg" alt="" width="106px" height="84px" /></div>
                                <strong class="text05">支付宝在线支付</strong><br />
                                支持工商、招商、农业、建设、等<br />
                                国内27家银行和信用卡
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/AliPay/Default.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <!--<li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/ybykt.jpg" alt="易宝一卡通充值" width="106px" height="84px" /></div>
                            <strong class="text05">易宝一卡通充值</strong><br />
                            易宝一卡通充值。
                            <p style="padding-top: 15px;">
                                <a href="/Manage/Pay/Yeepay2/Yeepay.aspx?params=YPCARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>-->
                            <%} %>
                            <% if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["merhantId"]))
                               { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/ybykt.jpg" title="易宝一卡通充值" width="106px" height="84px" /></div>
                                <strong class="text05">充值卡充值</strong><br />
                                全国骏网一卡通盛大卡、神州行、征途卡、Q币卡、联通卡....充值
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/Yeepay2/req.aspx" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                            <% if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["mbp_key"]))
                               { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/Images/pay/mobao.png" alt="" width="106px" height="84px" /></div>
                                <strong class="text05">MO宝在线支付</strong><br />
                                支持工商、招商、农业、建设、等<br />
                                国内银行和信用卡
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/MoBao/normalPay.aspx?params=MoBao" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                            <% if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["MemberID"]))
                               { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/baofu.png" alt="" width="106px" height="84px" /></div>
                                <strong class="text05">宝付在线充值</strong><br />
                                支持点卡、充值卡、网银等进行<br />
                                充值。
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/Baofoo/default.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                            <% if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["WX_MD5key"]))
                               { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/weixin.png" title="星启天微信支付" width="106px" height="84px" /></div>
                                <strong class="text05">微信支付</strong><br />
                                <br />
                                扫描支付充值。
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/WX/AddOrder.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                            <% if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["pc_MD5key"]))
                               { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/pay_02.jpg" title="星启天点卡" width="106px" height="84px" /></div>
                                <strong class="text05">点卡支付</strong><br />
                                <br />
                                支持盛大卡、神州行、征途卡、Q币卡、联通卡....充值
                                <p style="padding-top: 15px;">
                                    <a target="_blank" href="/Manage/Pay/PCard/default.aspx">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                             <%if (!string.IsNullOrEmpty(ConfigurationManager.AppSettings["Jubao_partnerid"]))
                              { %>
                            <li>
                                <div class="fl" style="padding-right: 14px;">
                                    <img src="/images/Pay/pay_01.jpg" title="聚宝网银充值" width="106px" height="84px" /></div>
                                <strong class="text05">网银充值</strong><br />
                                支持各大银行。
                                <p style="padding-top: 15px;">
                                    <a href="/Manage/Pay/jubao/default.aspx" target="_blank">
                                        <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                            </li>
                            <%} %>
                        </ul>
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
            <script src="/js/jquery-1.7.2.min.js" type="text/javascript">

            </script>
            <script src="/js/scroll.js" type="text/javascript"></script>
            </form>
            <div class="footcopy" id="newfooter">
                <div class="footcooper mgt">
                    <a target="_blank" href="#" rel="nofollow">关于我们</a> <a target="_blank" href="#">商务合作</a>
                    <a target="_blank" href="#" rel="nofollow">加入我们</a> <a target="_blank" href="/Service.aspx"
                        rel="nofollow">客服中心</a> <a target="_blank" href="/abc.html">家长监护</a> <a target="_blank"
                            href="/Service.aspx">问题反馈</a>
                </div>
                <div class="link mgt" style="">
                    <p class="fl link_l" style="text-align: center;">
                        <strong class="fr fl_txt">友情链接：</strong></p>
                    <p class="fl link_r">
                        <asp:Repeater runat="server" ID="rptLink">
                            <ItemTemplate>
                                <a target="_blank" href="<%#Eval("Link") %>" title="<%#Eval("LinkDes") %>">
                                    <%#Eval("LinkDes") %></a></ItemTemplate>
                        </asp:Repeater>
                    </p>
                </div>
                <div class="footer_info mgt" style="">
                    <div style="float: left;">
                        <img alt="游戏平台" src="/hnfooter/static/images/f_logo.jpg"></div>
                    <div class="f_p" style="float: left;">
                        <p class="" style="">
                            健康游戏忠告：抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当 适度游戏益脑 沉迷游戏伤身 合理安排 时间享受健康生活<br />
                            <a rel="nofollow" href="#" target="_blank">
                                <%= SiteConfig.GetParaValue("文化经营许可证")%></a> <a rel="nofollow" href="http://www.miibeian.gov.cn/"
                                    target="_blank">
                                    <%= SiteConfig.GetParaValue("SiteICP")%></a> <a rel="nofollow" href="#" target="_blank">
                                        地址：<%= SiteConfig.GetParaValue("公司地址")%></a><br />
                            <%= SiteConfig.GetParaValue("Title")%>
                            Copyright &copy;
                            <%= SiteConfig.GetParaValue("copyright")%>
                            版权所有 未经授权禁止转载、摘编、复制或建立镜像
                        </p>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript">
        $(document).ready(
        function () {
            $('.nav').find('li').eq(2).addClass('current');
            $('.nav').find('li').each(function () {
                $(this).addClass("menulist");
            }
            )
        });
    </script>
</body>
</html>
