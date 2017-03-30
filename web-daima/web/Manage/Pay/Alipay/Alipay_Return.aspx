<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Alipay.Manage_Pay_Alipay_Return" %>






<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head2" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
    <title>
      
    </title>
  
  
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <style type="text/css">
   .logo {
background: url(/images/structurePng.png) no-repeat;
background-position: -81px -50px;
width: 251px;
height: 98px;
 float:left;
cursor: pointer;
}
    </style>
</head>
<body>
<form id="form1" runat="server">
             <div id="Div1" style=" text-align:center; margin:0 auto; width:100%;">






            <div id="Div2">
                <h3 class="fl">
                    返回支付结果</h3>
                <p class="dqwz">
                    </p>
            </div>
            <div id="Div3" style=" text-align:center; margin:0 auto; width:100%;">
                <div  style=" text-align:left; margin:0 auto; width:25%;  line-height:180%; color:Blue; float:left;">&nbsp;
                </div>

        <div class="logo">
             
             </div>

        <div  style=" text-align:left; margin:0 auto; width:30%;  line-height:180%; color:Blue; float:left;">
            
          支付结果：   
                                         <%=PayResult %>
                                    <asp:Literal ID="Lab_msg" runat="Server" />
                                          
 <br/>
     订单号：    <%=PayOrderID %><br/>      充值金额：      <%=PayMoney %><br/>

       <a href="/" style=" color:Red" title="网站首页">网站首页</a><br/>
                   
                    </div>
                    </div>
                </div> <p>
                &nbsp;</p>
                
           
            <!--right End-->
 </form>
</body>
</html>