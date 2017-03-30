<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="fx.aspx.cs" Inherits="HN.Web.download.fx" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>
        <%= SiteConfig.GetParaValue("Title")%>游戏世界,中国最专业的棋牌游戏世界</title>
    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/theme.css" rel="stylesheet">
    <link href="css/bootstrap-reset.css" rel="stylesheet">
    <link rel="stylesheet" href="assets/font-awesome/css/font-awesome.css" />
    <link rel="stylesheet" href="assets/revolution_slider/css/rs-style.css" media="screen">
    <link rel="stylesheet" href="assets/revolution_slider/rs-plugin/css/settings.css"
        media="screen">
    <!-- Custom styles for this template -->
    <link href="css/common.css" rel="stylesheet">
    <link href="css/style-responsive.css" rel="stylesheet" />
    <!-- HTML5 shim and Respond.js IE8 support of HTML5 tooltipss and media queries -->
    <!--[if lt IE 9]>
      <script src="js/html5shiv.js"></script>
      <script src="js/respond.min.js"></script>
    <![endif]-->
    <style type="text/css">
        .tips { top: 0px; margin-top: 0px; vertical-aligin: top; position: absolute; z-index: 20000000; text-align: center; display: none; cursor: pointer; }
        .tips { margin-top: 0px; text-align: right; }
    </style>
</head>
<body onresize="bb()" click="closes()">
    <div class="tips" onclick="closes()">
        <img class="imgtip" />
    </div>
    <div class="container">
        <div class="row">
            <div class="col-md-6">
                <div class="ngame_detail_box">
                    <div class="ngame_detail_info">
                        <img src="/download/img/logo.png" alt="" class="ng_d_i_img" />
                        <div class="ng_d_info">
                            <h2>
                                <%= SiteConfig.GetParaValue("Title")%>游戏平台</h2>
                            <div class="g_d_t_sec">
                                <div class="s_l_c_r_xing">
                                    <p style="width: 82%;">
                                    </p>
                                </div>
                                <div class="g_d_t_bq s_l_c_r_thr">
                                    <span class="g_d_t_nobac">8.2&nbsp;分</span>
                                </div>
                            </div>
                            <p class="g_d_t_nums">
                                游戏类型：棋牌游戏&nbsp;&nbsp;</p>
                            <div class="s_l_c_r_thr">
                                <span>安全无毒</span> <span>免费</span> <span class="s_l_c_r_tan">权限：1</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-md-6">
                <div class="ng_d_i_right">
                    <a onclick="checkWeixin(this)" class="ng_downandrio"></a>
                    <br />
                    <a onclick="checkWeixin(this)" style="display: none" href="itms-services://?action=download-manifest&url=https://www.myzc0373.com/download/APP/HNWL.plist"
                        class="ng_downios"></a>
                </div>
            </div>
        </div>
        <div class="row">
            <div class="col-md-8">
                <div class="ng_l_left">
                    <!-- begin libao  -->
                    <!-- end libao  -->
                    <div class="ng_lb_box">
                        <div class="ng_lb_b_details">
                            <div class="def_menu_line">
                                <div style="padding: 0px;">
                                    精彩图集</div>
                            </div>
                            <div class="span12 about-carousel">
                                <div id="myCarousel" class="carousel slide">
                                    <!-- Carousel items -->
                                    <div class="carousel-inner">
                                        <div class="item  active">
                                            <img src="img/1.jpg" alt="">
                                            <div class="carousel-caption">
                                                <p>
                                                    <%= SiteConfig.GetParaValue("Title")%>游戏世界</p>
                                            </div>
                                        </div>
                                        <div class="item ">
                                            <img src="img/2.jpg" alt="">
                                            <div class="carousel-caption">
                                                <p>
                                                    <%= SiteConfig.GetParaValue("Title")%>游戏世界</p>
                                            </div>
                                        </div>
                                        <div class="item">
                                            <img src="img/4.jpg" alt="">
                                            <div class="carousel-caption">
                                                <p>
                                                    <%= SiteConfig.GetParaValue("Title")%>游戏世界</p>
                                            </div>
                                        </div>
                                    </div>
                                    <!-- Carousel nav -->
                                    <a class="carousel-control left" href="#myCarousel" data-slide="prev"><i class="icon-angle-left">
                                    </i></a><a class="carousel-control right" href="#myCarousel" data-slide="next"><i
                                        class="icon-angle-right"></i></a>
                                </div>
                            </div>
                            <div runat="server" id="divCode" visible="false">
                                <h1>
                                    邀请码为：</h1>
                                <big><b style="font-size: 28px; font-weight: bold;">
                                    <%=inviteCode%></b></big>
                            </div>
                            <div class="def_menu_line">
                                <div style="padding: 0px;">
                                    游戏详情</div>
                            </div>
                            <div class="ng_lb_b_d_conts">
                                <div class="ng_lb_b_d_c_div" style="font-size: 16px; line-height: 33px;">
                                    <a href="#game-snap" class="first-snap">
                                        <img class="game-snap-img" src="" alt="游戏截图"></a>
                                    <%=gameinfo %>
                                </div>
                            </div>
                            <div class="def_menu_line" style="display: none">
                                <div style="padding: 0px;">
                                    游戏攻略</div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="downloadbarpace">
        </div>
        <a onclick="checkWeixin(this)" target="_blank">
            <div class="navbar-fixed-bottom downLoadBar" style="position: fixed; right: 0; left: 0;
                border-width: 0 0 1px;">
                立即下载安装
            </div>
        </a><a onclick="checkWeixin(this)" style="display: none;">
            <div class="navbar-fixed-bottom downLoadBar">
                苹果手机下载
            </div>
        </a>
    </div>
    <iframe id="frame1" style="display:none"></iframe>
    <script>
        var slider = {
            //判断设备是否支持touch事件
            touch: ('ontouchstart' in window) || window.DocumentTouch && document instanceof DocumentTouch,
            slider: document.getElementById('slider'),

            //事件
            events: {
                index: 0,     //显示元素的索引
                slider: this.slider,     //this为slider对象
                icons: document.getElementById('icons'),
                icon: this.icons.getElementsByTagName('span'),
                handleEvent: function (event) {
                    var self = this;     //this指events对象
                    if (event.type == 'touchstart') {
                        self.start(event);
                    } else if (event.type == 'touchmove') {
                        self.move(event);
                    } else if (event.type == 'touchend') {
                        self.end(event);
                    }
                },
                //滑动开始
                start: function (event) {
                    var touch = event.targetTouches[0];     //touches数组对象获得屏幕上所有的touch，取第一个touch
                    startPos = { x: touch.pageX, y: touch.pageY, time: +new Date };    //取第一个touch的坐标值
                    isScrolling = 0;   //这个参数判断是垂直滚动还是水平滚动
                    this.slider.addEventListener('touchmove', this, false);
                    this.slider.addEventListener('touchend', this, false);

                },
                //移动
                move: function (event) {
                    //当屏幕有多个touch或者页面被缩放过，就不执行move操作
                    if (event.targetTouches.length > 1 || event.scale && event.scale !== 1) return;
                    var touch = event.targetTouches[0];
                    endPos = { x: touch.pageX - startPos.x, y: touch.pageY - startPos.y };
                    isScrolling = Math.abs(endPos.x) < Math.abs(endPos.y) ? 1 : 0;    //isScrolling为1时，表示纵向滑动，0为横向滑动
                    if (isScrolling === 0) {
                        event.preventDefault();      //阻止触摸事件的默认行为，即阻止滚屏
                        this.slider.className = 'cnt';
                        this.slider.style.left = -this.index * 600 + endPos.x + 'px';
                    }
                },
                //滑动释放
                end: function (event) {
                    var duration = +new Date - startPos.time;    //滑动的持续时间
                    if (isScrolling === 0) {    //当为水平滚动时
                        this.icon[this.index].className = '';
                        if (Number(duration) > 10) {
                            //判断是左移还是右移，当偏移量大于10时执行
                            if (endPos.x > 10) {
                                if (this.index !== 0) this.index -= 1;
                            } else if (endPos.x < -10) {
                                if (this.index !== this.icon.length - 1) this.index += 1;
                            }
                        }
                        this.icon[this.index].className = 'curr';
                        this.slider.className = 'cnt f-anim';
                        this.slider.style.left = -this.index * 600 + 'px';
                    }
                    //解绑事件
                    this.slider.removeEventListener('touchmove', this, false);
                    this.slider.removeEventListener('touchend', this, false);
                }
            },

            //初始化
            init: function () {
                var self = this;     //this指slider对象
                if (!!self.touch) self.slider.addEventListener('touchstart', self.events, false);    //addEventListener第二个参数可以传一个对象，会调用该对象的handleEvent属性
            }
        };

        slider.init();
    </script>
    <script type="text/javascript">
        window.onload = function () {
            $(".imgtip").css("width", $(window).width());

            var scheme = '<%=Request["scheme"] %>';
            if (scheme != '') {
                var u = navigator.userAgent;
                if (u.indexOf('Android') > -1 || u.indexOf('Linux') > -1) {//安卓手机
                    $("#frame1").attr('src', '<%=Request["scheme"] %>://<%=Request["host"] %>/<%=Request["open"] %>?nameID=<%=Request["nameID"] %>&password=<%=Request["password"] %>');
                }
                else if (u.indexOf('iPhone') > -1 || u.indexOf('iPad') > -1) {//
                    $("#frame1").attr('src', '<%=Request["scheme"] %>://nameID=<%=Request["nameID"] %>&password=<%=Request["password"] %>');
                }
            }
        }
        function checkWeixin(o) {
            //        var apple = document.getElementById("apple");src="img/appletips.png"imgtip

            var scheme = '<%=Request["scheme"] %>';
            var u = navigator.userAgent;
            if (u.indexOf('Android') > -1 || u.indexOf('Linux') > -1) {//安卓手机
                o.href = scheme != '' ? '<%=Request["scheme"] %>://<%=Request["host"] %>/<%=Request["open"] %>?nameID=<%=Request["nameID"] %>&password=<%=Request["password"] %>' : '<%=apkurl %>';


            } else if (u.indexOf('iPhone') > -1 || u.indexOf('iPad') > -1) {//
                //o.href = "itms-services://?action=download-manifest&url=https://www.xxx.com/download/myzc.plist";
                o.href = scheme != '' ? '<%=Request["scheme"] %>://nameID=<%=Request["nameID"] %>&password=<%=Request["password"] %>' : '<%=ipaurl %>';
            }

            if (isWeiXin()) {
                o.href = "javascript:void()";

                if (u.indexOf('Android') > -1 || u.indexOf('Linux') > -1) {//安卓手机
                    $(".imgtip").attr("src", "img/androdtips.png");
                    $(".tips").css("display", "block");
                    showdiv();


                }
                else if (u.indexOf('iPhone') > -1) {//苹果手机
                    $(".imgtip").attr("src", "img/appletips.png");
                    $(".tips").css("display", "block");
                    showdiv();
                    // o.href = "itms-services://?action=download-manifest&url=https://www.myzc0373.com/download/myzc.plist";
                }
            }

        }

        function isWeiXin() {
            var ua = window.navigator.userAgent.toLowerCase();
            if (ua.match(/MicroMessenger/i) == 'micromessenger') {
                return true;
            } else {
                return false;
            }
        }
        function showdiv() {

            var div_obj = $(".tips");
            //窗口宽度,高度
            var winWidth = $(window).width();
            var winHeight = $(window).height();
            //弹出的div的宽度,高度
            var popHeight = 0;
            var popWidth = 0;
            //div窗口居中显示加滚动条的位置top(滚动后div的居中高度)(winHeight - popHeight) / 2 + $(document).scrollTop()
            div_obj.animate({ opacity: "show", left: 0, top: $(document).scrollTop(), width: winWidth, height: winHeight }, 300);



        }

        function bb() {
            $(".imgtip").css("width", $(window).width());

        }

        function closes() {

            $(".tips").css("display", "none");

        }
        window.onscroll = function () {

            $(".tips").css("display", "none");

        }
    </script>
    <!--内容部分-->
    <!--在页面底部加载js可以加快页面的加载速度-->
    <script src="js/jquery.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
</body>
</html>
