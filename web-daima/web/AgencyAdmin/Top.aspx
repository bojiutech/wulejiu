<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Top.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.Top" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="/css/Navigate.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
    .sel{ color:Red;}
     .wsel{ color:#000;}
      .nav{ float:left;     background:url("../images/tableft7.gif") no-repeat left top;      margin:0;      padding:0 0 0 3px;      text-decoration:none;      }
      .nav span {float: left;display: block;background: url("/images/tabright7.gif") no-repeat right top;padding: 0px 0px 8px 8px;}
       </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" style="font-size: 12px;
            font-family: 宋体;">
            <tr>
                <td style="padding-left: 10px; height: 30px;">
                    帐号:
                    <asp:Label runat="server" Text="" ID="lab_UserName"></asp:Label>
                </td>
                <td>
                    真实姓名:
                    <asp:Label runat="server" Text="" ID="lab_TrueName"></asp:Label>
                </td>
                <td>
                    帐号金币:<span style="color: Red"><asp:Label runat="server" Text="" ID="lab_socre"></asp:Label></span>
                    &nbsp;
                   钻石:<span style="color: Red"><asp:Label runat="server" Text="" ID="LabJewels"></asp:Label></span>
                    <a href="javascript:window.location.reload();">刷新</a>
                </td>
                <td>
                    抽水比例: <span style="color: Red">
                        <asp:Label runat="server" Text="" ID="lab_bfb"></asp:Label></span>%
                </td>
                <td>
                    给代理充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_DlSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_DlSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    给玩家充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_WjSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_WjSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    提代理充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TDlSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TDlSum_Jewels"></asp:Label></span>
                </td>
                <td>
                    提玩家充金币共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TWjSum"></asp:Label></span>
                    &nbsp;
                    钻石共计：<span style="color: Red"><asp:Label runat="server" Text="0" ID="lab_TWjSum_Jewels"></asp:Label></span>
                </td>
            </tr>
        </table>
        <div id="tabs7">
            <ul>
                <li><a class="nav sel" href='/AgencyAdmin/Main.aspx' title="信息维护" target="Main"><span>信息维护</span></a></li>
                <li><a class="nav wsel" href='/AgencyAdmin/Pay/Default.aspx' title="充值" target="Main"><span>充值</span></a></li>
               
                <% if( Agency.Default.HasAddAgency(this.AgencyName)){ %>
                <li><a class="nav wsel" href='/AgencyAdmin/AddDownAgency.aspx?agencyName=admin' title="添加代理" target="Main">
                    <span>添加代理</span></a></li>
                    <%}%>
                <li><a class="nav wsel" href="/AgencyAdmin/AddDownPlayer.aspx" title="添加玩家" target="Main"><span>添加玩家</span></a></li>
                <li><a  class="nav wsel" href="/AgencyAdmin/MyDownAgency.aspx" title="直属代理" target="Main"><span>直属代理</span></a></li>
                <li><a class="nav wsel" href="/AgencyAdmin/MyDownPlayer.aspx" title="直属玩家" target="Main"><span>直属玩家</span></a></li>
                <li><a class="nav wsel" href="/AgencyAdmin/DownPlayerPayList.aspx" title="直属玩家充值记录" target="Main"><span>   直属玩家充值记录</span></a></li>                 
                <li><a class="nav wsel" href="/AgencyAdmin/DownShoperPayList.aspx" title="直属代理充值记录" target="Main"><span>直属代理充值记录</span></a></li>
                <li><a class="nav wsel" href="/AgencyAdmin/AgencySpreadView.aspx?agencyID=<%= this.AgencyID %>" title="代理推广查看"
                    target="Main"><span>查看推广</span></a></li>
                      <li><a class="nav wsel" href="/AgencyAdmin/MyBankrollDirection.aspx?agencyID=<%= this.AgencyID %>" title="财务状况"
                    target="Main"><span>财务状况</span></a></li>
                 
                <li><a class="nav wsel" href="/AgencyAdmin/PlayerLanding.aspx" title="玩家登录日志" target="Main"><span>玩家登录日志</span></a></li>
                </li>
                <li><a class="nav wsel" href="/AgencyAdmin/AgencyOut.aspx" title="安全退出" target="_parent"><span>安全退出</span></a></li>
            </ul>
        </div>
    </div>
    </form>
    <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
    <script type="text/ecmascript">
        $().ready(function () {
            $(".nav").click(function () {
                $(".nav").each(function () {
                   // console.log($(this).attr("href"));
                    $(this).removeClass("sel");
                    $(this).addClass("wsel");

                });
                $(this).removeClass("wsel");
                $(this).addClass("sel");

            });
        });
    
    
    </script>
</body>
</html>
