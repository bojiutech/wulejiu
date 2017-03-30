<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="HSPay.aspx.cs" Inherits="HN.Web.Manage.Pay.HS.HSPay" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="/Public/RightTop.ascx" TagName="RightTop" TagPrefix="uc1" %>
<%@ Register Src="/Public/LeftTop.ascx" TagName="LeftTop" TagPrefix="uc2" %>
<%@ Register Src="/Public/Bottom.ascx" TagName="Bottom" TagPrefix="uc3" %>
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
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <link href="/css/public.css" rel="stylesheet" type="text/css" />
    <link href="/css/global.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="/css/game.css" />
    <link href="/css/news.css" rel="stylesheet" type="text/css" />
    <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
    <script src="/JS/MSClass.js" type="text/javascript"></script>
    <script type="text/javascript">
        $().ready(function () {
            $("#pay").submit();
        });


        //图片按比例缩放
        var flag = false;
        function DrawImage(ImgD, iwidth, iheight) {
            //参数(图片,允许的宽度,允许的高度)
            var image = new Image();
            image.src = ImgD.src;
            if (image.width > 0 && image.height > 0) {
                flag = true;
                if (image.width / image.height >= iwidth / iheight) {
                    if (image.width > iwidth) {
                        ImgD.width = iwidth;
                        ImgD.height = (image.height * iwidth) / image.width;
                    } else {
                        ImgD.width = image.width;
                        ImgD.height = image.height;
                    }
                    ImgD.alt = image.width + "×" + image.height;
                }
                else {
                    if (image.height > iheight) {
                        ImgD.height = iheight;
                        ImgD.width = (image.width * iheight) / image.height;
                    } else {
                        ImgD.width = image.width;
                        ImgD.height = image.height;
                    }
                    ImgD.alt = image.width + "×" + image.height;
                }
            }
        } 
    </script>



    <script type="text/javascript" src="/js/Common.js"></script>
</head>
<body>
    <form runat="server" id="pay" action="http://go.xibaopay.com/ecpss.action"  method="post" target="_blank">
    <!--头部开始-->
    <div class="main">
        <div class="top">
            <div class="left">
                <img src="/images/logo.png" height="78" /></div>
            <div class="right mtop13 lan">
                <uc1:RightTop ID="RightTop1" runat="server" />
                <div class="clear">
                </div>
            </div>
        </div>
        <div class="nav">
            <div class="navLeft">
            </div>
            <div class="navCenter">
                <ul>
                    <li class=""><a href="/Index.aspx" hidefocus="true">首页</a></li>
                    <li class=""><a href="/NewsListP.aspx" hidefocus="true">资讯中心</a></li>
                    <li class=""><a href="/Manage/index.aspx" hidefocus="true">会员中心</a></li>
                    <li class="current"><a href="/Manage/Pay/Yeepay2/Default.aspx" hidefocus="true">充值中心</a></li>
                    <li class=""><a href="/Props.aspx" hidefocus="true">游戏商场</a></li>
                    <li class=""><a href="/Service/Customer.aspx" hidefocus="true">客服中心</a></li>
                    <li class=""><a href="/jzjh/gcjs.html" hidefocus="true">家长监护</a></li>
                </ul>
            </div>
            <div class="navRight">
            </div>
        </div>
    </div>
    <div class="clear">
    </div>
    <!--头部结束-->
    <!--[if IE 6]> 
<script>
function correctPNG() 
{
for(var i=0; i<document.images.length; i++)
{
var img = document.images[i];
var imgName = img.src.toUpperCase();
if (imgName.substring(imgName.length-3, imgName.length) == "PNG")
{
var imgID = (img.id) ? "id='" + img.id + "' " : "";
var imgClass = (img.className) ? "class='" + img.className + "' " : "";
var imgTitle = (img.title) ? "title='" + img.title + "' " : "title='" + img.alt + "' ";
var imgStyle = "display:inline-block;" + img.style.cssText;
if (img.align == "left") imgStyle = "float:left;" + imgStyle;
if (img.align == "right") imgStyle = "float:right;" + imgStyle;
if (img.parentElement.href) imgStyle = "cursor:hand;" + imgStyle;
var strNewHTML = "<span "+ imgID + imgClass + imgTitle + "style=\"" + "width:" + img.width + "px; height:" + img.height + "px;" + imgStyle + ";" 
+ "filter:progid:DXImageTransform.Microsoft.AlphaImageLoader" + "(src='" + img.src + "', sizingMethod='scale');\"></span>";
img.outerHTML = strNewHTML;
i = i-1;
}
}
}
window.attachEvent("onload", correctPNG);
</script>
<![endif]-->
    ​
    <!--页面主体开始-->
    <div class="main mtop10">
        <!--左边部分开始-->
        <div class="mainLeft1">
            <div class="LeftSide">
                <!--按钮部分开始-->
                <uc2:LeftTop ID="LeftTop1" runat="server" />
                <!--按钮部分结束-->
                <div class="clear">
                </div>
            </div>
            <div class="clear">
            </div>
        </div>
        <!--左边部分结束-->
        <!--右边部分开始-->
        <div class="mainRight1">
        <div class="center">
        <div class="step1"></div>
       

    	<table align="center" >
    
    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="MerNo"  id="MerNo" value="8888888"></td>
    </tr>
    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="BillNo"  id="BillNo" value="12333"></td>
    </tr>
    <tr>
      <td></td>
      <td>
      <input  runat="server"  type="hidden"   name="defaultBankNumber" id="defaultBankNumber"   value="ICBC"/>
      <input  runat="server"  type="hidden"   name="Amount"  id="Amount"  value="0.01"></td>
    </tr>

    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="ReturnURL" id="ReturnURL" value="http://localhost/PayResult.aspx" ></td>
    </tr>
    
	 <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="AdviceURL"  id="AdviceURL" value="http://localhost/PayResult2.aspx" ></td>
    </tr>

    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="SignInfo" id="SignInfo" value="111"></td>
    </tr>
    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="Remark" id="Remark" value="1111"></td>
    </tr>
	 <tr>
      <td></td>
      <td></td>
    </tr>
	 <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="orderTime" id="orderTime"  value="201410102123"></td>
    </tr>
    <tr>
      <td></td>
      <td><input  runat="server"  type="hidden"   name="products"  id="products"  value="11"></td>
    </tr>
  </table>
    <p align="center">
    <input type="submit" runat="server"     name="b1" id="Submit1" value="立即支付">
    
    <asp:Literal runat="server" ID="lit_web"   Visible="false"/>

		</div>

            <div class="clear">
            </div>
        </div>
        <!--资讯内容结束-->
        <div class="clear">
        </div>
        <!--右边部分结束-->
        <div class="clear">
        </div>
    </div>
    <!--页面主体结束-->
    <!--底部开始-->
    <uc3:Bottom ID="Bottom1" runat="server" />
    <!--底部结束-->
    </form>
</body>
</html>