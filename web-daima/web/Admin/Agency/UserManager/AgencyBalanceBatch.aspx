<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgencyBalanceBatch" Codebehind="AgencyBalanceBatch.aspx.cs" %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    	<script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
    <style type="text/css">
    <!--
    body {
	    
	    margin-top: 0px;
    }
    -->
    </style>
</head>
<body>
    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>代理商批量结算</strong></td>
            </tr>
            <tr>
                <td style="padding-left:100px;" colspan="2"><asp:Label ID="lbMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
            </tr>
            <tr>
            <td align="right" width="25%">
                    结算的最低金币：</td>
                <td align="left">
                    <asp:TextBox ID="txtMoney" runat="server"  Width="85px" MaxLength="9"></asp:TextBox>请输入大于或等于零的整数
                    </td>
            </tr>
            <tr>
                <td align="right" width="25%">
                    结算的截止日期：</td>
                <td align="left">
                    <asp:TextBox ID="txtDate" CssClass="Wdate" Width="85px" MaxLength="10" runat="server"></asp:TextBox>不能大于系统当前日期
                    </td>
            </tr>
            <tr>
                <td>
                    &nbsp;
                </td>
                <td>
                    <asp:Button ID="Button1" runat="server" CssClass="put" Text=" 结 算 " OnClick="button5_ServerClick"/>
                </td>
            </tr>
        </table>
        <script type="text/javascript">
        <!--  
            function onFormSubmit(f){
                
                var msgfix = '温馨提示：\n\n[';
                var msgend2 = '] 请输入大于或等于零的整数！';
            
                //----------
                if(!alertNonNegativeNumber($('#txtMoney')[0], msgfix+'结算的最低金币'+msgend2)){
                    return false;
                }
                
                if($('#txtDate')[0].value.trim() == ''){
                    alert('请输入结算的截止日期！');
                    $('#txtDate')[0].focus();
                    return false;
                }
                
                return confirm('确定要进行批量结算操作吗？');
                
                document.getElementById('<%=lbMsg.ClientID%>').innerText = '正在结算中，请不要关闭、刷新或切换该页面......';
                
                return true;
            }
         //-->
        </script>
    </form>
</body>
</html>
