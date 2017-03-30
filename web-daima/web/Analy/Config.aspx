<%@ Page Language="C#" AutoEventWireup="true" Codebehind="Config.aspx.cs" Inherits="DataAnaly.Analy.Config" %>

<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<%@ Register Assembly="dotnetCHARTING" Namespace="dotnetCHARTING" TagPrefix="dotnetCHARTING" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>
</head>
<body>
	<form id="form1" runat="server">
		<Bzw:Top runat="server" ID="top1" EnableViewState="false" />
		<div id="content">
			<Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
			<div id="tabs">
				<div class="tab">
					<ul>
						<li class="active" onclick="SetForms(0)">参数设置</li>
					</ul>
					<div class="clear">
					</div>
				</div>
				<div class="forms">
					<ul class="formShow">
						<li>
							<table style="width: 60%;">
								<tr>
									<th align="right">
										活跃用户标准（即当日所需的游戏局数）：
									</th>
									<td align="left">
										<asp:TextBox runat="server" ID="txtNeedGameCount" MaxLength="8" Width="250px"></asp:TextBox>
										<asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="txtNeedGameCount" Display="dynamic" runat="server" ErrorMessage="请输入活跃用户标准"></asp:RequiredFieldValidator>
										<asp:CompareValidator ID="CompareValidator1" ControlToValidate="txtNeedGameCount" Display="Dynamic" Operator="GreaterThanEqual" Type="Integer" ValueToCompare="0" runat="server" ErrorMessage="请输入大于或等于0的整数"></asp:CompareValidator></td>
								</tr>
								<tr>
									<th align="right">
										网站名称：
									</th>
									<td align="left">
										<asp:TextBox runat="server" ID="txtSiteName" MaxLength="500" Width="250px"></asp:TextBox>
									</td>
								</tr>
							</table>
						</li>
					</ul>
				</div>
			</div>
			<div id="btns">
				<div>
					<%-- 下面的返回按钮记得修改返回路径 --%>
					<asp:Button runat="server" ID="btnSubmit" CssClass="btnPublic" Text="提交" OnClick="btnSubmit_Click" />&nbsp;&nbsp;
					<%if( !string.IsNullOrEmpty( HN.Common.CommonManager.Web.Request( "reurl", "" ).Trim() ) )
	   {%>
					<input type="button" value="返回" class="btnPublic" onclick="LocationTo(decodeURIComponent(GetRequest('reurl','/Analy/Online/OnlineUser_Date.aspx')));" /><%} %>
				</div>
			</div>
		</div>
	</form>
</body>
</html>
