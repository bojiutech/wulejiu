<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PlayerDetail.aspx.cs" Inherits="DataAnaly.Analy.User.PlayerDetail" %>

<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
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
					<li class="active" onclick="SetForms(0)">
						查看玩家资料信息</li>
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
									玩家帐号：
								</th>
								<td align="left">
									<asp:Label ID="lbUserName" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									真实姓名：
								</th>
								<td align="left">
									<asp:Label ID="lbTrueName" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									帐号金币：
								</th>
								<td align="left">
									<asp:Label ID="lbWalletMoney" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									所属代理商：
								</th>
								<td align="left">
									<asp:Label ID="lbAgencyName" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									联系电话：
								</th>
								<td align="left">
									<asp:Label ID="lbPhone" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									QQ：
								</th>
								<td align="left">
									<asp:Label ID="lbQQNum" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									邮箱：
								</th>
								<td align="left">
									<asp:Label ID="lbEmail" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									注册时间/IP：
								</th>
								<td align="left">
									<asp:Label ID="lbRegTM" runat="server"></asp:Label>&nbsp;&nbsp;/&nbsp;&nbsp;<asp:Label ID="lbRegIP" runat="server"></asp:Label>
								</td>
							</tr>
							<tr>
								<th align="right">
									所在地区：
								</th>
								<td align="left">
									<%=Hebust.IpLocator.GetIpLocation( lbRegIP.Text.Trim() ).Country + " " + Hebust.IpLocator.GetIpLocation( lbRegIP.Text.Trim()).City%>（以注册的IP为参照）
								</td>
							</tr>
							<tr>
								<th align="right">
									最后登录时间/IP：
								</th>
								<td align="left">
									<asp:Label ID="lbLastTM" runat="server"></asp:Label>&nbsp;&nbsp;/&nbsp;&nbsp;<asp:Label ID="lbLastIP" runat="server"></asp:Label>
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
				<input type="button" value="返回" class="btnPublic" onclick="LocationTo(decodeURIComponent(GetRequest('reurl','/Analy/Online/OnlineUsers.aspx')));" />
			</div>
	</div> 
	</div>
	</form>
</body>
</html>
