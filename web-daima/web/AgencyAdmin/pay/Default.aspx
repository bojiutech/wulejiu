 <%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.pay.Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
      

       <link href="/css/Navigate.css" rel="stylesheet" type="text/css" />
       <style type="text/css">
       
.zhcz {height:683px;}
.zhcz li {background:url('/Images/cont_bg11.jpg') no-repeat;padding:14px 0 0 16px;width:314px;height:138px;float:left;margin:0 12px 5px 0;overflow:hidden;display:inline-block;}
.cz{ width:1000px; text-align:center;  margin:0px auto;}
.cz table {border-top:2px solid #0c71a0;margin:5px 0 5px 0;}
.cz tbody tr {border-bottom:1px solid #cccccc;height:30px;}
.cz tbody th {background-color:#f0f0f0;text-align:left;padding-left:10px;}
.cz tbody td {padding-left:10px;}
.yzm {background-color:#dddddd;width:42px;height:18px;text-align:center;margin-right:5px;}
.yzm01 {width:180px;}
.yzm02 {width:280px;}
.cz_btn {text-align:center;padding:30px 0 60px 0;}
.fl{ float:left; font-size:12px;}
       </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <div id="content01">
            <div id="title01" style="  text-align:center;">
             
               在线充值
            </div>
            <div id="sub_nr"  >
                <div class="cz">
                    <ul class="zhcz" style="height:780px;">
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/Images/cont_tbl_img20.jpg" alt="" /></div>
                            <strong class="text05">点卡充值</strong><br />
                            使用点卡充值卡，在官网上进行<br />
                            充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/PointCard.aspx">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <%if (UiCommon.StringConfig.YeepayMerID != "")
                          { %>
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/pay_01.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">网上银行充值</strong><br />
                            使用点卡充值卡，在官网上进行<br />
                            充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=Bank">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
 			<!--<li>
                       <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/jftpay.gif" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">聚付通在线支付</strong><br />
                        支持工商、招商、农业、建设等<br />
                        国内20家银行卡充值
                       <p style="padding-top: 7px;">
                            <a href="/Manage/Pay/JFTpay/Default.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>-->
                         <li style="display:none;">
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/Images/pay/pay_05.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">神州行充值卡充值</strong><br />
                            仅限移动用户，用神州行充值<br />
                            卡面额进行充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=SZX-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li style="display:none;">
                            <div class="fl" style="padding-right: 14px;" >
                                <img src="/Images/pay/czk.jpg" alt="" width="106px" height="84px" /></div>
                            <strong class="text05">联通卡充值</strong><br />
                            用联通卡充值卡面额进行充值。<br />
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=UNICOM-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li  style="display:none;">
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/pay/zt.jpg" alt="征途游戏卡充值" width="106px" height="84px" /></div>
                            <strong class="text05">征途游戏卡充值</strong><br />
                            用征途游戏卡充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=ZHENGTU-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                   
                        <li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/pay/qq.jpg" alt="Q币支付充值" width="106px" height="84px" /></div>
                            <strong class="text05">Q币支付充值</strong><br />
                            Q币支付充值。</br>
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=QQCARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                        <li>
                            <div class="fl" style="padding-right:14px;">
                                <img src="/images/Pay/jw.jpg" alt="全国骏网一卡通充值" width="106px" height="84px" /></div>
                            <strong class="text05">全国骏网一卡通充值</strong><br />
                            全国骏网一卡通充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=JUNNET-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
    			<li >
                            <div class="fl" style="padding-right:14px;">
                                <img src="/images/pay/sd.jpg" alt="盛大游戏卡充值" width="106px" height="84px" /></div>
                            <strong class="text05">盛大游戏卡充值</strong><br />
                            盛大游戏卡充值。
                            <p style="padding-top:15px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=SNDACARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>
                          <%}if(UiCommon.StringConfig.AlipayPartnerID!=""){ %>
                      <li>
                        <div class="fl" style="padding-right: 14px;">
                            <img src="/Images/pay/zfb.jpg" alt="" width="106px" height="84px" /></div>
                        <strong class="text05">支付宝在线支付</strong><br />
                      
                        国内27家银行和信用卡 
                       <p style="padding-top: 7px;">
                            <a href="/AgencyAdmin/Pay/AliPay/Index.aspx">
                                <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                    </li>

                        <!--<li>
                            <div class="fl" style="padding-right: 14px;">
                                <img src="/images/Pay/ybykt.jpg" alt="易宝一卡通充值" width="106px" height="84px" /></div>
                            <strong class="text05">易宝一卡通充值</strong><br />
                            易宝一卡通充值。
                           <p style="padding-top: 7px;">
                                <a href="/AgencyAdmin/Pay/Yeepay/Yeepay.aspx?params=YPCARD-NET">
                                    <img src="/Images/cont_btn05.jpg" alt="" /></a></p>
                        </li>-->
                        <%} %>
                    </ul>
                </div>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    </form>
</body>
</html>
