<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="index.aspx.cs" Inherits="Bzw.Admin2.Admin.index" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>后台管理中心 v3.0</title>
<meta http-equiv=pragma content=no-cache>
<meta http-equiv=cache-control content=no-cache>
<meta http-equiv=expires content=-1000>
<link href="css/admin.css" type="text/css" rel="stylesheet">
</head>
<frameset border=0 framespacing=0 rows="60, *" frameborder=0>
<frame name=header src="header.aspx" frameborder=0 noresize scrolling=no>
<frameset cols="170, *">
<frame name=menu src="left.aspx" frameborder=0 noresize>
<frame name=main src="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/SystemStatEveryDay.aspx" frameborder=0 noresize scrolling=yes>
</frameset>
</frameset>
<noframes>
</noframes>