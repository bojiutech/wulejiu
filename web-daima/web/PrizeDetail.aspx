<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PrizeDetail.aspx.cs" Inherits="HN.Web.PrizeDetail" %>
<%@ Register Src="/Public/NewFooter.ascx" TagName="NewFooter" TagPrefix="uc1" %>
<!doctype html>
<html>
<head>
    <meta charset="gbk">
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
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <style type="text/css">
        .footer_info
        {
            padding: 0px 0px 20px 0px;
        }
        .footer_info .f_p
        {
            margin-left: 20px;
            line-height: 23px;
        }
        .footer_info .f_p a
        {
            padding: 0 10px 0 0;
            color: #656565;
        }
        .footer_info .f_p a:hover
        {
            text-decoration: underline;
        }
        
        .clear:after
        {
            content: ".";
            display: block;
            height: 0;
            clear: both;
            visibility: hidden;
        }
        .clear
        {
            zoom: 1;
        }
        .tabTXT
        {
            height: 28px;
            border: 1px solid #cfcece;margin-bottom:2px;
        }
        table th
        {
            line-height: 28px; 
        }
        table label
        {
            font-size: 14px;
            font-weight: bold;
        }
        .btn_01
        {
            background-image: no-repeat url(/image/duihuan.png);
        }
    </style>
</head>
<body>
    <div id="min_max_width">
        <div class="jj_nav_hot jj_nav_hot_inner" id="jj_nav_hot">
            <div class="jj_nav_info">
                <div class="min_max_adap">
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
                    奖品中心</a> <span class="s">></span>
            </div>
            <div class="inner_thr_box">
                <div class="inner_thr_top" id="inner_thr_top">
                    <div class="le">
                        <img src="<%= PrizeDetailPic%>" /></div>
                    <div class="ri">
                        <h1>
                            <%=AwardName %></h1>
                        <div class="qc">
                            <span class="q">所需<%=UiCommon.StringConfig.GoldName%>：
                                <%=UiCommon.StringConfig.AddZeros(AwardMoney)%></span></div>
                        <div class="qc">
                            <span class="q">库存数：
                                <%=AwardCount%></span></div>
                        <div class="js">
                            物品图片仅供参考，请以实物为准，本公司拥有最终解释权！</div>
                    </div>
                </div>
                <div class="prize_detail">
                    <div class="ti">
                        图文详情</div>
                    <div class="img_li" id="prize_detail">
                        <%= Server.HtmlDecode(AwardInfo) %>
                        <form id="Form1" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
                        <div class="totalBd">
                            <div class="dtjs" style="">
                                <br />
                                <strong>请认真填写您的姓名和联系方式以及详细收货地址，以便确保您所兑换的奖品准确送到您的手中!</strong>
                                <br />
                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                                <div>
                                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                        <tr>
                                            <td colspan="2" style="display: none;">
                                                当前拥有的奖券数：<%=jq %>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th width="30%" align="right" scope="row">
                                                <label for="id01">
                                                    真实姓名：</label>
                                            </th>
                                            <td width="70%">
                                                <asp:TextBox ID="txtTrueName" runat="server" CssClass="tabTXT" MaxLength="20" Width="365px"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" scope="row">
                                                <label for="id01">
                                                    联系电话：</label>
                                            </th>
                                            <td>
                                                <asp:TextBox ID="txtPhone" runat="server" CssClass="tabTXT" MaxLength="20" Width="365px"></asp:TextBox>
                                                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPhone"
                                                    Display="Dynamic" ErrorMessage="电话号码不能空！"></asp:RequiredFieldValidator>
                                                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ControlToValidate="txtPhone"
                                                    Display="Dynamic" ErrorMessage="请输入正确的电话号码！" ValidationExpression="^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$"></asp:RegularExpressionValidator>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" scope="row">
                                                <label for="id01">
                                                    收货地址：</label>
                                            </th>
                                            <td>
                                                <asp:TextBox ID="txtAddress" runat="server" CssClass="tabTXT" MaxLength="100" Width="365px"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" scope="row">
                                                <label for="id01">
                                                    备注信息：</label>
                                            </th>
                                            <td>
                                                <asp:TextBox ID="txtUserRemark" runat="server" CssClass="tabTXT" Rows="2" TextMode="MultiLine"
                                                    Width="365px" MaxLength="500"></asp:TextBox>
                                            </td>
                                        </tr>
                                        <tr style="margin-top: 10px;">
                                            <td colspan="2" align="center">
                                                <a>
                                                    <asp:ImageButton runat="server" ID="imgBtn" ImageUrl="/image/duihuan.png" OnClick="button5_ServerClick" /></a>
                                            </td>
                                        </tr>
                                    </table>
                                </div>
                                <script type="text/javascript">
    <!--
                                    function onFormSubmit(f) {

                                        //            var pass  = document.getElementById("txtPassword");
                                        //            if(!alertNull(pass,"请先输入您的密码！")){
                                        //				return false;
                                        //            }

                                        //真实姓名-----------
                                        var txtTrueName = document.getElementById('txtTrueName');
                                        if (!alertNull(txtTrueName, '请输入真实姓名！')) {
                                            return false;
                                        }

                                        //联系电话-----------
                                        var txtPhone = document.getElementById('txtPhone');
                                        if (!alertNull(txtPhone, '请输入联系电话！')) {
                                            return false;
                                        }

                                        //联系地址-----------
                                        var txtAddress = document.getElementById('txtAddress');
                                        if (!alertNull(txtAddress, '请输入收货地址！')) {
                                            return false;
                                        }

                                        var o = document.getElementById("txtUserRemark");
                                        if (o.value.length > 500) {
                                            alert('备注不能超过500个字符');
                                            return false;
                                        }

                                        return true;
                                    }
     //-->
                                </script>
                            </div>
                        </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
        <div class="h_30px">
        </div>
    </div>
<uc1:NewFooter runat="server" id="new1" style="width: 980px; margin: 0 auto" />
    <script type="text/javascript" src="../../hn_css/js/www/www.jj.cn_pub_15.js" charset="gb2312"></script>
    <script type="text/javascript" src="../../hn_css/js/www/jj.cn_prize.js" charset="gb2312"></script>
    <div class="pop_win_prize" id="pop_win_prize">
        <div class="pop_win_info">
            <div class="tit">
                <span></span><a class="c"></a>
            </div>
            <div class="info" style="padding: 10px; height: 482px; overflow: hidden; text-align: center;">
            </div>
        </div>
        <div class="pop_win_bg">
        </div>
    </div>
    <div class="return_top" id="return_top">
        <a title="回到顶部" href="#"></a>
    </div>
    <script type="text/javascript">
        function inner_win_three() {
            $(".inner_thr_box .inner_thr_top .ri .lc a").eq(0).click(function () {
                win_fn("客户端兑奖中心", "../../hn_img/www/prize/pc_win.jpg");
            });
            $(".inner_thr_box .inner_thr_top .ri .lc a").eq(1).click(function () {
                win_fn("手机端兑奖中心", "../../hn_img/www/prize/ph_win.jpg");
            });
            function win_fn(title, img) {
                $(".pop_win_prize").show();
                $(".pop_win_prize .pop_win_info .tit span").html(title)
                $(".pop_win_prize .pop_win_info .info").html('<img src="' + img + '"/>')
                var win_height = $(window).height();
                var pop_height = $(".pop_win_info").height();
                $(".pop_win_info").css({ "top": (win_height - pop_height) / 2 })
            }
            $(".pop_win_prize .pop_win_info .tit .c,.pop_win_prize .pop_win_bg").click(function () {
                $("#pop_win_prize").hide()
            });
        }
        $(function () {
            //jj_cn_prizw.detail_ajax();
        })
    </script>
</body>
</html>
