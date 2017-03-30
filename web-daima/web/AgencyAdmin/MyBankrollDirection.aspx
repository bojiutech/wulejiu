<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MyBankrollDirection.aspx.cs"
    Inherits="Bzw.Web.AgencyAdmin.MyBankrollDirection" %>

<%@ Register Assembly="MyPage" Namespace="MyPage" TagPrefix="cc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>财务状况</title>
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align: center; font-size: 13px;">
        <font size="4"><b>代理商<span style="color: Red"><%=UiCommon.AgencyLoginInfo.AgencyName%></span>金币流水账</b></font>
    </div>
    <div style="text-align: center; font-size: 13px;">
        <table border="1px;" cellpadding="3" style="width: 80%; border-collapse: collapse;
            margin: 0;">
            <tr>
                <td align="left">
                    <input maxlength="30" type="text" id="txtKey" name="txtKey" style="display: none" />&nbsp;<input
                        style="display: none" maxlength="5" type="text" id="txtUserID" name="txtUserID" />&nbsp;
                    <br />
                    充值时间从：<asp:TextBox runat="server" ID="txtBeginDate" class="put" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;
                    到：<asp:TextBox runat="server" ID="txtEndDate" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;
                    <asp:DropDownList runat="server" ID="selPayType" name="selPayType" AutoPostBack="true"
                        OnSelectedIndexChanged="selPayTypeSelectedIndexChanged">
                        <asp:ListItem Text="所有" Value="-1"> </asp:ListItem>
                        <asp:ListItem Text="给代理充值" Value="1"> </asp:ListItem>
                        <asp:ListItem Text="给玩家充值" Value="2"> </asp:ListItem>
                        <asp:ListItem Text="提取代理金币或钻石" Value="3"> </asp:ListItem>
                        <asp:ListItem Text="提取玩家金币或钻石" Value="4"> </asp:ListItem>
                        <asp:ListItem Text="获取的抽水" Value="5"> </asp:ListItem>
                        <%--  <asp:ListItem Text="申请兑换" Value="6"> </asp:ListItem>
                        <asp:ListItem Text="系统返还" Value="7"> </asp:ListItem>--%>
                        <asp:ListItem Text="点卡充值" Value="8"> </asp:ListItem>
                        <asp:ListItem Text="网银充值" Value="9"> </asp:ListItem>
                    </asp:DropDownList>
                    <asp:Button Text="搜索" runat="server" OnClick="Unnamed1_Click" />
                    <input type="button" value="刷新" onclick="RefreshMe();" />
                </td>
            </tr>
            <tr>
                <td align="left" style="padding: 5px;">
                    <span runat="server" id="span_Rs"></span>&nbsp;
                    <span runat="server" id="spanJewels"></span>
                </td>
            </tr>
            <tr>
                <td>
                    <table style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px;
                        padding: 0px;" border="1px;" id="TABLE1">
                        <tr>
                            <th>
                                序号
                            </th>
                            <th>
                                类型
                            </th>
                            <th>
                                金币数量
                            </th>
                    <th>
                                钻石数量
                            </th>
                            <th>
                                日期
                            </th>
                            <th>
                                备注
                            </th>
                        </tr>
                        <asp:Repeater ID="rptDataList" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <td>
                                        <%# Container.ItemIndex + 1%>
                                    </td>
                                    <td>
                                        <%# TypeName(int.Parse(Eval("TypeID").ToString()), int.Parse(Eval("stype").ToString()))%>
                                    </td>
                                    <td>
                                        <%#Eval("NumMoeny")%>
                                    </td>
                              <td>
                                        <%#Eval("NumJewels")%>
                                    </td>
                                    <td>
                                        <%#Eval("AddTime") %>
                                    </td>
                                    <td>
                                        <%#Eval("Remark") %>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                        <asp:Label ID="lbNonData" runat="server" Text="<tr><td colspan='10'>没有记录！</td></tr>"
                            Visible="false"></asp:Label></table>
                    <table width="100%">
                        <tr>
                            <td colspan="2" style="font-size: 12px; color: #0099ff; background-color: #e6feda;
                                text-align: center;">
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
