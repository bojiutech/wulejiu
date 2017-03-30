<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Main.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.Main" %>
<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>代理商信息维护</title>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body>
	<form id="form1" runat="server" onsubmit="return f_checkIsNull()">
		<div style="text-align: center; font-size: 13px;">
			<table border="1" style="width: 98%; border-collapse: collapse;">
				<tr>
					<td align="center" colspan="2">
						<font size="4"><b>个人资料</b></font>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						登录名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxUser" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						登录密码:</td>
					<td style="text-align: left; height: 29px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword" runat="server" TextMode="Password" Width="149px" />不修改则留空</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						确认登录密码:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword2" runat="server" TextMode="Password" Width="149px" />
						<asp:CompareValidator ID="CompareValidator1" runat="server" ControlToCompare="tbxPassword" ControlToValidate="tbxPassword2" Display="Dynamic" ErrorMessage="两次输入的密码不一样"></asp:CompareValidator></td>
				</tr>
				<tr  style=" display:none">
					<td style="width: 200px; text-align: right;">
						二级域名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxDomain" runat="server"  MaxLength="20" />
						由3-20个英文字母或数字组成；不填写则与代理商登录帐号一样&nbsp;&nbsp;
                        <a  href="javascript:OnExsitDomainName();">检测二级域名是否存在</a>
					        <span id="span1" style="color: Red" ></span>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						真实姓名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxName" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
			</table>
			<table border="1" style="width: 98%; border-collapse: collapse; margin: 5px 0;">
				<tr>
					<td align="center" colspan="2">
						<font size="4"><b>收款信息</b></font>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						开户名:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAccountName" runat="server" MaxLength="25" Text="" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						开户行:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxBankName" runat="server" MaxLength="50" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						银行账号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAccountNo" runat="server" MaxLength="25" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						开户行地址:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxBankAddress" runat="server" MaxLength="50" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						支付宝账号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPayorNo" runat="server" MaxLength="50" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						财付通帐号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="txtTenpayNo" runat="server" MaxLength="100" />
					</td>
				</tr>
			</table>
			<table border="1" style="width: 98%; border-collapse: collapse;">
				<tr>
					<td align="center" colspan="2">
						<font size="4"><b>联系信息</b></font>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						手机:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxMobile" runat="server" MaxLength="20" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator4" runat="server" ControlToValidate="tbxMobile"
                            Display="Dynamic" ErrorMessage="请输入格式正确的手机号码，如13688885555" ValidationExpression="(^(0|\(0\))?(13|15|18)(\d){9}$)"></asp:RegularExpressionValidator>	
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						固定电话:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPhone" runat="server" MaxLength="20" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="请输入格式正确的电话号码，如0755-88888888或020-88888888" ControlToValidate="tbxPhone" Display="Dynamic" ValidationExpression="(^((\()?0\d{2,3}(\))?(-)?)?\d{7,8}$)"></asp:RegularExpressionValidator>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						联系地址:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAddress" runat="server" MaxLength="50" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						邮编:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPostalCode" runat="server" MaxLength="6" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator3" runat="server" ControlToValidate="tbxPostalCode"
                            Display="Dynamic" ErrorMessage="请输入6位数字，如518000" ValidationExpression="\d{6}"></asp:RegularExpressionValidator>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						Email:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxEmail" runat="server" MaxLength="50" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator2" runat="server" ErrorMessage="请输入格式正确的Email，如beby@163.com" ControlToValidate="tbxEmail" Display="Dynamic" ValidationExpression="[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}"></asp:RegularExpressionValidator>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						QQ号码:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxQQ" runat="server" MaxLength="15" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator5" runat="server" ControlToValidate="tbxQQ"
                            Display="Dynamic" ErrorMessage="请输入4-15位的数字" ValidationExpression="\d{4,15}"></asp:RegularExpressionValidator>
					</td>
				</tr>
				<tr style="display: none">
					<td style="width: 200px; text-align: right;">
						备注:</td>
					<td style="text-align: left">
					    <asp:TextBox ID="fckRemark" runat="server" MaxLength="50" />
					</td>
				</tr>
				<tr>
					<td colspan="2">
					</td>
				</tr>
				<tr>
					<td colspan="2" align="center">
						<asp:Button ID="btnSave" runat="server" Text=" 修 改 " OnClick="btnSave_Click" />
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
<script type="text/javascript">
    function OnExsitDomainName() {
        var txt = document.getElementById('<%=tbxDomain.ClientID %>');
        var msg = document.getElementById('span1');
        if (txt.value.trim() == '') {
            msg.innerText = '请输入二级域名';
            txt.focus();
            return;
        }
        var reval = '0';
        var urlData = '/Admin/AgencyValidate.aspx?type=updomainexit&name=' + escape(txt.value.trim()) + '&id=<%=UiCommon.AgencyLoginInfo.AgencyID %>';
        //alert(urlData);
        try {
            reval = AjaxCall(urlData);
        } catch (e) { }
        if (reval == '1') {
            msg.innerText = '抱歉，二级域名已存在';
        } else {
            msg.innerText = '二级域名可以使用';
        }
    }

    function f_checkIsNull() {
        var _tbxUser = document.getElementById("<%=tbxUser.ClientID%>");
        //--------------------
        var twoName = document.getElementById("<%=tbxDomain.ClientID%>");
        if (twoName.value.trim() == '') {
            twoName.value = _tbxUser.value.trim();
        }

        if (!/^[0-9a-zA-Z]{3,20}$/.test(twoName.value.trim())) {
            alert('二级域名由3-20个英文字母或数字组成，请重新输入');
            twoName.focus();
            return false;
        }

        var _tbxPostcode = document.getElementById("<%=tbxPostalCode.ClientID%>");
        if (_tbxPostcode.value.trim() != '' && !/^[0-9]{6}$/.test(_tbxPostcode.value.trim())) {
            alert('邮政编码由6个数字组成，请重新输入');
            _tbxPostcode.focus();
            return false;
        }

        return true;

    }
</script>
</html>
