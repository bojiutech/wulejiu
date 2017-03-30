<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AddDownAgency" Codebehind="AddDownAgency.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>增加我的下线代理</title>
	<link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript">
    
        function ExistName(agencyName){
            var reVal = '0';
            var urlData = '/Admin/AgencyValidate.aspx?type=agencyexit&name='+escape(agencyName);
            //alert(urlData);
            try{
                return AjaxCall(urlData);
            }catch(e){
                return reVal;
            }
        }
        
        function OnExsitParent(){
            var txt = document.getElementById('<%=tbxParentAgency.ClientID %>');
            if(txt.value.trim() == '')
            {
                document.getElementById('spmsg1').innerText = '请输入上级代理商帐号';
                txt.focus();
                return;
            }
            var reval = ExistName(txt.value);
            if(reval=='1'){
                document.getElementById('spmsg1').innerText = '上级代理商存在';
            }else{
                document.getElementById('spmsg1').innerText = '抱歉，上级代理商不存在';
            }
        }
        
        function OnExsitName(){
            var txt = document.getElementById('<%=tbxUser.ClientID %>');
            if(txt.value.trim() == '')
            {
                document.getElementById('spmsg2').innerText = '请输入代理商帐号';
                txt.focus();
                return;
            }
            var reval = ExistName(txt.value);
            if(reval=='1'){
                document.getElementById('spmsg2').innerText = '抱歉，代理商帐号已存在';
            }else{
                document.getElementById('spmsg2').innerText = '代理商帐号可以使用';
            }
        }
        
        function OnExsitDomainName(){
            var txt = document.getElementById('<%=tbxDomain.ClientID %>');
            var msg = document.getElementById('span1');
            if(txt.value.trim() == '')
            {
                msg.innerText = '请输入代理商二级域名';
                txt.focus();
                return;
            }
            var reval = '0';
            var urlData = '/Admin/AgencyValidate.aspx?type=domainexit&name='+escape(txt.value.trim());
            alert(urlData);
            try{
                reval = AjaxCall(urlData);
            }catch(e){}
            if(reval=='1'){
                msg.innerText = '抱歉，代理商二级域名已存在';
            }else{
                msg.innerText = '代理商二级域名可以使用';
            }
        }
    
	</script>

</head>
<body>
	<form id="form1" runat="server" onsubmit="return f_checkIsNull()">
		<div style="text-align: center; font-size: 13px;">
			<table border="1px;" cellpadding="3" style="width: 98%; border-collapse: collapse;">
				<tr>
					<td align="center" colspan="2">
						<font size="4"><b>添加代理商</b></font>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						上级代理商帐号:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxParentAgency" runat="server" MaxLength="20" /><span style="color: Red">*</span>
						<a  href="javascript:OnExsitParent();">检测上级代理是否存在</a>
						<span id="spmsg1" style="color: Red" ></span>
							
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						代理商帐号:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxUser" runat="server" MaxLength="20" /><span style="color: red">*</span>
						由5-20个英文字母或数字组成&nbsp;&nbsp;
						<a  href="javascript:OnExsitName();">检测帐号是否存在</a>
						<span id="spmsg2" style="color: Red" ></span>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						帐号密码:</td>
					<td style="text-align: left; height: 29px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword" runat="server" TextMode="Password" Width="149px" MaxLength="20" /><span style="color: red">*</span></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						确认帐号密码:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword2" runat="server" TextMode="Password" Width="149px" MaxLength="20" /><span style="color: red">*</span></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						代理商二级域名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxDomain" runat="server" MaxLength="20" />
						由3-20个英文字母或数字组成；不填写则与代理商登录帐号一样&nbsp;&nbsp;
                        <a  href="javascript:OnExsitDomainName();">检测二级域名是否存在</a>
					        <span id="span1" style="color: Red" ></span>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						抽水比例:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxSpareValue" runat="server" Text="0" Width="30" MaxLength="3" />%<span style="color: red">*</span></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						真实姓名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxName" runat="server" MaxLength="10" /><span style="color: Red">*</span>
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						固定电话:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPhone" runat="server" MaxLength="20" />
						<asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="请输入格式正确的电话号码，如0755-12345678或020-88669977" ControlToValidate="tbxPhone" Display="Dynamic" ValidationExpression="(^((\()?0\d{2,3}(\))?(-)?)?\d{7,8}$)"></asp:RegularExpressionValidator>
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
						<asp:TextBox ID="tbxPostalCode" runat="server"  MaxLength="6"/>
						<asp:RegularExpressionValidator ID="RegularExpressionValidator3" runat="server" ControlToValidate="tbxPostalCode"
                            Display="Dynamic" ErrorMessage="请输入6位数字，如529600" ValidationExpression="\d{6}"></asp:RegularExpressionValidator>
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
						手机:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxMobile" runat="server" MaxLength="20"/>
						<asp:RegularExpressionValidator ID="RegularExpressionValidator4" runat="server" ControlToValidate="tbxMobile"
                            Display="Dynamic" ErrorMessage="请输入格式正确的手机号码，如13688885555" ValidationExpression="(^(0|\(0\))?(13|15|18)(\d){9}$)"></asp:RegularExpressionValidator>
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
				<tr>
					<td style="width: 200px; text-align: right;">
						备注:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox runat="server" ID="txtRemark" TextMode="multiLine" Rows="5" Width="250px"></asp:TextBox>最多50个字符
					</td>
				</tr>
				<tr>
					<td colspan="2">
					</td>
				</tr>
				<tr>
					<td colspan="2" align="center">
						<asp:Button ID="btnSave" CssClass="put" runat="server" Text=" 保 存 " OnClick="btnSave_Click" />
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>

<script type="text/javascript">
    function f_checkIsNull()
    {
    
        var _tbxParentAgency = document.getElementById("<%=tbxParentAgency.ClientID%>");
        var _tbxUser = document.getElementById("<%=tbxUser.ClientID%>");
        var _tbxName = document.getElementById("<%=tbxName.ClientID%>");
        var _tbxPassword = document.getElementById("<%=tbxPassword.ClientID%>");
        var _tbxPassword2 = document.getElementById("<%=tbxPassword2.ClientID%>");
        var _tbxSpareValue = document.getElementById("<%=tbxSpareValue.ClientID%>");
        var _tbxName = document.getElementById("<%=tbxName.ClientID%>");
        //-----------------
        if(_tbxParentAgency.value.trim()=="")
        {
            alert("上级代理商帐号不能为空!");
            _tbxParentAgency.focus();
            return false;   
        }  
        
        //------------------
        if(_tbxUser.value.trim()=="")
        {
            alert("代理商帐号不能为空!");
            _tbxUser.focus();
            return false;
        }else if(!/^[0-9a-zA-Z]{5,20}$/.test(_tbxUser.value.trim())){
            alert('代理商帐号由5-20个英文字母或数字组成，请重新输入');
            _tbxUser.focus();
            return false;
        }
        
        //---------------------
        if(_tbxPassword.value.trim()=="")
        {
            alert("帐号密码不能为空!");
             _tbxPassword.focus();
            return false;
        }
        
        //-------------------
        if(_tbxPassword2.value.trim() != _tbxPassword.value.trim())
        {
            alert("两次输入的密码不一样!请重新输入.");
             _tbxPassword2.focus();
            return false; 
        }
        
        //--------------------
        var twoName = document.getElementById("<%=tbxDomain.ClientID%>");
        if(twoName.value.trim()==''){
            twoName.value = _tbxUser.value.trim();
        }
        
        if(!/^[0-9a-zA-Z]{3,20}$/.test(twoName.value.trim())){
            alert('二级域名由3-20个英文字母或数字组成，请重新输入');
            twoName.focus();
            return false;
        }
        
        //------------------
        if( _tbxSpareValue.value.trim()=="")
        {
            alert("抽水比例不能为空,请输入");
            _tbxSpareValue.focus();
            return false;
        }
        
        if(_tbxName.value.trim()=="")
        {
            alert("代理商的真实姓名不能为空!");
            _tbxName.focus();
            return false;   
        }
        
        //----------------------
        var txtRemark = document.getElementById("<%=txtRemark.ClientID%>");
        if(txtRemark.value.length>50){
            alert('备注最多只允许输入50个字符');
            txtRemark.focus();
            return false;
        }
        
        return true;
        
    }
</script>

</html>
