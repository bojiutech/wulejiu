<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_DataManager_ByPlayerSpareValueCount" Codebehind="ByPlayerSpareValueCount.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>玩家抽水统计</title>
	<link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
    	<script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
 
</head>
<body>
    <form id="form1" runat="server">
   <div style="text-align:center; font-size:13px;margin:0 auto; width:98%; border:1px solid;">    
        <div style="text-align:center; font-size:14px; vertical-align:middle;font-weight:bold;background-color: aliceblue;">
           玩家抽水统计
        </div>
        <table border="1px;" style="width:100%;border-collapse:collapse; padding:0; margin:0;" align="center">
            <tr>
                <td colspan="4">
                    开始日期:<asp:TextBox ID="txtBegin" runat="server" CssClass="input" Width="85px"  MaxLength="10"></asp:TextBox><span style="color:Red;">*</span>
                    &nbsp;&nbsp;&nbsp;结束日期:<asp:TextBox ID="txtEnd" runat="server" CssClass="input" Width="85px"  MaxLength="10"></asp:TextBox><span style="color:Red;">*</span>
                    <asp:Button ID="btnSearch" runat="server" Text=" 查 询 " CssClass="put" OnClick="btnSearch_Click" OnClientClick="return OnBtnSearch()" />
                    &nbsp;<asp:Button ID="btnReload" runat="server" CssClass="put" Text=" 刷 新 " OnClick="btnReload_Click" />&nbsp;&nbsp;点击“刷新”按钮会显示近1个月内的数据
                    <script type="text/javascript" >
                        function OnBtnSearch(){
                            var dtpFrom =document.getElementById('txtBegin');
                            if(dtpFrom.value.trim()==''){
                                dtpFrom.focus();
                                return false
                            }
                            
                            var dtpTo =document.getElementById('txtEnd');
                            if(dtpTo.value.trim()==''){
                                dtpTo.focus();
                                return false
                            }
                            
                            return true;
                        }
                    </script>
                </td>
            </tr>  
            <tr>
                <td colspan="4">
                <asp:Repeater ID="rptBySpareValueTimeDetialList" runat="server">
                    <HeaderTemplate>
                        <table style="width:100%;text-align:center;border-collapse:collapse;" border="1px;">
                            <tr style="background-color:#F5F5F5;">
                                <th>序号</th>
                                <th>日期</th>
                                <th>抽水</th>
                                <th>查看详细</th>
                            </tr>
                    </HeaderTemplate>
                    <ItemTemplate>
                            <tr>
                                <td><%#Container.ItemIndex + 1 %></td>
                                <td><%# Eval("CurrentTime","{0:yyyy-MM-dd}")%></td>
                                <td><%# UiCommon.StringConfig.MoneyChu100(Eval("TotalMoney"))%></td>
                                <td><a href='/Admin/Agency/DataManager/EveryDaySpareValueList.aspx?tm=<%#Eval("CurrentTime", "{0:yyyy-MM-dd}")%>&btm=<%=txtBegin.Text.Trim() %>&etm=<%=txtEnd.Text.Trim() %>'>查看</a></td>                                                                                                    
                            </tr>                                                
                    </ItemTemplate>
                    <FooterTemplate>
                        </table>                      
                    </FooterTemplate>
                </asp:Repeater>
                </td>
            </tr>
            <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='4'>暂无数据...</td></tr>"></asp:Literal>
        </table>       
    </div>
    </form>
</body>
</html>
