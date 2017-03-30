<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DownPlayerPayList.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.DownPlayerPayList" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>我的游戏玩家</title>

    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>

</head>
<body>
    <form id="form1" runat="server">
        <div style="text-align: center; font-size: 13px;">
            <font size="4"><b>代理商<span style="color: Red"><%=UiCommon.AgencyLoginInfo.AgencyName%></span>直属玩家的充值记录</b></font>
        </div>
        <div style="text-align: center; font-size: 13px;">
            <table border="1px;" cellpadding="3" style="width: 80%; border-collapse: collapse;
                margin: 0;">
                <tr>
                    <td align="left">
                        玩家账号：<input maxlength="30" type="text" id="txtKey" name="txtKey" />&nbsp;玩家ID：<input maxlength="5" type="text" id="txtUserID" name="txtUserID" />&nbsp;<select id="selPayType" name="selPayType" onchange="OnTypeSelected(this);">
						<option value="none">=按充值类型=</option>
						<option value="0">网银</option>
						<option value="1">点卡</option>
					</select><br />充值时间从：<input type="text" id="txtBeginDate" class="put" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});"/>&nbsp; 到：<input type="text" id="txtEndDate" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;
                        <input type="button" value="搜索" onclick="OnSearch();" />&nbsp;
                        <input type="button" value="刷新" onclick="RefreshMe();" />

                        <script>
                            var bd = $("#txtBeginDate");
                            var ed = $("#txtEndDate");
                            var o = $("#txtKey");
                            var u = $("#txtUserID");
                            var pkey = "请输入玩家账号";
                            var ukey = "请输入玩家id";

                            bd.val(decodeURIComponent(GetRequest("bd", "")));
                            ed.val(decodeURIComponent(GetRequest("ed", "")));
                            o.val(decodeURIComponent(GetRequest("key", pkey)));
                            u.val(decodeURIComponent(GetRequest("uid", ukey)));
                            DropSetByValue("selPayType", GetRequest("type", "none"));

                            if (GetRequest("key", "") == "") {
                                o.css("color", "gray");
                            }
                            else {
                                o.css("color", "black")
                            }
                            o.focus(function () { if (o.val().Trim() == pkey) { o.css("color", "black"); o.val(""); } });
                            o.blur(function () { if (o.val().Trim() == "") { o.css("color", "gray"); o.val(pkey); } });


                            if (GetRequest("uid", "") == "") {
                                u.css("color", "gray");
                            }
                            else {
                                u.css("color", "black")
                            }
                            u.focus(function () { if (u.val().Trim() == ukey) { u.css("color", "black"); u.val(""); } });
                            u.blur(function () { if (u.val().Trim() == "") { u.css("color", "gray"); u.val(ukey); } });

                            //搜索按钮
                            function OnSearch() {
                                if (bd.val().Trim() != "" || ed.val().Trim() != "" || (o.val().Trim() != pkey && o.val().Trim() != "") || (u.val().Trim() != ukey && u.val().Trim() != "")) {
                                    var url = SetUrlParam(location.href, "key=" + ((o.val().Trim() != pkey && o.val().Trim() != "") ? encodeURIComponent(o.val().Trim()) : ""));
                                    url = SetUrlParam(url, "uid=" + ((u.val().Trim() != ukey && u.val().Trim() != "") ? encodeURIComponent(u.val().Trim()) : ""));
                                    url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
                                    LocationTo(SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim())));
                                    return;
                                }
                                alert("请先输入您要搜索的玩家ID或玩家账号，或选择要查看的时段。");
                            }

                            //按类型搜索事件
                            function OnTypeSelected(obj) {
                                var value = obj.options[obj.selectedIndex].value;
                                if (value == "none") {
                                    RefreshMeDelParam("(&)?type=(\\d+)");
                                }
                                else {
                                    LocationToMeParam("type=" + value);
                                }
                            }							
					</script>


                    </td>
                </tr>
                <tr>
                    <td align="left"  style=" padding:5px;">
                     
                    <span runat="server" id="span_Rs"></span>
                        <%--点卡充值的总金额：<%=CardPayMoney %>元/<%=CardPayMoneyCount %>条，网银充值的总金额：<%=NetPayMoney %>元/<%=NetPayMoneyCount %>条，总的充值金额：<%=TotalMoney%>元/<%=TotalMoneyCount%>条。--%>
                       </td>
                </tr>
                <tr>
                    <td>
                        <table style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px;
                            padding: 0px;" border="1px;" id="TABLE1">
                            <tr>
                                <th>
                                    序号</th>
                                <th>
                                    订单号/点卡号</th>
                                <th>
                                    玩家ID</th>
                                <th>
                                    玩家账号</th>
                                <th>
                                    充值金额</th>
                                <th>
                                    充值时间</th>
                                <th>
                                    充值类型</th>
                                <th>
                                    状态</th>

                            </tr>
                            <asp:Repeater ID="rptDataList" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            <%# ( Container.ItemIndex + 1 ) + anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) %>
                                        </td>
                                        <td>
                                            <%#Convert.ToInt32(Eval("PayType")) == 1 ?"<font color='red'>"+Eval("OrderIDOrNum").ToString() + "(点卡号)</font>" : Eval("OrderIDOrNum").ToString() + "(订单号)"%>
                                        </td>
                                        <td>
                                            <%# Eval("UserID")%>
                                        </td>
                                        <td>
                                            <%# Eval("UserName")%>
                                        </td>
                                        <td>
                                            <%# Convert.ToInt32(Eval("PayType")) == 1 ? Eval("PayMoney") :UiCommon.StringConfig.MoneyChu100(Eval("PayMoney"))%>
                                        </td>
                                        <td>
                                            <%# Eval("AddTime")%>
                                        </td>
                                        <td>
                                         
                                            <%# Convert.ToInt32(Eval("PayType").ToString())==0?"网银":"点卡"%>
                                        </td>
                                        <td>
                                            <%# Convert.ToInt32(Eval("PaySuccess")) == 0 ? "未支付" : Convert.ToInt32(Eval("PaySuccess")) == 1 ? "<font color='blue'>已支付</font>" : "<font color='blue'>已充值</font>"%>
                                        </td>
                                    </tr>
                                </ItemTemplate>
                            </asp:Repeater>
                            <asp:Label ID="lbNonData" runat="server" Text="<tr><td colspan='10'>没有记录！</td></tr>"
                                Visible="false"></asp:Label></table>
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
