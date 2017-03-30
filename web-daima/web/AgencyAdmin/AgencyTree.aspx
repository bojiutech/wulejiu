<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AgencyTree.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.AgencyTree" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
  <div style="color: Black">
			<asp:TreeView ID="tvAgencyView" Height="100%" runat="server" Width="100%" NodeIndent="10" ImageSet="msdn" SkinID="girdviewskin" PopulateNodesFromClient="False" ExpandDepth="1" ShowLines="True">
				<HoverNodeStyle BackColor="Transparent" BorderStyle="None" Font-Underline="True" ForeColor="Black" BorderWidth="0px" />
				<NodeStyle Font-Names="Verdana" Font-Size="8pt" ForeColor="Black" HorizontalPadding="5px" NodeSpacing="1px" VerticalPadding="2px" ImageUrl="~/images/agency/03.gif" />
				<LeafNodeStyle ForeColor="Black" />
			</asp:TreeView>
		</div>
    </form>
</body>
</html>
