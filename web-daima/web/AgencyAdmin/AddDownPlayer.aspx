<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AddDownPlayer.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.AddDownPlayer" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>增加下属的玩家</title>
	<script type="text/javascript" src="/Public/js/jquery.js"></script>
	<script type="text/javascript" src="/Public/js/public.js"></script>
	
</head>
<body>
	<form id="form1" runat="server">
	<div style="text-align: center; font-size: 13px;">
		<table border="1px;" style="width: 75%; border-collapse: collapse;">
			<tr>
				<td align="center" colspan="2">
					<font size="4"><b>添加玩家</b></font>
				</td>
			</tr>
			<tr>
				<td colspan="2">
					<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
				</td>
			</tr>
			<tr>
				<td style="width: 200px;">
					玩家帐号:
				</td>
				<td style="text-align: left;">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<asp:TextBox ID="tbxUser" runat="server" MaxLength="20" onblur="checkUsername()" /><span style="color: red">*</span>
					&nbsp;&nbsp; <span id="spuser">由5-20个英文字母或数字组成。</span>
				</td>
			</tr>
			<tr>
				<td style="width: 200px;">
					昵称:
				</td>
				<td style="text-align: left;">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<asp:TextBox ID="txtNickName" runat="server" MaxLength="20" onblur="checkNickName()" /><span style="color: red">*</span>
					&nbsp;&nbsp; <span id="spnick"></span>
				</td>
			</tr>
			<tr style="display:none;">
				<td style="width: 200px">
					真实姓名:
				</td>
				<td style="text-align: left;">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<asp:TextBox ID="tbxName" runat="server" MaxLength="25" onblur="checkTrueName()" /><span style="color: red">*</span>
					&nbsp;&nbsp;<span id="spname">请认真填写姓名,一旦提交,将不允许修改。</span>
				</td>
			</tr>
			<tr>
				<td style="width: 200px">
					密&nbsp;&nbsp;码:
				</td>
				<td style="text-align: left">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<asp:TextBox ID="tbxPassword" runat="server" TextMode="Password" MaxLength="20" onblur="checkPwd()" /><span style="color: red">*</span>
					&nbsp;&nbsp;<span id="sppwd1">密码由6-20个英文字母或数字组成。</span>
				</td>
			</tr>
			<tr>
				<td style="width: 200px">
					再次输入密码:
				</td>
				<td style="text-align: left">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<asp:TextBox ID="tbxPassword2" runat="server" TextMode="Password" MaxLength="20" onblur="checkPwd2()" /><span style="color: red">*</span>
					&nbsp;&nbsp;<span id="sppwd2"></span>
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<asp:Button ID="btnSave" runat="server" Text="保 存" OnClick="btnSave_Click" OnClientClick="return f_checkIsNull()" />
				</td>
			</tr>
		</table>
	</div>
	</form>
</body>
<script type="text/javascript">

    function checkUsername() {
        var txtuser = $("#<%=tbxUser.ClientID %>");
        var sp = $("#spuser");
        if (txtuser.val().Trim() == '') {
            sp.text("请输入玩家帐号");
            sp.css("color", "red");
            return false;
        }
        else if (!/^[0-9a-zA-Z]{5,20}$/.test(txtuser.val().Trim())) {
            sp.text("玩家帐号由5-20个英文字母或数字组成，请重新输入！");
            sp.css("color", "red");
            return false;
        }
        $.get(
			"/Public/XmlHttpUser.aspx?type=nameexist&username=" + escape(txtuser.val().Trim()) + "&x=" + Math.random(),
			function (data) {
			    if (data == "1") {
			        sp.text("抱歉，玩家帐号已存在！");
			        sp.css("color", "red");
			        return false;
			    }
			}
		);
        sp.text("");
        return true;
    }

    function checkNickName() {
        var txt = $("#<%=txtNickName.ClientID %>");
        var sp = $("#spnick");
        if (txt.val().Trim() == '') {
            sp.text("请输入昵称！");
            sp.css("color", "red");
            return false;
        }
        $.get(
			"/Public/XmlHttpUser.aspx?type=nickexist&nickname=" + escape(txt.val().Trim()) + "&x=" + Math.random(),
			function (data) {
			    if (data == "1") {
			        sp.text("抱歉，昵称已存在！");
			        sp.css("color", "red");
			        return false;
			    }
			}
		);
        sp.text("");
        return true;
    }

    function checkTrueName() {
        //		if ($("#<%=tbxName.ClientID%>").val().Trim() == "")
        //		{
        //			$("#spname").text("请输入真实姓名！");
        //			$("#spname").css("color","red");
        //			
        //			return false;
        //		}
        //		$("#spname").text("");
        return true;
    }

    function checkPwd() {
        var _tbxPassword = $("#<%=tbxPassword.ClientID%>");
        var sppwd1 = $("#sppwd1");

        if (_tbxPassword.val().Trim() == "") {
            sppwd1.text("帐号密码不能为空！");
            sppwd1.css("color", "red");
            return false;
        }
        else if (!/^[0-9a-zA-Z]{6,20}$/.test(_tbxPassword.val().Trim())) {
            sppwd1.text("密码由6-20个英文字母或数字组成！");
            sppwd1.css("color", "red");
            return false;
        }
        sppwd1.text("");
        return true;
    }
    function checkPwd2() {
        //---------------------
        var _tbxPassword = $("#<%=tbxPassword.ClientID%>");
        var _tbxPassword2 = $("#<%=tbxPassword2.ClientID%>");
        var sppwd2 = $("#sppwd2");

        //-------------------
        if (_tbxPassword2.val().Trim() != _tbxPassword.val().Trim()) {
            sppwd2.text("两次输入的密码不一样，请重新输入！");
            sppwd2.css("color", "red");
            return false;
        }
        sppwd2.text("");
        return true;
    }

    function f_checkIsNull() {
        if (!checkUsername()) {
            $("#<%=tbxUser.ClientID %>")[0].focus();
            return false;
        }

        if (!checkNickName()) {
            $("#<%=txtNickName.ClientID %>")[0].focus();
            return false;
        }

        //--------------------------------
        if (!checkTrueName()) {
            $("#<%=tbxName.ClientID%>")[0].focus();
            return false;
        }

        //---------------------
        if (!checkPwd()) {
            $("#<%=tbxPassword.ClientID%>")[0].focus();
            return false;
        }
        if (!checkPwd2()) {
            $("#<%=tbxPassword2.ClientID%>")[0].focus();
            return false;
        }

        return true;

    }
</script>
</html>
