<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrEdit" Codebehind="PrEdit.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>
        <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
        <script src="/Public/Js/jquery.js"></script>
        <script src="/Public/Js/public.js"></script>
    <style type="text/css">
<!--
body {

	margin-top: 0px;
}
-->
</style>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>修改推广员资料</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    用户名：</td>
                <td width="83%" align="left">
                    <font color="red"><%=TGUserName %></font></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    真实姓名：</td>
                <td width="83%" align="left">
                    <input type="text" name="Truename" value="<%=Truename %>" class="put" maxlength="10"/></td>
            </tr>
             <tr>
                <td width="17%" align="right">
                    身份证号码：</td>
                <td width="83%" align="left">
                    <input type="text" name="IDCardNo" value="<%=IDCardNo %>" class="put" maxlength="20"/></td>
            </tr>
              <tr>
                <td align="right">
                    身份证正面图片</td>
                <td align="left">
					<asp:PlaceHolder runat="server" ID="phImageIDCardMain">
						<asp:TextBox runat="server" ID="txtImageIDCardMain" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageIDCardMain.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileUpload">
						<asp:FileUpload runat="server" ID="fuImageIDCardMain" />（300K以内，仅允许jpg,jpeg及gif格式）
					</asp:PlaceHolder>
                    <%--<iframe src='../inc/upload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                </td>
            </tr>

            <tr>
                <td align="right">
                    身份证反面图片</td>
                <td align="left">
					<asp:PlaceHolder runat="server" ID="phImageIDCardOther">
						<asp:TextBox runat="server" ID="txtImageIDCardOther" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageIDCardOther.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileUpload1">
						<asp:FileUpload runat="server" ID="fuImageIDCardOther" />（300K以内，仅允许jpg,jpeg及gif格式）
					</asp:PlaceHolder>
                    <%--<iframe src='../inc/upload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                </td>
            </tr>

            <tr>
                <td width="17%" align="right">
                    联系电话：</td>
                <td width="83%" align="left">
                    <input type="text" name="Phone" value="<%=Phone %>" class="put" maxlength="20" /></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    联系地址：</td>
                <td width="83%" align="left">
                    <input type="text" name="Address" value="<%=Address %>" class="put"  maxlength="50"/></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    开户行：</td>
                <td width="83%" align="left">
                    <input type="text" name="BankName" value="<%=BankName %>" class="put"  maxlength="50"/></td>
            </tr>
              <tr>
                <td width="17%" align="right">
                    银行账号：</td>
                <td width="83%" align="left">
                    <input type="text" name="BankNo" value="<%=BankNo %>" class="put"  maxlength="50"/></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    总收入：</td>
                <td width="83%" align="left">
                    <font color="red"><%= MoneyCount%></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    统计时间：<%=CountTime%></td>
            </tr>
            <tr>
                <td align="right">
                    是否审核：</td>
                <td align="left">
                    
                      
                    <input type="radio" name="CheckState" value="0" class="put" <%= (CheckState.ToString().ToLower()=="0" ? "CHECKED" : "") %>/>未审核
                    <input type="radio" name="CheckState" value="1" class="put" <%= (CheckState.ToString().ToLower()=="1" ? "CHECKED" : "") %>/>审核中
                    <input type="radio" name="CheckState" value="2" class="put" <%= (CheckState.ToString().ToLower()=="2" ? "CHECKED" : "") %> />审核通过
                    <input type="radio" name="CheckState" value="3" class="put" <%= (CheckState.ToString().ToLower()=="3" ? "CHECKED" : "") %>/>审核未通过
                </td>
            </tr>
             <tr>
                <td width="17%" align="right">
                    审核未通过理由：</td>
                <td width="83%" align="left">
                   
                    <textarea id="txtRemark" cols="40" rows="6" runat="server"></textarea></td>
                 
            </tr>
            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="确认修改" class="put" OnClick="PrEd" />
                    <input type="reset" name="Submit2" value="还原设置" class="put" />
                    <input type="button" name="Submit2" onclick="javascript:history.back();" value="返回上一页"
                        class="put" />
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
