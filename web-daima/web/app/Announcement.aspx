<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Announcement.aspx.cs" Inherits="HN.Web.app.Announcement" %>

<!DOCTYPE>
<html>
<head id="Head1" runat="server">
    <title></title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0" />
    <!--[if lt IE 9]><script src="http://css3-mediaqueries-js.googlecode.com/svn/trunk/css3-mediaqueries.js"></script><![endif]-->
    <style type="text/css">
        * { margin: 0; padding: 0; border: 0; font: normal 100% Helvetica, Arial, sans-serif; }
        h1 { font-size: 1.5em; }
        .bg { margin: 0; padding: 0; margin: 0; border: 0; background-color: #070011;min-height:350px; }
        table { border: none; margin: 0; padding: 0; color: #ddd; width: 100%; }
         table tr td table{background: url(/Image/bg03.png); filter: "progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod='scale')"; -moz-background-size: 100% 100%; background-size: 100% 100%;}
        table tr td table tr{ border: none; margin: 0; padding: 0; }
        table tr td table tr th { border: none; margin: 0; padding: 0; width: 100%; height: 44px; line-height: 44px; text-align: center; float: left; font-size: 14px; color: #fee084; }
        table tr td table tr th .left { float: left; line-height: 44px; color: #ffffa3; display: block; background: url(/Image/bg01.png); filter: "progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod='scale')"; -moz-background-size: 100% 100%; background-size: 100% 100%; width: 60%; }
        table tr td table tr th .right { float: right; line-height: 44px; color: #fee084; width: 40%; }
        table tr td table tr td { border: none; margin: 0; padding: 5% 10%; color: #fee084;  }
    </style>
</head>
<body>
    <div class="bg">
        <table border="0" cellpadding="0" cellspacing="0">
        <tr>
        <td>
            <asp:Repeater ID="AnnouncementRep" runat="server">
                <ItemTemplate>
                <table>
                    <tr>
                        <th>
                            <span class="left">
                                <%# Eval("MTitle")%></span> <span class="right">
                                    <%# Eval("AddTime")%></span>
                        </th>
                    </tr>
                    <tr>
                        <td>
                            <%# Eval("MContent")%>
                        </td>
                    </tr>
                    </table>
                </ItemTemplate>
            </asp:Repeater>
            </td>
            </tr>
        </table>
    </div>
</body>
</html>
