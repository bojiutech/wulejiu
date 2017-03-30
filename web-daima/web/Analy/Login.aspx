<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="DataAnaly.Analy.Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>登录管理中心</title>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" language="javascript">
    <!--

        function CheckForm() {
            var AdminName = document.getElementById("txtUserName");
            if(AdminName.value == '') {
                alert('温馨提示：\n\n请输入用户名！');
                AdminName.focus();
                return false;
            }
            
            var AdminPwd = document.getElementById("txtPass");
            if(AdminPwd.value == '') {
                alert('温馨提示：\n\n请输入密码！');
                AdminPwd.focus();
                return false;
            }
            var GetCode = document.getElementById("GetCode");
            if (GetCode.value == '') {
                alert ('温馨提示：\n\n请输入验证码！');
                GetCode.focus();
                return false;
            }
            return true;
        }

    
		function TopLocationToMe()
		{
		    try{
			    if(parent != null && parent.location.href != location.href)
				    top.location.href = location.href;
				
			}catch(e){}
		}
	//-->
	</script>

	<style type="text/css">
		*{margin:0;padding:0;border:0;}
        body{
	        font-family:Arial, Helvetica, sans-serif, "宋体";
	        font-size:12px;
	        color:#fff;
	        background:#030 url(images/bg.jpg) no-repeat center top;
        }
        /*-------------loginPlease----------------*/
        #loginPlease{
			width:1004px;
			margin:0 auto;
			position:relative;
		}
        #login{
	        width:365px;
	        height:167px;
			padding:57px 0 0 31px;
			position:absolute;
			top:225px;
			left:378px;
	        background:url(images/login.jpg) no-repeat left top;
			z-index:100;
        }
       #login div{
		   font-weight:bold;
		   margin-bottom:11px;
	   }
	    #login div input{
			vertical-align:middle;
		}
        .fr_input01,.fr_input02{
	        width:150px;
	        height:17px;
	        line-height:17px;
			padding:2px 0 1px 23px;
	        border:1px solid #030;
			background:#fff url(images/icon10.gif) no-repeat 5px center;
        }
		.fr_input02{background:#fff url(images/icon11.gif) no-repeat 5px center;}
   		.w_input{width:49px;border:1px solid #030; height:16px;line-height:16px;padding-left:5px;padding-top:2px;}
        #login img{ vertical-align:middle;}
		#login_btn{
			width:98px;
			height:99px;
			position:absolute;
			top:312px;
			left:648px;
			z-index:1200;
		}
		#login_btn input{
			width:98px;
			height:99px;
			border:none;
			cursor:hand;
			vertical-align:middle;
			background:url(images/login_btn.jpg) no-repeat left top;
		}
		#lock{
			width:123px;
			height:156px;
			position:absolute;
			top:283px;
			left:277px;
			z-index:800;
		}
        #copyright{width:100%;clear:both;text-align:center;color:#fff;}
    
    </style>
</head>
<body onload="TopLocationToMe()">
	<form id="form1" method="post" onsubmit='return CheckForm();' runat="server">
		<div id="loginPlease">
			<div id="login_btn">
				<asp:Button name="btnSubmit" runat="server" ID="btnSubmit" value=" " OnClick="AddAdminLogin" /></div>
			<div id="login">
				<div>
					用户名：<asp:TextBox ID="txtUserName" runat="server" CssClass="fr_input01" MaxLength="20"></asp:TextBox></div>
				<div>
					密&nbsp;&nbsp;&nbsp; 码：<asp:TextBox runat="server" TextMode="Password" ID="txtPass"
						MaxLength="20" CssClass="fr_input02"></asp:TextBox></div>
				<div>
					验证码：<asp:TextBox ID="GetCode" runat="server" MaxLength="4" CssClass="w_input"></asp:TextBox>
					<img src="/Public/GetAnalyCode.aspx" width="41" height="16" onclick="this.src='/Public/GetAnalyCode.aspx?token='+tokenKey();"
						alt="点击换一张图片" /></div>
			</div>
			<div id="lock">
				<img src="images/lock.jpg" width="123" height="173" /></div>
		</div>
	</form>
</body>
</html>

<script type="text/javascript">
<!--
        document.getElementById('txtUserName').focus();
//-->
</script>

