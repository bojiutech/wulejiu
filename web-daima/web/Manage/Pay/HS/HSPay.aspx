<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="HSPay.aspx.cs" Inherits="Bzw.Web.Manage.Pay.HS.HSPay" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
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
        .rechargeable_004 dl {
float: left;
width: 230px;
height: 37px;
padding: 0px;
margin: 10px 0px 10px 0;
}

/* CSS Document */
*{ margin:0; padding:0}
body{ font-family:Arial, Helvetica, sans-serif; font:"宋体"; font-size:12px; line-height:18px;}
li{ list-style:none}
.clear{ clear:both}
h2{ font-size:14px; margin:0 0 10px 0}

a:hover{ text-decoration:underline}


.bankName{ cursor:pointer;}

.container{ width:1000px; height:auto; margin:0 auto}
.container .header{}
.container .pagebody{}
.container .pagebody .productinfo{ padding:12px; border:3px solid #BCCCEE; background:#F0F7FF; min-height:30px;}
.container .pagebody .productinfo .title{ height:23px; border-bottom:1px dashed #999;}
.container .pagebody .productinfo .title ul li{ float:left;}
.container .pagebody .productinfo .title .name{ width:390px; padding:0 0 0 15px }
.container .pagebody .productinfo .title .seller{ width:110px; }
.container .pagebody .productinfo .title .price{ width:195px; text-align:right; font-weight:bold}
.container .pagebody .productinfo .productinfolist{ margin:5px 0 0 0;  clear:both; height:auto}
.container .pagebody .productinfo .productinfolist ul li{ font-size:14px; float:left}
.container .pagebody .productinfo .productinfolist .productname{ width:155px;}
.container .pagebody .productinfo .productinfolist .more{width:214px;}
.container .pagebody .productinfo .productinfolist .more a{ color:#0A4992; text-decoration:none}
.container .pagebody .productinfo .productinfolist .more a:hover{ color:#F00}
.container .pagebody .productinfo .productinfolist .sellername{ width:110px; text-align:center; color:#4F4F4F}
.container .pagebody .productinfo .productinfolist .pricenumber{ width:220px; text-align:right; color:#FF6600; font-weight:bold; font-size:18px}
.container .pagebody .productinfo .productinfolist .yuan{ color:#4F4F4F; width:37px; margin:0 0 0 10px}

.container .pagebody .productinfo .orderinfo{ border:1px solid #7DA0C9; background:#FFF; min-height:150px; clear:both; padding:7px; }
.container .pagebody .productinfo .orderinfo ul li{padding:2px; float:left; font-size:12px;}
.container .pagebody .productinfo .orderinfo .transactions_title{ width:70px; min-height:20px; font-weight:bold}
.container .pagebody .productinfo .orderinfo .transactions_info{ width:600px; min-height:20px;}

.container .pagebody .bankinfo{ margin:10px 0 0 0; height:auto}
.container .pagebody .bankinfo .paymenttitle{ background:url(../images/bg.gif) repeat-x; border:1px solid #88ACD4; height:23px; padding:6px 0 0 14px;}
.container .pagebody .bankinfo .paymenttitle span{ font-weight:bold; font-size:14px; color:#4D4D4D;}




.container .pagebody .bankinfo .banklist{ clear:both; border:3px solid #BCCCEE; background:#FAFDFF;}
.container .pagebody .bankinfo .banklist .bankfont{ margin:23px 0 0 13px; font-size:14px; width:100px; height:60px; float:left; color:#666}
.container .pagebody .bankinfo .banklist .banklistselect{ margin:20px 0 0 0; width:650px; float:left; height:auto;}
.container .pagebody .bankinfo .banklist .banklistselect ul{ height:40px; width:157px; float:left}
.container .pagebody .bankinfo .banklist .banklistselect ul li{ float:left}
.container .pagebody .bankinfo .banklist .banklistselect ul .radio_1{ padding:5px 0 0 0; width:20px; height:20px; display:inline}
.container .pagebody .bankinfo .banklist .banklistselect ul .bank_img{ width:95px; height:20px; border:1px solid #C8CACC; text-align:center}

.container .pagebody .bankinfo .banklist .bankpayment{ height:75px; width:98%; margin:0 auto; clear:both; border-top:1px dashed #999; padding:8px 0 0 0; text-align:right}
.container .pagebody .bankinfo .banklist .bankpayment input{ width:178px; height:32px; background:url(../images/button.gif); border:0; margin:20px 25px 0 0}

.bankpayment { border-top: 1px dashed #999999;clear: both;height: 75px;margin: 0 auto;padding: 8px 0 0;
 text-align: right;width: 98%;}
.bankpayment input{ width:178px; height:32px; background:url(../images/button.gif); border:0; margin:20px 25px 0 0;}


.container .pagebody .orderenter{ border:1px solid #99B1E2; background:#FAFDFF; padding:10px; height:43px;}
.container .pagebody .orderenter ul li{ float:left; height:25px;}
.container .pagebody .orderenter .orderleft{ width:75px;}
.container .pagebody .orderenter .orderright{ width:680px;}


.container .pagebody .recharge{ padding:10px; background:#FAFDFF; border:3px solid #BCCCEE; margin:15px 0 0 0; height:auto; _height:280px; min-height:280px; clear:both}
.container .pagebody .recharge .rechargefont{ padding:2px 0 0 0; width:70px; float:left}
.container .pagebody .recharge .rechargefont span{ color:#4B4C4D; font-size:14px;}
.container .pagebody .recharge .rechargetable{ width:680px; height:auto; float:left}
.container .pagebody .recharge .rechargetable .bankimg{ width:125px; height:30px; background:#FFF; text-align:center; border:1px solid #BCBCBC;}
.container .pagebody .recharge .rechargetable .bankinfotable{ margin:10px 0 5px 0; padding:5px 0 0 0; border-top:1px dashed #D6D6D6;}

.container .pagebody .recharge .rechargenumber{ float:left; width:500px; height:auto;}
.container .pagebody .recharge .rechargenumber .number{}
.container .pagebody .recharge .rechargenumber .number input{ width:50px; height:18px; margin:0 5px 0 0}
.container .pagebody .recharge .rechargenumber .numberfont{ background:url(../images/icon.gif) left no-repeat; padding:0 0 0 22px; margin:5px 0 0 0}
.container .pagebody .recharge .rechargenumber .numberfont span{ color:#CCC}

.container .pagebody .recharge .rechargenumber .signinrecharge{ margin:5px 0 0 0}
.container .pagebody .recharge .rechargenumber .signinrecharge input{ width:194px; height:33px; background:url(../images/button2.gif) no-repeat; border:0}

.container .pagebody .fontinfo{ margin:15px 0 0 0}
.container .pagebody .fontinfo ul li{ list-style:25px; color:#4D4D4D}

.container .footer{ height:50px; border-top:1px solid #4d4d4d; padding:15px 0 0 0; margin:40px 0 0 0}
.container .footer li{ height:30px; padding:6px 0 0 0; text-align:center}
.container .footer li a{ color:#000; text-decoration:none}

.rechargeable_004 { margin-left:70px;overflow: hidden;padding-left: 30px 0 10px 20px; width:90%; }
.rechargeable_004 dl {float: left;width: 230px;height: 37px;padding: 0px;margin: 10px 0px 10px 0;}
.rechargeable_004 dl dd {float: left;padding-top: 5px;width: 20px;}
.rechargeable_004 dl dt {float: left;border: 1px solid #c6c4c4;height: 34px;width: 190px;background-color: #FFF; overflow:hidden;}

.rechargeable_004 dl dt p{padding-top:10px;height: 24px; float:left; width:140px; cursor:pointer;}
.rechargeable_004 dl dt .bank_font{line-height:15px; color:#666; background: #f5efb8; width:50px; text-align:center; font-weight:bold;}

.rechargeable_004 dl dt .bank_icbc{background:url(/images/combo.gif) no-repeat left -397px; }
.rechargeable_004 dl dt .bank_cu{background:url(/images/combo.gif) no-repeat left -676px;}
.rechargeable_004 dl dt .bank_abc{background:url(/images/combo.gif) no-repeat left -1px; }
.rechargeable_004 dl dt .bank_bocsh{background:url(/images/combo.gif) no-repeat left -74px; }
.rechargeable_004 dl dt .bank_ccb{background:url(/images/combo.gif) no-repeat left -110px; }
.rechargeable_004 dl dt .bank_cmb{background:url(/images/combo.gif) no-repeat left -217px; }
.rechargeable_004 dl dt .bank_spdb{background:url(/images/combo.gif) no-repeat left -638px; }
.rechargeable_004 dl dt .bank_gdb{background:url(/images/combo.gif) no-repeat left -327px; }
.rechargeable_004 dl dt .bank_bocom{background:url(/images/combo.gif) no-repeat left -290px; }
.rechargeable_004 dl dt .bank_psbc{background:url(/images/combo.gif) no-repeat left -523px; }
.rechargeable_004 dl dt .bank_cncb{background:url(/images/combo.gif) no-repeat left -181px; }
.rechargeable_004 dl dt .bank_cmbc{background:url(/images/combo.gif) no-repeat left -255px; }
.rechargeable_004 dl dt .bank_ceb{background:url(/images/combo.gif) no-repeat left -146px; }
.rechargeable_004 dl dt .bank_hxb{background:url(/images/combo.gif) no-repeat left -363px; }
.rechargeable_004 dl dt .bank_cib{background:url(/images/combo.gif) no-repeat left -437px; }
.rechargeable_004 dl dt .bank_bos{background:url(/images/combo.gif) no-repeat left -560px; }
.rechargeable_004 dl dt .bank_srcb{background:url(/images/combo.gif) no-repeat left -472px; }
.rechargeable_004 dl dt .bank_pab{background:url(/images/combo.gif) no-repeat left -600px; }
.rechargeable_004 dl dt .bank_bccb{background:url(/images/combo.gif) no-repeat left -37px; }
.rechargeable_004 dl dt .bank_bccb{background:url(/images/combo.gif) no-repeat left -37px; }

.rechargeable_004 dl dt .bank_hebe{background:url(/images/comboMerchant.gif) no-repeat left -940px;}
.rechargeable_004 dl dt .bank_shenfa{background:url(../images/comboMerchant.gif) no-repeat left -858px;}
.rechargeable_004 dl dt .bank_huishang{background:url(../images/comboMerchant.gif) no-repeat left -820px;}
.rechargeable_004 dl dt .bank_dongya{background:url(../images/comboMerchant.gif) no-repeat left -716px;}
.transfer_001 {height: auto;}

.transfer_001 h2 {font-size: 14px;font-weight: normal;color: #4d4d4d;line-height: 45px;padding-left: 15px;}
.transfer_001 .transfer_002 {background: #f9faeb;overflow: hidden;padding: 25px 20px 20px 20px;}
.transfer_001 .transfer_022 {background: #FFF5E8;overflow: hidden;padding: 20px 0  20px 45px; border:#fce6a4 1px soid;}
.transfer_001 .transfer_006 {background: #ebf2fa;overflow: hidden;padding-top: 20px;}
.transfer_004 {height: auto;}
.transfer_004 .transfer_004top {height: auto;}
.transfer_004 .transfer_004center {height: auto;}
.transfer_004 .transfer_004top ul {overflow: hidden;font-size: 14px;line-height: 35px;padding-top: 8px;background:#FFF7D2 url(../images/index_37.gif) repeat-x left bottom;padding-left: 10px; height: 36px;}
.transfer_004top ul li {float: left;width: 150px;height: 35px;text-align: center;}
.transfer_004line{border-top: 1px solid #CCC;border-right: 1px solid #CCC;border-left: 1px solid #CCC;background-color: #FFF;color: #0961BC;}
.transfer_004 .transfer_004center {height: auto;}


.transfer_004 .transfer_023top{background: url(../images/index_37.gif) repeat-x left bottom;height: 43px;margin-top: 10px;}
.transfer_004 .transfer_023top ul {overflow: hidden;font-size: 14px;padding: 8px 0  0 10px;height: 35px;line-height: 35px;}
.rechargeable_016 {line-height: 18px;padding-left: 15px;margin-top: 15px;float: left;font-size: 14px;}



.transfer_023top ul li {float: left;width: 150px;height: 34px;text-align: center;color: #333;margin-left: 10px;border-top: 1px solid #CCC;border-right: 1px solid #CCC;border-left: 1px solid #CCC;background: url(../images/index_45.gif) repeat-x left bottom;_background: url(../images/index_45.gif) repeat-x left -16px ;}
.transfer_023top ul li a{color: #333; text-decoration:none;}

.transfer_023top ul li a:hover{ text-decoration:none;}


.transfer_023line{border-top: 1px solid #CCC;border-right: 1px solid #CCC;border-left: 1px solid #CCC;background-color: #FFF;}
.transfer_023top ul .transfer_004line{background-color: #FFF;color: #0961BC;border-right: 1px solid #CCC;border-left: 1px solid #CCC;border-top: 1px solid #CCC;border-bottom: 1px solid #fff;background-image: none;}
.transfer_005 {line-height: 50px;font-size: 18px;padding-left: 10px;font-family: "å¾®è½¯é›…é»‘";}
.account_center01 {margin-top: 10px;}
.management {height: auto;border: 1px solid #cccaca;}
.management_001 {border-bottom: 1px solid #CCC;font-size: 14px;color: #252424;font-weight: bold;line-height: 30px;overflow: hidden;padding-left: 10px;margin: 0px;height: 30px;}
.management_001 span {font-size: 12px;font-weight: normal;color: #999;float: right;}
.transfer_023top ul .transfer_004line a {color: #124DBA;}





.registered_009{font-size:14px; color:#999; border-top: 1px dashed #ccc; margin-top:10px; padding-top:10px; clear:both;}
.rechargeable_002 h3 {line-height: 30px;font-size: 14px;font-weight: normal;color: #999;}
.rechargeable_002 h3 .text_12px{ font-size:12px; color:#666666;}
.rechargeable_002 {margin-left:15px;}








.ebank_prompts {border: 1px solid #CCCCCC; width:970px;}
table {border-collapse: collapse; border-spacing: 0;}
.ebank_prompts th {background: none repeat scroll 0 0 #D3DFEB;border: 1px solid #CCCCCC; font-weight: bold;height: 25px;line-height: 25px;padding: 1px 0; text-align: center;}
.ebank_prompts td { border: 1px solid #CCCCCC;height: 23px;line-height: 23px; padding: 1px 0; text-align: center;}
.tall-leave-10{ margin-top:10px; padding:0 10px;}

.rechargeable {height: auto;padding: 10px;background-color: #FFF;}
.rechargeable h4 {font-weight: normal;font-size: 12px;color: #0a7ef6;line-height: 25px;}



    </style>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
</head>
<body>
         <form method="post"  runat="server" action="https://pay.ecpss.com/sslpayment" id="pay" target="_blank">
    <div class="bgBox">
        <img src="/images/Bg2.jpg" />
    </div>
    <div class="wrap">
        <div class="header">
            <div class="mainNav " id="mainNav">
                <uc1:NewMenu ID="NewMenu1" runat="server" />
            </div>
            <a href="/index.aspx">
                <div class="logo png">
                </div>
            </a>
        </div>
        <div class="totalContent">
            <div class="totalHd png" style="background-image: none; background-color: #9bceed; 
                overflow: hidden; height: 62px;">
                <i class="ico_67 i1 newsNotice png"></i>
                <div id='noticetime' class="time">
                    <span></span>
                </div>
                <div class="text" style="text-align: left;">
                    在线充值
                    <p>
                      汇潮在线支付</p>
                </div>
            </div>
            <div class="totalBd" style=" background-color:#bedff6;padding-bottom:20px; text-align:center; margin:0 auto;">
        
        <div class="rechargeable_004">
														<dl>
															<dd>

																<input name="bank" type="radio" id="rad_bank1" class="bankName"
																	value="ICBC" checked="true" />
															</dd>
															<label for="rad_bank1"><dt>
																	<p class="bank_icbc"></p>
																</dt></label>
														</dl>
														<dl id="bank_abc">
															<dd>
																<input name="bank" type="radio" id="rad_bank2" class="bankName"
																	value="ABC"  />

															</dd>
															<label for="rad_bank2"><dt>
																	<p class="bank_abc"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank3"
																	value="BOCSH" class="bankName" />
															</dd>
															<label for="rad_bank3"><dt>
																	<p class="bank_bocsh"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank4"
																	value="CCB" class="bankName" />
															</dd>
															<label for="rad_bank4"><dt>
																	<p class="bank_ccb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank5"
																	value="CMB" class="bankName"/>
															</dd>
															<label for="rad_bank5"><dt>
																	<p class="bank_cmb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank6"
																	value="SPDB" class="bankName" />
															</dd>
															<label for="rad_bank6"><dt>
																	<p class="bank_spdb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank7"
																	value="GDB" class="bankName" />
															</dd>
															<label for="rad_bank7"><dt>
																	<p class="bank_gdb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank8"
																	value="BOCOM" class="bankName" />
															</dd>
															<label for="rad_bank8"><dt>
																	<p class="bank_bocom"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank9"
																	value="PSBC" class="bankName" />
															</dd>
															<label for="rad_bank9"><dt>
																	<p class="bank_psbc"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank10"
																	value="CNCB" class="bankName"/>
															</dd>
															<label for="rad_bank10"><dt>
																	<p class="bank_cncb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank11"
																	value="CMBC" class="bankName" />
															</dd>
															<label for="rad_bank11"><dt>
																	<p class="bank_cmbc"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank12"
																	value="CEB" class="bankName"/>
															</dd>
															<label for="rad_bank12"><dt>
																	<p class="bank_ceb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank13"
																	value="HXB" class="bankName"/>
															</dd>
															<label for="rad_bank13"><dt>
																	<p class="bank_hxb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank14"
																	value="CIB" class="bankName"/>
															</dd>
															<label for="rad_bank14"><dt>
																	<p class="bank_cib"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank15"
																	value="BOS" class="bankName" />
															</dd>
															<label for="rad_bank15"><dt>
																	<p class="bank_bos"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank16"
																	value="SRCB" class="bankName" />
															</dd>
															<label for="rad_bank16"><dt>
																	<p class="bank_srcb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank17"
																	value="PAB" class="bankName" />
															</dd>
															<label for="rad_bank17"><dt>
																	<p class="bank_pab"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank18"
																	value="BCCB" class="bankName" />
															</dd>
															<label for="rad_bank18"><dt>
																	<p class="bank_bccb"></p>
																</dt></label>
														</dl>
														<dl>
															<dd>
																<input name="bank" type="radio" id="rad_bank19"
																	value="BOC"  class="bankName"/>
															</dd>
															<label for="rad_bank19"><dt>
																	<p class="bank_bocsh"></p>
																	<p class="bank_font">大额</p>
																</dt></label>
														</dl>
													</div>


  <p align="center">
    <input type="submit" runat="server"     name="b1" id="b1" value="立即支付">
  </p>


 <table align="center" style=" display:none">
    
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
    <script src="/Content/js/DD_belatedPNG.js"></script>
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

    <script type="text/javascript">
        $().ready(function () {
            $(".bankName").click(function () {
                $("#defaultBankNumber").val($(this).val());
            });
        });

        
</script>

</body>
</html>