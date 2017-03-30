<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MyDownPlayer.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.MyDownPlayer" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>我的游戏玩家</title>
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align: center; font-size: 13px;">
        <font size="4"><b>代理商<span style="color: Red"><%=this.AgencyName%></span>的直属玩家</b></font>
    </div>
    <div style="text-align: center; font-size: 13px;">
        <table border="1px;" cellpadding="3" style="width: 80%; border-collapse: collapse;
            margin: 0;">
            <tr>
                <td align="left">
                    <input maxlength="50" type="text" id="txtKey" name="txtKey" size="32" />&nbsp;
                    <input type="button" value="搜索" onclick="OnSearch();" />&nbsp;
                    <input type="button" value="刷新" onclick="RefreshMe();" />
                    <script>
                        var pkey = "请输入直属玩家帐号或真实姓名";
                        var o = $("#txtKey");
                        o.val(decodeURIComponent(GetRequest("key", pkey)));
                        o.css("color", "gray");
                        o.focus(function () { if (o.val().Trim() == pkey) { o.css("color", "black"); o.val(""); } });
                        o.blur(function () { if (o.val().Trim() == "") { o.css("color", "gray"); o.val(pkey); } });

                        function OnSearch() {
                            if (o.val().Trim() == "" || o.val().Trim() == pkey) {
                                alert("请先输入要搜索的直属玩家帐号或真实姓名。");
                                return;
                            }
                            LocationToMeParam("key=" + encodeURIComponent(o.val().Trim()));
                        }
                    </script>
                </td>
            </tr>
            <tr>
                <td>
                    <table style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px;
                        padding: 0px;" border="1px;" id="TABLE1">
                        <tr>
                            <th>
                                游戏帐号
                            </th>
                                <th>
                                玩家昵称
                            </th>
                            <th>
                                玩家姓名
                            </th>
                            <th>
                                银行<%=UiCommon.StringConfig.MoneyName%>
                            </th>
                            <th>
                                钱包<%=UiCommon.StringConfig.MoneyName %>
                            </th>
                            <th>
                                钻石
                            </th>
                            <th>
                                状态
                            </th>
                            <th>
                                操作
                            </th>
                        </tr>
                        <asp:Repeater ID="rptDataList" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <td>
                                        <%# Eval("UserName")%>
                                    </td>
                                     <td>
                                        <%# Eval("NickName")%>
                                    </td>
                                    <td>
                                        <%# Eval("TrueName")%>
                                    </td>
                                    <td>
                                        <%#Eval("BankMoney") %>
                                    </td>
                                    <td>
                                        <%# UiCommon.StringConfig.MoneyChu100(Eval("WalletMoney"))%>
                                    </td>
                                    <td>
                                        <%# UiCommon.StringConfig.MoneyChu100(Eval("Jewels"))%>
                                    </td>
                                    <td>
                                        <font style='color: <%# Convert.ToInt32(Eval("Disabled")) ==0?"black":"red"%>'>
                                            <%# Convert.ToInt32( Eval( "Disabled" ) ) == 0 ? "正常" : "禁用"%>
                                        </font>
                                    </td>
                                    <td>
                                        <%# Agency.Default.HasGiveToPlayer(this.AgencyName) ? "<a href=\"AgencyToBank.aspx?typeID=2&stype=1&agencyName=" + Server.UrlEncode(Eval("UserName").ToString()) + "&TrueName=" + Server.UrlEncode(Eval("NickName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">充" + UiCommon.StringConfig.MoneyName + "</a>&nbsp;|&nbsp;" : ""%>
                                        <%# Agency.Default.HasPickUpCashToPlayer(this.AgencyName) ? "<a href=\"BankToAgency.aspx?typeID=2&stype=1&agencyName=" + Server.UrlEncode(Eval("UserName").ToString()) + "&TrueName=" + Server.UrlEncode(Eval("NickName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">提" + UiCommon.StringConfig.MoneyName + "</a>&nbsp;|&nbsp;" : ""%>

                                         <%# Agency.Default.HasGiveToPlayer(this.AgencyName) ? "<a href=\"AgencyToBank.aspx?typeID=2&stype=2&agencyName=" + Server.UrlEncode(Eval("UserName").ToString()) + "&TrueName=" + Server.UrlEncode(Eval("NickName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">充钻石</a>&nbsp;|&nbsp;" : ""%>
                                        <%# Agency.Default.HasPickUpCashToPlayer(this.AgencyName) ? "<a href=\"BankToAgency.aspx?typeID=2&stype=2&agencyName=" + Server.UrlEncode(Eval("UserName").ToString()) + "&TrueName=" + Server.UrlEncode(Eval("NickName").ToString()) + "&url=" + Utility.Common.CurrentPageUrl + "\">提钻石</a>&nbsp;|&nbsp;" : ""%>
                 <%--                       <%# (int)Eval("Disabled") == 0 ? "<a href='MyDownPlayer.aspx?action=taboo&taboo=1&userid=" + Eval("UserID").ToString() + "&url=" + Utility.Common.CurrentPageUrl + "'>禁用帐号</a>" : "禁用帐号"%>--%>
                                         <a href="<%# "MyDownPlayer.aspx?action=taboo&userid=" + Eval("UserID")+ "&taboo="+ Eval("Disabled") + "&url="+Utility.Common.CurrentPageUrl%>"><%# Convert.ToInt32(Eval("Disabled")) == 0 ? "禁用帐号" : "启用帐号"%></a>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                        <asp:Label ID="lbNonData" runat="server" Text="<tr><td colspan='6'>没有记录！</td></tr>"
                            Visible="false"></asp:Label>
                        <tr>
                            <td colspan="7" align="left" style=" padding:5px;">
                                直属玩家的金币总计为：<asp:Label ID="lab_sum" runat="server" Text="0"></asp:Label>
                                &nbsp;|&nbsp;
                                钻石总计为：<asp:Label ID="LabJewels" runat="server" Text="0"></asp:Label>
                            </td>
                        </tr>
                    </table>
                    <table width="100%">
                        <tr>
                            <td colspan="2" style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
                                <webdiyer:AspNetPager PageSize="15" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                    FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                                    PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                                    ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                                    AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
                                </webdiyer:AspNetPager>
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
