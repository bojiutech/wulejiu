<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PlayerLanding.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.PlayerLanding" %>
<%@ Register Assembly="MyPage" Namespace="MyPage" TagPrefix="cc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>会员登入日志</title>
    <script src="/Public/Js/Global.js" type="text/javascript"></script>
    <script src="/Public/Js/DatePicker/WdatePicker.js" type="text/javascript"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center; font-size:13px;">
        <table border="1px;" style="width:85%;border-collapse:collapse;" >
            <tr><td><font size="3"><b>玩家在游戏大厅的登录日志</b></font></td></tr>
                <tr>
                    <td>
				    开始日期：<asp:TextBox ID="dtpFrom" Width="85px"  MaxLength="10" runat="server"  onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'dtpTo\')}'});"></asp:TextBox><span style="color:Red">*</span>
				    &nbsp;&nbsp;结束日期：<asp:TextBox ID="dtpTo" Width="85px"  MaxLength="10" runat="server"  onfocus="WdatePicker({minDate:'#F{$dp.$D(\'dtpFrom\')}',dateFmt:'yyyy-MM-dd'});"></asp:TextBox><span style="color:Red">*</span>
                    &nbsp;&nbsp;<asp:Button ID="btnSearch" runat="server" Text=" 查 询 " OnClick="btnSearch_Click" OnClientClick="return OnSearch()" />
                    查询前请先选择开始日期和结束日期
                    </td>
                    <script type="text/javascript" >
                        function OnSearch() {
                            var dtpFrom = document.getElementById('dtpFrom');
                            if (dtpFrom.value.trim() == '') {
                                dtpFrom.focus();
                                return false
                            }

                            var dtpTo = document.getElementById('dtpTo');
                            if (dtpTo.value.trim() == '') {
                                dtpTo.focus();
                                return false
                            }

                            return true;
                        }
                    </script>
                </tr>           
            <tr>
                <td style="text-align:left;" colspan="4">
                <asp:Repeater ID="rptPlayerLogList" runat="server">
                    <HeaderTemplate>
                        <table style="width:100%;text-align:center;border-collapse:collapse;margin:0px;padding:0px;" border="1";>
                            <tr>
                                <td>玩家ID</td>
                                <td>玩家帐号</td>
                                <td>最后登录</td>
                                <td>登录IP</td>                                                                
                            </tr>
                    </HeaderTemplate>
                    <ItemTemplate>
                            <tr>
                                <td><%# Eval("UserID")%></td>
                                <td><%# Eval("UserName")%></td>
                                <td><%# Eval("LastLoginTM")%></td>
                                <td><%# Eval("LastLoginIP")%></td>                                                          
                            </tr>                                                
                    </ItemTemplate>
                    <FooterTemplate>
                        </table>                     
                    </FooterTemplate>
                </asp:Repeater> 
                        <table width="100%" align="center">
                            <tr>
                                <td align="center" colspan="5">
                                <asp:Label ID="NoDataList" runat="server" Text="没有记录！" Visible="false"></asp:Label>
                                </td>
                            </tr>
                        </table>     
            		<table width="100%">
						<tr>
							<td colspan="2" style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
                           <cc1:Pager ID="Pager1" runat="server" PageSize="15" OnPageIndexChanging="Pager1_PageIndexChanging" />
							</td>
						</tr>
					</table>             
                </td>
            </tr>
        </table>     
    </div>
    </form>
</body>
</html>

