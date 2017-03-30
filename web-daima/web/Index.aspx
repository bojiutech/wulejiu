<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="Bzw.Web.Index" %>

<%@ Register Src="/Public/NewFooter.ascx" TagName="NewFooter" TagPrefix="uc1" %>
<!doctype html>
<html>
<head>
    <meta charset="gb2312">
    <meta name="keywords" content="斗地主,麻将,德州扑克,单机斗地主,欢乐斗地主,真人斗地主,斗地主手机版,麻将,网页,游戏,大厅,免费下载" />
    <meta name="description" content="斗地主，是全国最大的斗地主、麻将、德州扑克等棋牌类游戏在线竞技平台。以竞技为核心，通过组织比赛的形式，让您在紧张刺激中享受游戏的乐趣。" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Cache-Control" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <title>舞乐久在线棋牌竞技平台-享受棋牌竞技的快乐</title>
    <script src="../hn_css/js/jquery.js" type="text/javascript"></script>
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script type="text/javascript" src="../hnlogin/www/js/jquery-1.8.3.min.js"></script>
    <script type="text/javascript" src="../hnlogin/www/js/base.min.js"></script>
    <script type="text/javascript">
        function getQueryString(name) {
            var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)", "i");
            var r = location.search.substr(1).match(reg);
            if (r != null) {
                return unescape(decodeURI(r[2]));
            }
            return null;
        }
        (function () {
            try {
                var showtype = getQueryString("showtype") || '';
                if (showtype == 'pc') {
                    return null;
                }
            } catch (e) { }
            if (/gt-p1000|iphone|android|phone|mobile|wap|netfront|java|operamobi|operamini|ucweb|windowsce|symbian|series|webos|sony|blackberry|dopod|nokia|samsung|palmsource|xda|pieplus|meizu|midp|cldc|motorola|foma|docomo|up.browser|up.link|blazer|helio|hosin|huawei|novarra|coolpad|webos|techfaith|palmsource|alcatel|amoi|ktouch|nexian|ericsson|philips|sagem|wellcom|bunjalloo|maui|smartphone|iemobile|spice|bird|zte-|longcos|pantech|gionee|portalmmm|jigbrowser|hiptop|benq|haier|^lct|320x320|240x320|176x220|mqqbrowser/i.test(navigator.userAgent.toLowerCase())) {
                //window.location.href = '#';

            }
        })();
    </script>
    <style type="text/css">
@charset "gb2312";
html{color:#333;}body,div,dl,dt,dd,ul,ol,li,h1,h2,h3,h4,h5,h6,pre,code,form,fieldset,legend,input,textarea,p,blockquote,th,td{margin:0;padding:0;}table{border-collapse:collapse;border-spacing:0}fieldset,img{border:0}address,caption,cite,code,dfn,em,th,var{font-style:normal;font-weight:normal}ol,ul{list-style:none}caption{text-align:left}h1,h2,h3,h4,h5,h6{font-size:100%;font-weight:normal}q:before,q:after{content:''}abbr,acronym{border:0;font-variant:normal}sup{vertical-align:text-top}sub{vertical-align:text-bottom}input,textarea,select{font-family:inherit;font-size:inherit;font-weight:inherit}input,textarea,select{*font-size:100%}legend{color:#000}
html,body{ font-family:"Microsoft YaHei", Arial; color:#3c3c3c;}
img{ border:0;}
a{text-decoration:none; color:#3c3c3c; outline:none;}
a:hover{ color:#c16b13;}
em{ font-style:normal;}
.h_1px{ height:1px; line-height:1px; overflow:hidden; clear:both;}
.bg_f7f7f7{ background:#f7f7f7;}
.min_max_adap{ width:1200px; margin:0 auto; position:relative;}
.jj_nav_hot{ height:612px; color:#FFF;
-webkit-transition:opacity 0.8s ease;
-moz-transition:opacity 0.8s ease;
-ms-transition:opacity 0.8s ease;
-o-transition:opacity 0.8s ease;
transition:opacity 0.8s ease;}
.jj_nav_hot a{ color:#FFF;}
.jj_nav_info .usr{ padding-right:40px; position:absolute; padding-right:142px; top:14px; right:10px; line-height:30px; font-size:14px; z-index:10;}
.jj_nav_info .usr .down{ width:106px; height:20px; display:block; position:absolute; right:0; top:3px;}
.jj_nav_info .usr .down .jt{ width:100px; height:30px; background:url(../hn_img/www/hn/xiala_but_bg.png) center bottom no-repeat; _background:url(../hn_img/www/hn/xiala_but_bg.gif) center bottom no-repeat; padding-left:28px; padding-top:3px; display:block; position:absolute; top:-5px; right:0; cursor:pointer; color:#d3e2ef; color:rgba(255,255,255,0.50); overflow:hidden;}
.jj_nav_info .usr .down .li{ width:371px; height:102px; background:url(../hn_img/www/hn/xiala_but_bg_hov.png) right -26px; _background:url(../hn_img/www/hn/xiala_but_bg_hov.gif) right -26px; position:absolute; top:24px; right:0; display:none;}
.jj_nav_info .usr .down_hov .jt{ background:url(../hn_img/www/hn/xiala_but_bg_hov.png) right top; _background:url(../hn_img/www/hn/xiala_but_bg_hov.gif) right top; cursor:default; color:#d74848; height:26px; line-height:30px;}
.jj_nav_info .usr .down_hov .li{ display:block;}
.jj_nav_info .usr .down .li a{ color:#717171;}
.jj_nav_info .usr .down .li dl{ position:absolute; top:4px; left:3px; line-height:32px; text-align:center;}
.jj_nav_info .usr .down .li dl dt{ width:121px; height:46px; line-height:46px; float:left;}
.jj_nav_info .usr .down .li dl dt.d1{ border-bottom:1px solid #c3e5e6; border-right:1px solid #c3e5e6;}
.jj_nav_info .usr .down .li dl dt.d2{ border-bottom:1px solid #c3e5e6;}
.jj_nav_info .usr .down .li dl dt.d3{ border-right:1px solid #c3e5e6;}
.jj_nav_info .usr .down .li dl dt a{ display:block;}
.jj_nav_info .usr .down .li dl dt a:hover{ background:#c2e4e4; color:#419bd2;}
.jj_nav_info .usr .down .li dl dt a:active{ background:#4c97bf; color:#464f54;}
.jj_nav_info .usr .nh,
.jj_nav_info .usr .name{ color:#f4f0a2;}
.jj_nav_info{ position:absolute; width:100%; top:0; left:0; z-index:2;}
.jj_nav_info .logo{ position:absolute; left:10px; top:38px;}
.jj_nav_info .logo a{ width:210px; height:80px; display:block; _background:url(../hn_img/www/hn/hn_logo.gif);}
.jj_nav_info .logo img{ _display:none;}
.jj_nav_info .nav{ position:absolute; left:340px; top:63px; height:32px; line-height:32px; font-size:18px;}
.jj_nav_info .nav li{ float:left; margin-right:20px; display:inline-block; position:relative;}
.jj_nav_info .nav li a{ color:#FFFFFF; padding:0 16px 0 46px; float:left;}
.jj_nav_info .nav li a:hover,.jj_nav_info .nav li.hov a{ color:#fffdd3;}
.jj_nav_info .nav li span{ width:32px; height:32px; background:url(../hn_img/www/hn/jj_nav_bg.png); _background:url(../hn_img/www/hn/jj_nav_bg.gif); position:absolute; left:10px; top:-1px;}
.jj_nav_info .nav li.hov{ background:rgba(0,0,0,0.2); border-radius:10px;}
.jj_nav_info .nav li span.s1{ background-position:left -96px;}
.jj_nav_info .nav li span.s2{ background-position:left top;}
.jj_nav_info .nav li span.s3{ background-position:left -32px;}
.jj_nav_info .nav li span.s4{ background-position:left -64px;}
.jj_nav_info .nav li a:hover span.s1,.jj_nav_info .nav li.hov a span.s1{ background-position:-32px -96px;}
.jj_nav_info .nav li a:hover span.s2{ background-position:-32px top;}
.jj_nav_info .nav li a:hover span.s3{ background-position:-32px -32px;}
.jj_nav_info .nav li a:hover span.s4{ background-position:-32px -64px;}
.jj_nav_info .dow{ position:absolute; top:206px; right:10px; color:#FFF; width:350px;}
.jj_nav_info .dow .dow_but{ width:350px; height:82px; background:url(../hn_img/www/hn/dow_but_bg.jpg);  position:absolute; top:110px;}
.jj_nav_info .dow .dow_but:hover{ background-position:left -85px;}
.jj_nav_info .dow .dow_but:active{ background-position:left -170px;}

.jj_nav_info .dow .h_tit{ padding-left:10px; line-height:36px;}
.jj_nav_info .dow .h_tit h1{ font-size:26px; color:#FFF; line-height:36px;}.jj_nav_info .dow .ph_dow { position:absolute; top:220px; width:100px; text-align:center; color:#FFF;}
.jj_nav_info .dow .ph_dow { position:absolute; top:220px; width:100px; text-align:center; color:#FFF;}
.jj_nav_info .dow .ph_dow h2{ line-height:36px; height:36px; display:block;}
.jj_nav_info .dow .ph_dow span{ width:88px; height:88px; display:block; margin:0 auto; background:url(../hn_img/www/hn/ph_dow_but_bg.png); _background:url(../hn_img/www/hn/ph_dow_but_bg.gif);}
.jj_nav_info .dow .ph_dow1{ left:5px;} 
.jj_nav_info .dow .ph_dow1:hover span{ background-position:left -92px;}
.jj_nav_info .dow .ph_dow1:active span{ background-position:left -184px;}
.jj_nav_info .dow .ph_dow2{ left:121px;}
.jj_nav_info .dow .ph_dow2 span{ background-position:-92px top;}
.jj_nav_info .dow .ph_dow2:hover span{ background-position:-92px -92px;}
.jj_nav_info .dow .ph_dow2:active span{ background-position:-92px -184px;} 
.jj_nav_info .dow .ph_dow3{ left:239px;}
.jj_nav_info .dow .ph_dow3 span{ background-position:-184px top;}
.jj_nav_info .dow .ph_dow3:hover span{ background-position:-184px -92px;}
.jj_nav_info .dow .ph_dow3:active span{ background-position:-184px -184px;} 
.jj_nav_info .dow .wm2{ background:#000; background:rgba(0,0,0,0.70); border-radius:10px; top:136px; width:130px; height:164px; position:absolute; left:-170px; padding:10px; text-align:center; display:none; z-index:10;}
.jj_nav_info .dow .wm2 img{ width:120px; height:120px; padding:5px; background:#FFF;}
.jj_nav_info .dow .wm2 span{ line-height:32px;}

.jj_hot_img{ position:absolute; height:612px; width:100%; top:0; left:0; z-index:1;}
.jj_hot_img .hot_img{ position:absolute; height:612px; width:100%; top:0; left:0;
-webkit-transition:all 0.8s ease;
-moz-transition:all 0.8s ease;
-ms-transition:all 0.8s ease;
-o-transition:all 0.8s ease;
transition:all 0.8s ease;
opacity:0;}
.jj_hot_img .hot_img .hot_img_len{ width:100%; height:612px; }
.jj_hot_img .hot_img .hot_img_len .min_max_adap{ height:612px; }
.jj_hot_img .hot_img .hot_img_len .aa{ width:683px; height:381px; position:absolute; top:157px; left:65px;}
.jj_hot_img .hot_img .hot_img_len1{background:#0082cc url(../hn_img/www/hn/hot_img_len01.png) center top; }
.jj_hot_img .hot_img .hot_img_len1 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len01towbg.jpg) left top; }
.jj_hot_img .hot_img .hot_img_len1 .aa{ background:url(../hn_img/www/hn/hot_img_len1_bb02.jpg) left top;}
.jj_hot_img .hot_img .hot_img_len2{background:#008857 url(../hn_img/www/hn/hot_img_len02.png) center top; }
.jj_hot_img .hot_img .hot_img_len2 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len02towbg.jpg) left top; }
.jj_hot_img .hot_img .hot_img_len2 .aa{ background:url(../hn_img/www/hn/hot_img_len2_bb02.jpg) left top;}
.jj_hot_img .hot_img .hot_img_len3{background:#df951f url(../hn_img/www/hn/hot_img_len03.png) center top; }
.jj_hot_img .hot_img .hot_img_len3 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len03towbg.jpg) left top; }
.jj_hot_img .hot_img .hot_img_len3 .aa{ background:url(../hn_img/www/hn/hot_img_len3_bb02.jpg) left top;}
.hot_img_nav{ position:absolute; top:570px; left:537px;}
.hot_img_nav li{ width:29px; height:13px; background:url(../hn_img/www/hn/hot_nav_bg.png) right top; _background:url(../hn_img/www/hn/hot_nav_bg.gif) right top; overflow:hidden; display:inline; float:left; margin:0 10px; cursor:pointer;}
.hot_img_nav li.hov{ background-position:left top;  cursor:default; }
.hot_img_nav li{ float:left;}
.jj_game_list{ padding:12px 0 24px;}
.jj_game_list .jj_ind_left{ width:780px; float:left;}
.jj_ind_tit{ height:58px; line-height:58px; padding:0 20px;}
.jj_ind_tit h2{ font-size:22px; float:left; font-family:"Microsoft YaHei",SimHei;}
.jj_ind_tit .mo{ float:right; font:14px; color:#3db5e6;}
.jj_ind_tit .mo span{ font-family:SimSun;}
.jj_game_icon { margin-top:5px;}
.jj_game_icon li{ width:155px; height:156px; float:left; position:relative;}
.jj_game_icon li a{ padding-top:17px; display:block; position:relative; z-index:1;}
.jj_game_icon li a span{ width:100px; width:100px; margin:0 auto; display:block;-webkit-transition:all 0.1s ease;
-moz-transition:all 0.1s ease;
-ms-transition:all 0.1s ease;
-o-transition:all 0.1s ease;
transition:all 0.1s ease;}
.jj_game_icon li a:hover span{ margin-top:-5px; padding-bottom:5px; opacity:0.9;}
.jj_game_icon li a:active span{ opacity:0.7; margin-top:-4px; padding-bottom:4px;}
.jj_game_icon li a span img{ width:100px; height:100px;}
.jj_game_icon li a h3{ font-size:16px; text-align:center; line-height:32px;}

.web_game_icon { margin-top:0;}
.web_game_icon li{ width:193px; height:210px;}
.web_game_icon li a{ width:193px; height:176px;}
.web_game_icon li a span,
.web_game_icon li a span img{ width:168px; height:134px;}
.web_game_icon li a h3{ line-height:48px;}

.jj_ind_right{ background:#f4f4f4; border:1px solid #EEE; float:right; width:386px;}
.jj_ind_right h3{ height:48px; clear:both; line-height:48px; font-size:22px; font-family:"Microsoft YaHei",SimHei; border-bottom:1px solid #EEE; padding:0 16px;}
.jj_ind_right .im{ float:right; margin-top:5px; margin-bottom:5px; border:1px solid red;}
.jj_ind_right .im img{ float:right; padding:8px 5px 5px 5px;-webkit-transition:all 0.2s ease;
-moz-transition:opacity 0.2s ease;
-ms-transition:opacity 0.2s ease;
-o-transition:opacity 0.2s ease;
transition:opacity 0.2s ease; width:376px;}
.jj_ind_right a:hover img{ opacity:0.9;}
.jj_ind_right2{ margin:15px 0 6px 0; background:#f9f9f9;}
.jj_ind_right2 .im img,.jj_ind_right3 .im img{ padding:5px;}
.jj_ind_right3{ margin:26px 0 6px 0; background:#f4f4f4;}
.tv_cooper{ height:150px;}
.tv_cooper{ width:100%;}
.tv_cooper li{ width:12.499%; float: left;}
.tv_cooper li a{ display: block; text-align:center;}
.tv_cooper li a span img{ width: 74px; height: 74px;}
.tv_cooper li a span{ width:74px; height:74px;}
/*980*/
.min_980 .jj_nav_hot,
.min_980 .jj_hot_img,
.min_980 .jj_hot_img .hot_img,
.min_980 .jj_nav_hot{ height:500px;}
.min_980 .jj_hot_img .hot_img .hot_img_len{ height:500px; }
.min_980 .jj_hot_img .hot_img .hot_img_len .min_max_adap{ height:500px; }
.min_980 .jj_hot_img .hot_img .hot_img_len .aa{ width:558px; height:311px;top:129px; left:53px;}
.min_980 .jj_hot_img .hot_img .hot_img_len1{background:url(../hn_img/www/hn/hot_img_len01980.png) center top; }
.min_980 .jj_hot_img .hot_img .hot_img_len1 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len01towbg980.jpg) left top; }
.min_980 .jj_hot_img .hot_img .hot_img_len1 .aa{ background:url(../hn_img/www/hn/hot_img_len1_bb02980.jpg) left top;}
.min_980 .jj_hot_img .hot_img .hot_img_len2{background:url(../hn_img/www/hn/hot_img_len02980.png) center top; }
.min_980 .jj_hot_img .hot_img .hot_img_len2 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len02towbg980.jpg) left top; }
.min_980 .jj_hot_img .hot_img .hot_img_len2 .aa{ background:url(../hn_img/www/hn/hot_img_len2_bb02980.jpg) left top;}
.min_980 .jj_hot_img .hot_img .hot_img_len3{background:url(../hn_img/www/hn/hot_img_len03980.png) center top; }
.min_980 .jj_hot_img .hot_img .hot_img_len3 .min_max_adap{background:url(../hn_img/www/hn/hot_img_len03towbg980.jpg) left top; }
.min_980 .jj_hot_img .hot_img .hot_img_len3 .aa{ background:url(../hn_img/www/hn/hot_img_len3_bb02980.jpg) left top;}
.min_980 .min_max_adap{ width:980px;}
.min_980 .jj_nav_info .nav li a{ padding:0 20px 0 45px; font-size:16px;}
.min_980 .jj_nav_info .dow{ width:310px; top:160px;}

.min_980 .jj_nav_info .dow .dow_but{ width:310px; background:url(../hn_img/www/hn/dow_but_bg_980.jpg); height:72px; top:90px;}
.min_980 .jj_nav_info .dow .dow_but:hover{ background-position:left -75px;}
.min_980 .jj_nav_info .dow .dow_but:active{ background-position:left -150px;}

.min_980 .jj_nav_info .dow .h_tit h1{ font-size:26px; line-height:36px;}
.min_980 .jj_nav_info .dow .h_tit span{ font-size:14px;}
.min_980 .jj_nav_info .dow .ph_dow span{ width:71px; height:71px; background:url(../hn_img/www/hn/ph_dow_but_bg_980.png); _background:url(../hn_img/www/hn/ph_dow_but_bg_980.gif);}
.min_980 .jj_nav_info .dow .ph_dow{ width:80px; top:186px;}
.min_980 .jj_nav_info .dow .ph_dow1:hover span{ background-position:left -74px;} 
.min_980 .jj_nav_info .dow .ph_dow1:active span{ background-position:left -148px;} 
.min_980 .jj_nav_info .dow .ph_dow2{ left:113px;}
.min_980 .jj_nav_info .dow .ph_dow2 span{ background-position:-74px top;} 
.min_980 .jj_nav_info .dow .ph_dow2:hover span{ background-position:-74px -74px;} 
.min_980 .jj_nav_info .dow .ph_dow2:active span{ background-position:-74px -148px;} 
.min_980 .jj_nav_info .dow .ph_dow3{ left:223px;}
.min_980 .jj_nav_info .dow .ph_dow3 span{ background-position:-148px top;} 
.min_980 .jj_nav_info .dow .ph_dow3:hover span{ background-position:-148px -74px;} 
.min_980 .jj_nav_info .dow .ph_dow3:active span{ background-position:-148px -148px;} 
.min_980 .jj_nav_info .dow .wm2{ left:-160px;}
.min_980 .hot_img_nav{ top:466px; left:427px;}
.min_980 .jj_nav_info .nav li span{ background-image:url(../hn_img/www/hn/jj_nav_bg_980.png);} background-image:url(../hn_img/www/hn/jj_nav_bg_980.png);
.min_980 .jj_nav_info .nav{ left:300px;}




.pub_footer{ background:url(../hn_img/images/newIndex/download/v2/pub_footer_bg.png) repeat-x top; text-align:center;color:#9e9e9e;  height:114px; font-size:14px;}
.pub_footer .pf_box{width:980px; margin:0 auto; position:relative;}
.pub_footer .n{ line-height:40px; padding-top:10px; }
.pub_footer .n a{color:#6c6c6c; margin:0 15px;}
.pub_footer .i{ line-height:24px; font-size:12px;}
.pub_footer .m{ position:absolute; top:25px; right:60px; }
.pub_footer .huang_dao{ position:absolute; left:0; top:10px;}
.pub_footer .aa{ position:absolute; top:20px; right:0;}
.pub_footer .a2{ right:60px; top:26px;}
.pub_footer .a3{ right:106px;}
.pub_footer .a4{ right:160px;}

.mainLeft
{
   
    }
.mainLeftUL li
{
    position:relative; width:435px; float:left; height:140px; padding-top:10px; padding-bottom:10px;
    }
   .mainLeftUL li h3
{
  font-size: 16px;
 font-weight:bold;
  line-height: 32px;
    } 
    
 .mainLeftUL2
 {
    margin-top:10px;
     }   
    .mainLeftUL2 li
{
    width:160px; float:left; height:130px;  margin-right:10px; padding-bottom:40px;
    }
  .mainLeftUL2 li img
     {
         width:160px;  height:130px;
         }
 .mainLeftUL2 li h3
     {
      text-align:center; font: 14px/1.5 "Microsoft YaHei","\5b8b\4f53";
         }
    .mainLeftUL li div
{
   height:140px;
    } 
    .icon_pic
    {
       
        }
   .icon_pic:hover .qr-tips {
	display: block;
}
   .icon_pic_ios:hover .qr-tips_ios {
	display: block;
}
.qr-tips {
	padding: 10px;
	border: 1px solid #d1d2d6;
	position: absolute;
    bottom:0;
	left: 15px;
	background-color: #ffffff;
	display: none;
}

.qr-tips img {
	width: 188px;
	height: 188px;
}
.qr-tips_ios {
	padding: 10px;
	border: 1px solid #d1d2d6;
	position: absolute;
    bottom:0;
	left: 15px;
	background-color: #ffffff;
	display: none;
}
.qr-tips_ios img {
	width: 188px;
	height: 188px;
}
.mainlef_tit{ height:58px; line-height:58px; }
.mainlef_tit h2{ font-size:22px; float:left; font-family:"Microsoft YaHei",SimHei;}
.mainlef_tit .mo{ float:right; padding:0px 20px; font:14px; color:#3db5e6;}
.mainlef_tit .mo span{ font-family:SimSun;}

.mainlef_tit2{ height:58px; line-height:58px; }
.mainlef_tit2 h2{ font-size:22px; float:left; font-family:"Microsoft YaHei",SimHei;}
.mainlef_tit2 .mo{ float:right; padding:0px 20px; font:14px; color:#3db5e6;}
.mainlef_tit2 .mo span{ font-family:SimSun;}

.news_con {
	PADDING-BOTTOM: 5px; MARGIN-TOP: 5px; PADDING-LEFT: 10px; WIDTH: 308px; PADDING-RIGHT: 10px; OVERFLOW: hidden; PADDING-TOP: 0px; font-size:14px;
}
.news_con LI {
	#BORDER-BOTTOM: #d1d2d3 1px dashed; TEXT-ALIGN: left; LINE-HEIGHT: 28px; PADDING-LEFT: 8px; BACKGROUND: url(../imagesnew/tb.gif) no-repeat left center; COLOR: #bf862d; 
}
.news_con LI A {
	COLOR: #922300
}
.news_con SPAN {
	TEXT-ALIGN: left; PADDING-BOTTOM: 0px; PADDING-LEFT: 5px; PADDING-RIGHT: 5px; COLOR: #666666; PADDING-TOP: 0px
}
.news_con h3
{
  height: 48px;
  line-height: 48px;
  font-size: 22px;
  font-family: "Microsoft YaHei",SimHei;
  #border-bottom: 1px solid #EEE;
  padding: 0 16px;
    }
.news_con .im{ float:right; margin-top:10px; margin-bottom:5px;}
.news_con .im img{ float:right; padding:8px 5px 5px 5px;-webkit-transition:all 0.2s ease;
-moz-transition:opacity 0.2s ease;
-ms-transition:opacity 0.2s ease;
-o-transition:opacity 0.2s ease;
transition:opacity 0.2s ease; width:300px;}
/***滚动显示***/
.hg-gamebox {
	 OVERFLOW: hidden; height:410px; margin-top:5px; position:relative;
}
.blk_18 {
	 WIDTH: 860px; ZOOM: 1; FONT-SIZE: 9pt; OVERFLOW: hidden; 
}
.blk_18 .pcont {
	PADDING-LEFT: 6px; WIDTH: 800px; FLOAT: left; OVERFLOW: hidden
}
.blk_18 .ScrCont {
	WIDTH: 32766px; ZOOM: 1; MARGIN-LEFT: -5px
}
.blk_18 #List1_1 {
	FLOAT: left
}
.blk_18 #List2_1 {
	FLOAT: left
}
.blk_18 .LeftBotton {
	MARGIN-TOP: 64px; WIDTH: 26px; BACKGROUND: url(../imagesnew/leftjt.jpg) no-repeat; FLOAT: left; HEIGHT: 274px
}
.blk_18 .RightBotton {
	MARGIN-TOP: 64px; WIDTH: 26px; BACKGROUND: url(../imagesnew/gjtr.jpg) no-repeat; FLOAT: right; HEIGHT: 274px
}

.blk_18 .pl IMG {
	BORDER-BOTTOM-STYLE: none; MARGIN: 6px auto 1px; BORDER-LEFT-STYLE: none; DISPLAY: block; BORDER-TOP-STYLE: none; BORDER-RIGHT-STYLE: none; CURSOR: pointer; width:260px; height:200px; 
}

.blk_18 .pl {
	BORDER-BOTTOM: #fff 1px solid; TEXT-ALIGN: center; BORDER-LEFT: #fff 1px solid; LINE-HEIGHT: 100px; WIDTH: 260px; FLOAT: left; BORDER-TOP: #fff 1px solid; BORDER-RIGHT: #fff 1px solid;
	 font-size:18px;
 font-weight:bold;
 text-align:center;
}
.blk_18 A.pl:hover {
	BORDER-BOTTOM: #dc5800 1px solid; BORDER-LEFT: #dc5800 1px solid; BACKGROUND: #fff; COLOR: #fda20b; BORDER-TOP: #dc5800 1px solid; BORDER-RIGHT: #dc5800 1px solid
}

.CoinTop {
	PADDING-BOTTOM: 5px; MARGIN-TOP: 5px; PADDING-LEFT: 10px; WIDTH: 308px; PADDING-RIGHT: 10px; OVERFLOW: hidden; PADDING-TOP: 0px; font-size:14px;
}
.CoinTop h3
{
  height: 48px;
  line-height: 48px;
  font-size: 22px;
  font-family: "Microsoft YaHei",SimHei;
  #border-bottom: 1px solid #EEE;
  padding: 0 16px;
    }
table {
  display: table;
  border-collapse: separate;
  border-spacing: 2px;
  _border-color: gray;
}
td, th {
  display: table-cell;
  vertical-align: inherit;

}
.table_head {
  background-color: #eaf7ff;
  text-align: center;
  font-weight: bold;
  padding-right: 4px;
  padding-left: 4px;
  padding-bottom:10px;
}

.table_gray {
  color: #922300;
  text-align: center;
  padding-right: 4px;
  padding-left: 4px;
  display: table-cell;
  vertical-align: inherit;  
  font-size:14px;
}
.table_black {
  text-align: center;
  padding-right: 4px;
  padding-left: 4px;
  display: table-cell;
  vertical-align: inherit;  
  font-size:14px;
}
.table_red 
{
    color:Red;
  text-align: center;
  padding-right: 4px;
  padding-left: 4px;
  display: table-cell;
  vertical-align: inherit;  
  font-size:14px;
  font-weight:bold;
}

</style>
</head>
<body>
    <div id="min_max_width">
        <div class="jj_nav_hot" id="jj_nav_hot">
            <div class="jj_nav_info">
                <div class="min_max_adap">
                    <div class="logo">
                        <a href="#">
                            <img src="../hn_img/www/hn/hn_logo.png" /></a></div>
                    <ul class="nav" style="width: 600px;">
                        <li class="hov"><a href="/index.aspx"><span class="s1"></span>首 页</a></li>
                        <li><a href="/Down.aspx" title="下载中心"><span class="s2"></span>下载中心</a></li>
                        <li><a href="/Manage/Pay/Yeepay2/default.aspx" title="游戏充值"><span class="s3"></span>
                            游戏充值</a></li>
                        <li><a href="/PrizeList.aspx"><span class="s4"></span>积分商城</a></li>
                    </ul>
                    <div class="dow">
                        <div class="h_tit">
                            <h1>
                                舞乐久为用户提供舒适的在线棋牌竞技体验</h1>
                            <span>三方互通，让玩家随时随地感受棋牌的乐趣</span>
                        </div>
                        <a class="dow_but" href="<%=fullUrl %>">
                        
                        </a><a class="ph_dow ph_dow1" style="" target="_blank" id="but_wm2_and" href="<%=adrUrl %>">
                            <span></span>
                            <h2>安卓手机</h2>
                        </a><a class="ph_dow ph_dow2" style="" target="_blank" id="but_wm2_iph" href="<%=appUrl %>">
                            <span></span>
                            <h2> 苹果手机</h2>
                        </a>
                        <a class="ph_dow ph_dow3" style="" target="_blank" id="but_wm2_ipad" href="<%=appUrl %>">
                            <span></span> 
                            <h2>iPad</h2>
                        </a>
                        <span class="wm2" id="wm2_and">
                            <img alt="安卓版" title="安卓版" class="im" src="<%=adrImg %>" />
                            <span>安卓手机下载</span> </span><span class="wm2" id="wm2_iph" style="left: -50px;">
                                <img alt="iPhone版" title="iPhone版" class="im" src="<%=appImg %>" />
                                <span>苹果手机下载</span> </span><span class="wm2" id="wm2_ipad" style="left: 70px;">
                                    <img class="im" src="<%=appImg %>" />
                                    <span>iPad 下载</span> </span>
                    </div>
                    <ul class="hot_img_nav" id="hot_img_nav">
                    </ul>
                </div>
            </div>
            <div class="jj_hot_img" id="jj_hot_img">
                <div class="hot_img" style="opacity: 1;">
                    <div class="hot_img_len hot_img_len1">
                        <div class="min_max_adap">
                            <a class="aa" href="/PrizeList.aspx" target="_blank"></a>
                        </div>
                    </div>
                </div>
                <div class="hot_img">
                    <div class="hot_img_len hot_img_len2">
                        <div class="min_max_adap">
                            <a class="aa" href="/Down.aspx" target="_blank"></a>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div id="mainFrame" style="margin: 0px auto; display: block; width: 1183px; background: #f7f7f7;">
            <div style="float: left; width: 870px;">
                <div id="mainLeft" class="mainLeft" style="float: left; width: 870px; margin-bottom: 20px;">
                    <div style="">
                        <div class="mainlef_tit">
                            <h2 title="游戏">
                                <a href="/Down.aspx" target="_blank">
                                    <%= SiteConfig.GetParaValue("Title")%>手游</a></h2>
                            <a class="mo" href="/Down.aspx" title="更多游戏" target="_blank">更多下载 <span>&gt;&gt;</span></a>
                        </div>
                        <ul class="mainLeftUL">
                            <!--绑定手机游戏-->
                            <asp:Repeater ID="rptPhone" runat="server">
                                <ItemTemplate>
                                    <li>
                                        <%--                                     <div style="float: left; width: 55%; height: 100%;">
                                            <img src="<%#Eval("images") %>" style="width: 210px; height: 140px;" />
                                        </div>
                                        <div style="float: right; height: 100%; width: 45%;">
                                            <div style="width: 100%; height: 60%;">
                                                <h3>
                                                    <%#Eval("Gname")%></h3>
                                            </div>
                                            <div style="width: 100%; height: 40%;">
                                                <a class="icon_pic" href="<%#Eval("AndroidName") %>" target="_blank">
                                                    <img src="/image/icon1.png" />
                                                    <div class="qr-tips">
                                                        <img style="width: 138px; height: 138px;" src="<%#Eval("AndroidQrcode") %>" title="安卓下载"
                                                            alt="安卓下载">
                                                    </div>
                                                </a><a class="icon_pic_ios" href="<%#Eval("appleName") %>" target="_blank">
                                                    <img src="/image/icon2.png" />
                                                    <div class="qr-tips_ios">
                                                        <img style="width: 138px; height: 138px;" src="<%#Eval("AppleQrcode") %>" title="苹果下载"
                                                            alt="苹果下载">
                                                    </div>
                                                </a>
                                            </div>
                                        </div>--%>
                                        <div id="<%#Eval("id","az{0}") %>" style="display: none; position: absolute; margin: 0px auto;
                                            background: #000; background: rgba(0,0,0,0.70); padding: 10px; z-index: 9999;">
                                            <img alt="安卓版" title="安卓版" src="<%#Eval("AndroidQrcode") %>" style="width: 100px;
                                                height: 100px; margin: 0 auto; text-align: center; color: #FFF; padding: 5px;
                                                background: #FFF;" />
                                            <p style="text-align: center; color: #FFF;">
                                                安卓手机下载</p>
                                        </div>
                                        <div id="<%#Eval("id","os{0}") %>" style="display: none; position: absolute; margin: 0px auto;
                                            background: #000; background: rgba(0,0,0,0.70); padding: 10px; z-index: 9999;">
                                            <img alt="苹果版" title="苹果版" src="<%#Eval("AppleQrcode") %>" style="width: 100px; height: 100px;
                                                margin: 0 auto; text-align: center; color: #FFF; padding: 5px; background: #FFF;" />
                                            <p style="text-align: center; color: #FFF;">
                                                苹果手机下载</p>
                                        </div>
                                        <img src="<%#Eval("BigImage") %>" usemap="<%#Eval("id","#ump{0}") %>" />
                                        <map name="<%#Eval("id","ump{0}") %>">
                                            <area shape="rect" coords="278,90,322,136" href="<%#Eval("AndroidName") %>" target="_blank"
                                                onmouseover="document.getElementById('<%#Eval("id","az{0}") %>').style.display='';"
                                                onmouseout="document.getElementById('<%#Eval("id","az{0}") %>').style.display='none';"
                                                alt="安卓下载" />
                                            <area shape="rect" coords="350,90,396,136" href="<%#Eval("appleName") %>" target="_blank"
                                                alt="苹果下载" onmouseover="document.getElementById('<%#Eval("id","os{0}") %>').style.display='';"
                                                onmouseout="document.getElementById('<%#Eval("id","os{0}") %>').style.display='none';" />
                                        </map>
                                    </li>
                                </ItemTemplate>
                            </asp:Repeater>
                        </ul>
                    </div>
                </div>
                <div style="float: left; width: 870px; margin-bottom: 20px;">
                    <div class="mainlef_tit2">
                        <h2 title="游戏">
                            <a href="/Down.aspx" target="_blank">
                                <%= SiteConfig.GetParaValue("Title")%>棋牌</a></h2>
                        <a class="mo" href="/Down.aspx" title="更多游戏" target="_blank">更多下载 <span>&gt;&gt;</span></a>
                    </div>
                    <ul class="mainLeftUL2">
                        <asp:Repeater ID="rptPC" runat="server">
                            <ItemTemplate>
                                <li><a href="<%#Eval("Down_address") %>" target="_blank"><span>
                                    <img title="<%#Eval("Game_Name") %>" alt="<%#Eval("Game_Name") %>" src="<%#Eval("Image_URL") %>" /></span>
                                    <h3 style="text-align: center;">
                                        <%#Eval("Game_Name")%></h3>
                                </a></li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ul>
                </div>
                <div style="float: left; width: 870px;">
                    <div class="jj_ind_tit">
                        <h2 title="奖品中心">
                            <a href="/PrizeList.aspx" target="_blank">奖品中心</a></h2>
                        <a class="mo" href="/PrizeList.aspx" title="奖品中心" target="_blank">查看更多 <span>&gt;&gt;</span></a>
                    </div>
                    <div class="hg-gamebox jj_game_icon web_game_icon">
                        <div class="blk_18">
                            <a class="LeftBotton" onmousedown="ISL_GoUp_1()" onmouseup="ISL_StopUp_1()" onmouseout="ISL_StopUp_1()"
                                href="javascript:void(0);" target="_self"></a>
                            <div class="pcont" id="ISL_Cont_1">
                                <div class="ScrCont">
                                    <div id="List1_1">
                                        <asp:Repeater ID="rptPrize" runat="server">
                                            <ItemTemplate>
                                                <a class="pl" href="/PrizeDetail.aspx?id=<%#Eval("Award_ID") %>" title="<%#Eval("Award_Name") %>">
                                                    <img src="<%#Eval("Award_MainPic") %>" title="<%#Eval("Award_Name") %>" alt="<%#Eval("Award_Name") %>"><%#Eval("Award_Name") %></a>
                                            </ItemTemplate>
                                        </asp:Repeater>
                                    </div>
                                </div>
                            </div>
                            <a class="RightBotton" onmousedown="ISL_GoDown_1()" onmouseup="ISL_StopDown_1()"
                                onmouseout="ISL_StopDown_1()" href="javascript:void(0);" target="_self"></a>
                        </div>
                    </div>
                </div>
                <div style="float: left; height: 50px; width: 870px; display: none;" id="emptyDiv">
                </div>
            </div>
            <div id="mainRight" style="float: right; width: 308px;">
                <div style="top: 0; padding: 0;" id="Loging">
                    <div class="lg-top hide_txt">
                        欢乐一刻，必有所得！</div>
                    <div class="lg-mid">
                        <div class="abs loading" style="display: none;">
                            <img src="../hnlogin/www/images/load.gif" alt="加载中">
                        </div>
                        <div class="login-q" id="signin">
                            <form onsubmit="javascript:return false;" method="post">
                            <div class="lg-tip">
                                <p class="ico-login">
                                </p>
                            </div>
                            <div class="rel ico-login lg-inptu-box">
                                <input name="" type="text" class="abs lg-inptu lg-name" placeholder="账号">
                                <input name="" type="password" class="abs lg-inptu lg-pwd" placeholder="密码">
                            </div>
                            <div class="rel mgt10 lg-rzm hide">
                                <div class="ico-login rzm-box">
                                    <input name="" type="text" class="abs lg-inptu lg-yzm" placeholder="验证码">
                                </div>
                                <img class="abs rzm-img" src="#" alt="验证码" title="点击换一张" />
                            </div>
                            <div class="rel lg-btn">
                                <p id="lg-slides" class="abs an2 lg-slides on">
                                    <span class="abs an2 lg-on">ON</span><a class="abs an2 lg-slides-btn"></a><span class="abs an2 lg-off">OFF</span></p>
                                <p class="abs lg-rem-name">
                                    记住用户名</p>
                                <a class="abs forget-pwd" href="/Manage/GetPass.aspx" target="_blank" title="忘记密码?">
                                    忘记密码？</a> <a class="abs ico-login hide_txt lg-login" id="btnSubmit" title="立即登录">立即登录</a>
                            </div>
                            </form>
                            <div class="rel wx-res-box">
                                <div class="abs ico-login wx-box">
                                    关注微信公众号有惊喜</div>
                                <div class="abs res-box">
                                    <p class="abs res-tip">
                                        还没有游戏账号？</p>
                                    <a class="abs ico-login hide_txt res-btn registet-link" href="/register.aspx" title="免费注册">
                                        免费注册</a><%-- <a class="abs ico-login bind-phpone" style="display: inherit;" href="#"
                                            target="_blank" title="天天签到">天天签到</a>--%>
                                </div>
                            </div>
                        </div>
                        <div class="login-h hide" id="logon" style="margin-left: 7px;">
                            <div class="rel user-info">
                                <div class="abs user-photo">
                                    <img class="abs" src="/images/UserLogos/Logo_1.png"><a class="abs" href="/Manage/index.aspx"
                                        target="_blank"></a></div>
                                <div class="abs user-mesg" style="display: none;">
                                    <a href="http://my.65.com/message.html" target="_blank" title="未读信息"></a>
                                </div>
                                <div class="abs user-name-box">
                                    <a class="user-name" href="/Manage/index.aspx" target="_self"></a><a class="abs user-exit"
                                        href="/Public/Logout.aspx">[退出]</a></div>
                                <div style="display: block; width: 164px; height: 32px; left: 120px; top: 53px; position: absolute;">
                                    <p>
                                        银行存款：<span id="sp_bank"></span>&nbsp;<%=UiCommon.StringConfig.MoneyName%></p>
                                    <p>
                                        钱包：<span id="sp_wallet"></span>&nbsp;<%=UiCommon.StringConfig.MoneyName%></p>
                                </div>
                            </div>
                            <div class="user-base">
                                <dl class="user-base-dl">
                                    <dd class="user-1 hide" style="display: none;">
                                        <p class="user-b1">
                                        </p>
                                        <p class="user-b2">
                                        </p>
                                    </dd>
                                    <dd class="user-2 hide" style="display: none;">
                                        <a class="an05" href="http://my.65.com/integral.html" target="_blank" title="积分余额">
                                            <p class="user-b1">
                                            </p>
                                            <p class="user-b2">
                                                积分余额</p>
                                        </a>
                                    </dd>
                                    <dd class="user-2" style="display: none;">
                                        <a class="an05" href="http://my.65.com/coin_pay.html" target="_blank" title="平台币余额">
                                            <p class="user-b1">
                                            </p>
                                            <p class="user-b2">
                                                平台币余额</p>
                                        </a>
                                    </dd>
                                    <dd class="rel user-bdd ">
                                        <em class="bq-11 an05"></em><a class="abs an05 user-center" href="/Manage/index.aspx"
                                            target="_self" title="用户中心">用户中心</a><i class="bq-1"></i></dd>
                                    <dd class="rel user-bdd" style="">
                                        <em class="bq-22 an05"></em><a class="abs an05 user-sign" href="javascript:;" id="btnsign"
                                            title="每日签到">每日签到</a><i class="bq-2"></i></dd>
                                    <dd class="rel user-bdd ">
                                        <em class="bq-33 an05"></em><a class="abs an05 user-pay" href="/Manage/Pay/Yeepay2/default.aspx"
                                            target="_self" title="我要充值">我要充值</a><i class="bq-3"></i></dd>
                                </dl>
                                <input runat="server" id="txt_signid" value="0" type="hidden" />
                            </div>
                            <div class="palyed-game hide">
                                <p class="played rel">
                                    我玩过的游戏：<a class="abs ico-login bind-phpone" href="bindphone/bindphone.html" target="_blank"
                                        title="绑定手机领礼包">绑定手机领礼包</a></p>
                                <dl class="played-game-list">
                                </dl>
                            </div>
                        </div>
                    </div>
                    <div class="lg-bottom">
                    </div>
                </div>
                <div class="news_con">
                    <h3>
                        <a href="/NewList.aspx" target="_blank">新闻公告</a></h3>
                    <ul>
                        <asp:Repeater ID="rpNewsList" runat="server">
                            <ItemTemplate>
                                <li>
                                    <img src="/image/circle.png" />&nbsp;<a href='/NewsPage.aspx?id=<%#Eval("News_ID") %>'><%# Eval("Title") %></a></li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ul>
                    <a class="im" href="/Down.aspx" target="_blank" style="display: none;">
                        <img src='/image/ads.jpg' alt="游戏大厅" title="游戏大厅"></a>
                </div>
                <div class="CoinTop" style="display: ;">
                    <h3>
                        <a>财富排行</a></h3>
                    <table width="100%" border="0" cellpadding="0" cellspacing="1">
                        <tr>
                            <td class="table_head">
                                排名
                            </td>
                            <td class="table_head">
                                用户名
                            </td>
                            <td class="table_head">
                                金币
                            </td>
                        </tr>
                        <asp:Repeater ID="rptCoin" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <%#Convert.ToInt32(Eval("line"))<=3 ? "<td class='table_red'>"+Eval("line")+"</td>":"<td class='table_black'>"+Eval("line")+" </td>" %>
                                    <td class="table_gray">
                                        <%#Eval("NickName")%>
                                    </td>
                                    <td class="table_black">
                                        <%#Eval("Coin") %>
                                    </td>
                                </tr>
                                <tr style="height: 18px;">
                                    <td>
                                    </td>
                                    <td>
                                    </td>
                                    <td>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                <div class="box5" style="position: relative; margin-bottom: 20px;">
                    <div class="lmwrap">
                        <h2 class="fl z-lm">
                            快速通道</h2>
                    </div>
                    <div class="box5-con">
                        <div class="box5-top">
                            <ul class="abs ullihover cooperation">
                                <li class="rel border-left cop-p1">
                                    <p class="abs an2 border-left">
                                    </p>
                                    <a class="cop-span1 registet-link" href="/Register.aspx" title="免费注册"><i class="cop-p">
                                    </i><span class="cop-span an2">免费注册</span> <em></em></a></li>
                                <li class="rel cop-p2">
                                    <p class="abs an2">
                                    </p>
                                    <a class="cop-span2" href="/Manage/GetPass.aspx" target="_blank" title="找回密码"><i
                                        class="cop-p"></i><span class="cop-span an2">找回密码</span> <em></em></a></li>
                                <li class="rel border-right cop-p3">
                                    <p class="abs an2 border-right">
                                    </p>
                                    <a class="logstatus cop-span3" href="/Manage/index.aspx" data-href="/Manage/index.aspx"
                                        target="_blank" title="修改密码"><i class="cop-p"></i><span class="cop-span an2">修改密码</span>
                                        <em></em></a></li>
                                <li class="rel cop-p4">
                                    <p class="abs an2">
                                    </p>
                                    <a class="logstatus cop-span4" href="/Manage/index.aspx" data-href="/Manage/index.aspx"
                                        target="_blank" title="修改资料"><i class="cop-p"></i><span class="cop-span an2">修改资料</span>
                                        <em></em></a></li>
                             <%--   <li class="rel cop-p5">
                                    <p class="abs an2">
                                    </p>
                                    <a class="cop-span5" href="/Service.aspx" target="_blank" title="问题提交"><i class="cop-p">
                                    </i><span class="cop-span an2">问题提交</span> <em></em></a></li>--%>
                                <li class="rel cop-p6">
                                    <p class="abs an2">
                                    </p>
                                    <a class="cop-span6" href="/Manage/index.aspx" target="_blank" title="记录查询"><i class="cop-p">
                                    </i><span class="cop-span an2">记录查询</span> <em></em></a></li>
                            </ul>
                        </div>
                        <div class="box5-fot">
                            <ul class="rel ullihover contact">
                                <li class="abs contact-online">
                                    <p class="abs an2">
                                    </p>
                                    <a href="/Service.aspx" target="_blank" title="在线客服"><i class="abs"></i><span>在线客服</span>
                                        <em class="cont-em1"></em></a></li>
                                <li class="abs go-vip">
                                    <p class="abs an2">
                                    </p>
                                    <a class="logstatus" href="http://wpa.qq.com/msgrd?v=3&amp;uin=<%= SiteConfig.GetParaValue("CustomServiceqq1")%>&amp;site=qq&amp;menu=yes"
                                        data-href="http://wpa.qq.com/msgrd?v=3&amp;uin=<%= SiteConfig.GetParaValue("CustomServiceqq1")%>&amp;site=qq&amp;menu=yes"
                                        target="_blank" title="QQ在线"><i class="abs"></i><span>QQ在线</span> <em class="cont-em2">
                                        </em></a></li>
                                <li class="abs contact-tell"><i class="abs"></i><span>
                                    <%= SiteConfig.GetParaValue("客服电话")%></span> </li>
                            </ul>
                        </div>
                    </div>
                </div>
                <div style="clear: both">
                </div>
            </div>
        </div>
        <div style="clear: both">
        </div>
    </div>
    <uc1:NewFooter runat="server" ID="new1" />
    <script type="text/javascript" src="/js/jquery-1.7.2.min.js"></script>
    <script type="text/javascript" src="/js/scroll.js"></script>
    <script type="text/javascript">

        //首页滚动js
        var Speed_1 = 10; //速度(毫秒)
        var Space_1 = 20; //每次移动(px)
        var PageWidth_1 = 92 * 4; //翻页宽度
        var interval_1 = 5000; //翻页间隔时间
        var fill_1 = 0; //整体移位
        var MoveLock_1 = false;
        var MoveTimeObj_1;
        var MoveWay_1 = "right";
        var Comp_1 = 0;
        var AutoPlayObj_1 = null;
        function GetObj(objName) { if (document.getElementById) { return eval('document.getElementById("' + objName + '")') } else { return eval('document.all.' + objName) } }
        function AutoPlay_1() { clearInterval(AutoPlayObj_1); AutoPlayObj_1 = setInterval('ISL_GoDown_1();ISL_StopDown_1();', interval_1) }
        function ISL_GoUp_1() { if (MoveLock_1) return; clearInterval(AutoPlayObj_1); MoveLock_1 = true; MoveWay_1 = "left"; MoveTimeObj_1 = setInterval('ISL_ScrUp_1();', Speed_1); }
        function ISL_StopUp_1() {
            if (MoveWay_1 == "right") { return }; clearInterval(MoveTimeObj_1); if ((GetObj('ISL_Cont_1').scrollLeft - fill_1) % PageWidth_1 != 0) { Comp_1 = fill_1 - (GetObj('ISL_Cont_1').scrollLeft % PageWidth_1); CompScr_1() } else { MoveLock_1 = false }
            AutoPlay_1()
        }
        function ISL_ScrUp_1() {
            if (GetObj('ISL_Cont_1').scrollLeft <= 0) { GetObj('ISL_Cont_1').scrollLeft = GetObj('ISL_Cont_1').scrollLeft + GetObj('List1_1').offsetWidth }
            GetObj('ISL_Cont_1').scrollLeft -= Space_1
        }
        function ISL_GoDown_1() { clearInterval(MoveTimeObj_1); if (MoveLock_1) return; clearInterval(AutoPlayObj_1); MoveLock_1 = true; MoveWay_1 = "right"; ISL_ScrDown_1(); MoveTimeObj_1 = setInterval('ISL_ScrDown_1()', Speed_1) }
        function ISL_StopDown_1() {
            if (MoveWay_1 == "left") { return }; clearInterval(MoveTimeObj_1); if (GetObj('ISL_Cont_1').scrollLeft % PageWidth_1 - (fill_1 >= 0 ? fill_1 : fill_1 + 1) != 0) { Comp_1 = PageWidth_1 - GetObj('ISL_Cont_1').scrollLeft % PageWidth_1 + fill_1; CompScr_1() } else { MoveLock_1 = false }
            AutoPlay_1()
        }
        function ISL_ScrDown_1() {
            if (GetObj('ISL_Cont_1').scrollLeft >= GetObj('List1_1').scrollWidth) { GetObj('ISL_Cont_1').scrollLeft = GetObj('ISL_Cont_1').scrollLeft - GetObj('List1_1').scrollWidth }
            GetObj('ISL_Cont_1').scrollLeft += Space_1
        }
        function CompScr_1() {
            if (Comp_1 == 0) { MoveLock_1 = false; return }
            var num, TempSpeed = Speed_1, TempSpace = Space_1; if (Math.abs(Comp_1) < PageWidth_1 / 2) { TempSpace = Math.round(Math.abs(Comp_1 / Space_1)); if (TempSpace < 1) { TempSpace = 1 } }
            if (Comp_1 < 0) {
                if (Comp_1 < -TempSpace) { Comp_1 += TempSpace; num = TempSpace } else { num = -Comp_1; Comp_1 = 0 }
                GetObj('ISL_Cont_1').scrollLeft -= num; setTimeout('CompScr_1()', TempSpeed)
            } else {
                if (Comp_1 > TempSpace) { Comp_1 -= TempSpace; num = TempSpace } else { num = Comp_1; Comp_1 = 0 }
                GetObj('ISL_Cont_1').scrollLeft += num; setTimeout('CompScr_1()', TempSpeed)
            }
        }
        function picrun_ini() {
            GetObj("List2_1").innerHTML = GetObj("List1_1").innerHTML;
            GetObj('ISL_Cont_1').scrollLeft = fill_1 >= 0 ? fill_1 : GetObj('List1_1').scrollWidth - Math.abs(fill_1);
            GetObj("ISL_Cont_1").onmouseover = function () { clearInterval(AutoPlayObj_1) }
            GetObj("ISL_Cont_1").onmouseout = function () { AutoPlay_1() }
            AutoPlay_1();
        }
    </script>
    <script type="text/javascript">
        var www_jj_cn_index = {
            gat_id: function (id) {
                return document.getElementById(id);
            },
            but_wm2: function (id, wm) {
                id.onmouseover = function () {
                    clearTimeout(id.timer);
                    clearTimeout(id.timer2);
                    id.timer2 = setTimeout(function () {
                        wm.style.display = "block";
                    }, 250);
                }
                id.onmouseout = function () {
                    clearTimeout(id.timer);
                    clearTimeout(id.timer2);
                    id.timer = setTimeout(function () {
                        wm.style.display = "none";
                    }, 50);
                }
            },
            but_wm2_fn: function () {
                this.but_wm2(this.gat_id("but_wm2_and"), this.gat_id("wm2_and"));
                this.but_wm2(this.gat_id("but_wm2_iph"), this.gat_id("wm2_iph"));
                this.but_wm2(this.gat_id("but_wm2_ipad"), this.gat_id("wm2_ipad"));
            },
            setStyle3: function (obj, name, value) {
                var aCss3 = ['transform', 'transition', 'borderRadius', 'boxShadow', 'textShadow'];
                if (aCss3.indexOf(name) != -1) {
                    obj.style['Webkit' + name.charAt(0).toUpperCase() + name.substring(1)] = value;
                    obj.style['Moz' + name.charAt(0).toUpperCase() + name.substring(1)] = value;
                    obj.style['ms' + name.charAt(0).toUpperCase() + name.substring(1)] = value;
                    obj.style['O' + name.charAt(0).toUpperCase() + name.substring(1)] = value;
                    obj.style[name] = value;
                } else {
                    obj.style[name] = value;
                }
            },
            is_max_width: true,
            is_min_width: true,
            min_max_width: function () {
                if (document.getElementById('min_max_width')) {
                    var iWinWidth = document.documentElement.clientWidth || document.body.clientWidth;
                    var iWinHeight = document.documentElement.clientHeight || document.body.clientHeight;
                    var oBorWidth = document.getElementById('min_max_width');
                    if ((iWinWidth > 1200 || iWinHeight < 760) && this.is_max_width) {
                        oBorWidth.className = 'max_1200';
                        this.is_min_width = true;
                        this.is_max_width = false;
                    }
                    if ((iWinWidth <= 1201 || iWinHeight <= 761) && this.is_min_width) {
                        oBorWidth.className = 'min_980';
                        this.is_max_width = true;
                        this.is_min_width = false;
                    }
                }
            }
        }
        function www_jj_cn_index_lenbo() {
            this.obj = null;
            this.timerr = null;
            this.now = 0;
            this.index = 1;
        }
        www_jj_cn_index_lenbo.prototype = {
            init: function (nav, bjimg, jjnavhot) {
                var _this = this;
                this.outImgUl = document.getElementById(nav);
                this.imgChildren = this.outImgUl.children;
                this.obj = document.getElementById(bjimg);
                this.jjnavhot = document.getElementById(jjnavhot);
                this.aImg = this.obj.children;
                this.len = this.aImg.length;
                for (var i = 0; i < this.len; i++) {
                    var oLi = document.createElement('li');
                    oLi.index = i;
                    oLi.onclick = function () {
                        _this.now = this.index;
                        _this.tab_but();
                    }
                    this.outImgUl.appendChild(oLi);
                }
                this.imgChildren[this.now].className = "hov";
                this.aImg[this.now].style.zIndex = this.index;
                this.aImg[this.now].style.opacity = '1';
                this.slider();
            },
            slider: function () {
                var _this = this;
                this.timerr = setInterval(function () {
                    _this.now++;
                    _this.tab();
                }, 5000);
            },
            tab: function () {
                ++this.index
                if (this.now == -1) {
                    this.now = this.len - 1;
                };
                if (this.now == this.len) {
                    this.now = 0;
                };
                this.tab_but();
            },
            tab_but: function () {
                for (var i = 0; i < this.len; i++) {
                    this.imgChildren[i].className = ""
                    this.aImg[i].style.opacity = '0';
                    this.aImg[i].style.zIndex = '0';
                }
                this.aImg[this.now].style.zIndex = this.index;
                this.aImg[this.now].style.opacity = '1';
                this.imgChildren[this.now].className = "hov"
            }
        }
        var index_lenbo = new www_jj_cn_index_lenbo();
        index_lenbo.init("hot_img_nav", "jj_hot_img", "jj_nav_hot")
        www_jj_cn_index.but_wm2_fn();
        www_jj_cn_index.min_max_width();
        window.onresize = function () {
            www_jj_cn_index.min_max_width();
        };
        $(document).ready()
        {
            getLoginInfo();
            $("#btnSubmit").click(btnSubmit_Click);
            $("#btnsign").click(function () {
                if ($("#txt_signid").val() == "1") {
                    alert("今天已签到!");
                    return;
                }
                $("#btnsign").attr("value", "签到中....")
                $.getJSON("/public/SignIN.ashx?rd=" + Math.random(), { type: 1 }, function (data) {

                    if (data != null) {
                        $("#btnsign").attr("value", "已签到")
                        $("#txt_signid").val("1");
                        if (data.Rs == 1) {
                            //$("#span_score").html(returnFloat(data.BankMoney));
                            //$("#span_daycount").html("已连续签到" + data.CountDay + "天");
                        }
                        alert(data.Msg);
                    }
                    else {
                        alert("系统繁忙，请重试！");

                    }
                });
            });
        }
        function btnSubmit_Click() {
            var uname = $('.lg-name').val(); var upwd = $('.lg-pwd').val(); var ucode = $('.lg-yzm').val();
            if ($.trim(uname) == '') { $(".lg-tip p").html('账号不能为空!'); $("input.lg-name").focus(); return false; }
            else if ($.trim(upwd) == '') { $(".lg-tip p").html('密码不能为空!'); $("input.lg-pwd").focus(); return false; }

            $.ajax({ url: '/Public/Register.ashx?rand' + Math.random(), type: "GET", data: { action: 'login', uname: uname, upwd: upwd }, dataType: "json",

                success: function (d) {
                    if (d.code == 1) {
                        //$('.login-q').hide();
                        //$('.login-h').css('display', 'block');
                        $("#signin").hide();
                        $("#logon").show();
                        location.href = location.href;
                    }
                    else { $(".lg-tip p").html(d.msg); return false; }
                },
                error: function (textStatus, errorThrown) { $(".lg-tip p").html("系统繁忙，请稍后再试！"); alert("系统ajax交互错误: " + textStatus); }
            });
        }
        function getLoginInfo() {
            $.ajax({ url: '/Public/Register.ashx?rand=' + Math.random(), type: "GET", dataType: "json",
                data: { action: 'loginstatus' }, success: function (res) {
                    if (res.code == 1) {
                        $("#emptyDiv").hide();
                        $("#signin").hide();
                        $("#logon").show();
                        $('.username,.user-name').html(res.uname);
                        $('.user-mesg a').html(res.msg);
                        $('.user-mes span').html('(' + res.msg + ')');
                        $(".lg-bottom").eq(0).css('background', 'none');
                        //$(".lg-mid").eq(0).css('height', '195');
                        $("#sp_bank").html(res.bankmoney);
                        $("#sp_wallet").html(res.walletmoney);
                        // $('.login-q').css('display', 'none');
                        //$('.user-photo img').attr('src', '/images/UserLogos/' + res.uid + '.png');
                        //$("#Loging").height($("#Loging").height() - 190);
                        $("#usr_loding").hide();
                    }
                    else {
                        $("#emptyDiv").show();
                        $("#signin").show();
                        $("#logon").hide();
                        $("#usr_loding").show();
                    }
                }, error: function (textStatus, errorThrown) { $(".loading").show(); $(".login-q,.login-h").hide(); }
            });
        }
    </script>
</body>
</html>
