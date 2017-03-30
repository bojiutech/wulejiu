<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AgencySpreadView.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.AgencySpreadView" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title>代理后台--树目录</title>
</head>
<frameset id="AdminMainFrame" cols="230,*" frameborder="1" border="0" framespacing="0" >

	<frame id="LeftTree" name="leftTree" src="AgencyTree.aspx?agencyID=<%= this.AgencyID %>" noresize="no" bordercolor="#008000">
	<frame id="LeftMain" name="leftMain" src="leftMianDetail.aspx?agencyID=<%= this.AgencyID %>" scrolling="no">
</frameset>
</html>
