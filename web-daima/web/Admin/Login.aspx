<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Bzw.Admin2.Admin.Login" Debug="true" %>



<html xmlns="http://www.w3.org/1999/xhtml">
<head>

<title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>_管理后台</title>

  


  <script language="javascript" type="text/javascript">
      function EnterKey() {
          var t = document.getElementById("txt_no");
          if (t != null || t.value != "") {
              t.value = t.value.toUpperCase();
          }

      }
      function checkrest() {
          document.getElementById("txt_UserName").value = "";
          document.getElementById("txt_PassWord").value = "";
          document.getElementById("txt_no").value = "";
          return false;
      }
      function check() {

          var s = document.getElementById("txt_UserName").value;
          var spwd = document.getElementById("txt_PassWord").value;
          var sno = document.getElementById("txt_no").value;

          var fig = true;
          if (s == null || s.length == 0) {
              fig = false;
              alert("请输入用户名！");
              return false;
          }
          if (spwd == null || spwd.length == 0) {
              fig = false;
              alert("请输入密码！");
              return false;
          }
          if (sno == null || sno.length == 0) {
              fig = false;
              alert("请输入验证码！");
              return false;
          }

          return true;
      }
      function reloadcode() {
          var verify = document.getElementById('safecode');
          verify.setAttribute('src', '/Public/Getcode.aspx?' + Math.random());

      }


      function GetCookie(sName) {
          var aCookie = document.cookie.split("; ");
          for (var i = 0; i < aCookie.length; i++) {
              var aCrumb = aCookie[i].split("=");

              if (sName == aCrumb[0])
                  return unescape(aCrumb[1]);
          }
          return null;
      }
      function Mycookic() {
          var s = GetCookie("v1") + "__" + GetCookie("user_lanjm11");

          alert(s);
      }
        
        </script>
    <style type="text/css">
       #txt_UserName 
       {
      width:70px; 
	height:17px;
	color:Black;
	background-color:#87adbf;
	font-size:12px;
	border:solid 1px #153966;
	font-family:Arial, Helvetica, sans-serif;
	 font-weight:900;
	
}
      #txt_PassWord 
       {
      width:70px; 
	height:17px;
	color:Black;
	background-color:#87adbf;
	font-size:12px;
	border:solid 1px #153966;
	font-family:Arial, Helvetica, sans-serif;
	 font-weight:900;
	
}

      #txt_no 
       {
      width:70px; 
	height:17px;
	color:Black;
	background-color:#87adbf;
	font-size:12px;
	border:solid 1px #153966;
	font-family:Arial, Helvetica, sans-serif;
	 font-weight:900;
	
}

    </style>    
</head>

<body >
<form name="login" method="post" action="" id="login" runat="server">
<table width="100%"  height="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td bgcolor="#1075b1">&nbsp;</td>
  </tr>
  <tr>
    <td height="608" background="images/login_03.gif"><table width="847" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td height="318" background="images/login_04.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td height="84"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="381" height="84" background="images/login_06.gif">&nbsp;</td>
            <td width="162" valign="middle" background="images/login_07.gif">
            	<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="50" style="width:50px; font-size:12px;">用户名:</td>
    <td width="72"><input name="txt_UserName" type="text" maxlength="20" id="txtUserName" runat="server" style="height:18px;width:70px;" /></td>
    <td width="40">&nbsp;</td>
  </tr>
  <tr>
    <td style="width:50px; font-size:12px;">密&nbsp;&nbsp;码:</td>
    <td><input name="txt_PassWord" type="password" maxlength="20" id="txtPassword" runat="server" style="height:18px;width:70px;" /></td>
    <td>&nbsp;</td>
  </tr>
  
  <tr>
    <td style="width:50px; font-size:12px;">验证码:</td>
    <td><input name="txt_no" type="text" maxlength="4" id="txtCode" runat="server" style="height:18px;width:40px;" /></td>
    <td align="right">  <a href="javascript:reloadcode()"  t>
        <img src="/Public/Getcode.aspx" style="width:45px; height:20px;" id="safecode" style="border:0" title="看不清，换一张"  alt="看不清，换一张"/>
       
        </a></td>
  </tr>
</table>

            </td>
            <td width="26"><img src="images/login_08.gif" width="26" height="84"></td>
            <td width="67" background="images/login_09.gif"><table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td height="25"><div align="center">
                
                <asp:ImageButton ImageUrl="images/dl.gif"  OnClientClick="return check();" 
                        style="height:20px;width:57px;border-width:0px;"  runat="server" 
                        onclick="Unnamed1_Click"/>
                 
                </div></td>
              </tr>
              <tr>
                <td height="25"><div align="center">
                  <input type="image" name="ImageButton2" id="ImageButton2" src="images/cz.gif" onclick="return checkrest();" style="height:20px;width:57px;border-width:0px;" />
                </div></td>
              </tr>
            </table></td>
            <td width="211" background="images/login_10.gif">
            &nbsp;&nbsp;</td>
          </tr>
        </table></td>
      </tr>
      <tr>
        <td height="206" background="images/login_11.gif">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td bgcolor="#152753">&nbsp;</td>
  </tr>
</table>
</form>
<!-- oursdictionary.com Baidu tongji analytics -->
<script type="text/javascript">
    var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
    document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3Fc9e51dea66ece9f643fe8c0a58b4aea6' type='text/javascript'%3E%3C/script%3E"));
</script>
</body>
</html>
