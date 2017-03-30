<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PayList.aspx.cs" Inherits="Bzw.Web.Analy.Records2.PayList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagPrefix="Bzw" TagName="Top" Src="~/Analy/Top.ascx" %>
<%@ Register TagPrefix="Bzw" TagName="Nav" Src="~/Analy/Navigations.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <script type="text/javascript">
        var ActionUrl = "/Analy/User/PlayerDetail.aspx"; //定义本页的信息编辑页地址
        var Target = "_blank"; //定义信息编辑页打开方式，_self表示在当前页打开，即浮动出一个信息编辑页面层来。_blank表示在新页面打开
        var DialogWidth = 500; //定义浮动层的宽度，仅在Target="_self"时有效
        var DialogHeight = 300; //定义浮动层的高度，仅在Target="_self"时有效
    </script>
    <script type="text/javascript" src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
    <link href="/Analy/Images/analy/analy.css" type="text/css" rel="Stylesheet" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
    <script type="text/javascript" src="/Public/Js/analy.js"></script>
</head>
<body>
    <form id="form1" runat="server">
    <Bzw:Top runat="server" ID="top1" EnableViewState="false" />
    <div id="content">
        <Bzw:Nav runat="server" ID="nav1" EnableViewState="false" />
        <div class="datalist">
            <div class="action" style="width: 50%;">
                <span onclick="ExportPage();">导出所选</span> <span onclick="Export();">导出全部</span><%if (!string.IsNullOrEmpty(HN.Common.CommonManager.Web.Request("reurl", "").Trim()))
                                                                                                 {%>
                <span onclick="LocationTo(decodeURIComponent(GetRequest('reurl','OnlineUser_Date.aspx')));">
                    返回</span>
                <%} %>
            </div>
            点卡充值总额：<asp:Label ID="lblCardPayCount" runat="server"></asp:Label>&nbsp;&nbsp;&nbsp;&nbsp;网银充值总额：<asp:Label
                ID="lblNetPayCount" runat="server"></asp:Label>&nbsp;&nbsp;&nbsp;&nbsp;总金额：<asp:Label
                    ID="lblTotal" runat="server"></asp:Label>
            <div class="search" style="width: auto;">
                &nbsp;&nbsp;<input type="text" name="txtUserName" id="txtUserName" />&nbsp;&nbsp;<input
                    type="text" name="txtUserID" id="txtUserID" />&nbsp;&nbsp;日期：<input type="text" name="txtBeginDate"
                        id="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" />&nbsp;&nbsp;
                到<input type="text" name="txtEndDate" id="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" />&nbsp;&nbsp;<span
                    onclick="OnSearch()">搜索</span>&nbsp;&nbsp;<span onclick="RefreshMe();">刷新</span>
                <script type="text/javascript">
                    var bd = $("#txtBeginDate");
                    var ed = $("#txtEndDate");
                    var un = $("#txtUserName");
                    var uid = $("#txtUserID");

                    var ukey = "请输入用户名";
                    var okey = "请输入玩家ID号";

                    bd.val(decodeURIComponent(GetRequest("bd", "")));
                    ed.val(decodeURIComponent(GetRequest("ed", "")));
                    var uval = decodeURIComponent(GetRequest("un", ""));
                    var oval = decodeURIComponent(GetRequest("uid", ""));

                    if (uval != "") {
                        un.val(uval);
                        un.css("color", "black");
                    }
                    else {
                        un.val(ukey);
                        un.css("color", "gray");
                    }
                    if (oval != "") {
                        uid.val(oval);
                        uid.css("color", "black");
                    }
                    else {
                        uid.val(okey);
                        uid.css("color", "gray");
                    }
                    un.focus(
								function () {
								    if (un.val().Trim() == ukey) {
								        un.val("");
								        un.css("color", "black");
								    }
								}
							);
                    un.blur(
								function () {
								    if (un.val().Trim() == "") {
								        un.val(ukey);
								        un.css("color", "gray");
								    }
								}
							);

                    uid.focus(
								function () {
								    if (uid.val().Trim() == okey) {
								        uid.val("");
								        uid.css("color", "black");
								    }
								}
							);
                    uid.blur(
								function () {
								    if (uid.val().Trim() == "") {
								        uid.val(okey);
								        uid.css("color", "gray");
								    }
								}
							);

                    function OnSearch() {
                        var url = location.pathname;
                        if ((bd.val().Trim() == "" || ed.val().Trim() == "") && (un.val().Trim() == "" || un.val().Trim() == ukey) && (uid.val().Trim() == "" || uid.val().Trim() == okey)) {
                            Msg("请输入搜索条件", 200);
                            return;
                        }
                        url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
                        url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));
                        if (un.val().Trim() != "" && un.val().Trim() != ukey) {
                            url = SetUrlParam(url, "un=" + encodeURIComponent(un.val().Trim()));
                        }
                        if (uid.val().Trim() != "" && uid.val().Trim() != okey) {
                            url = SetUrlParam(url, "uid=" + encodeURIComponent(uid.val().Trim()));
                        }
                        LocationTo(url);
                    }
                    function Clear() {
                        $("input[type='text']").val("");
                    }
                </script>
            </div>
            <div class="clear">
            </div>
            <table id="tbContent">
                <tr>
                    <th>
                        <input type="checkbox" name="cbxAll" id="cbxAll" value="all" />
                    </th>
                    <th>
                        序号
                    </th>
                    <th axis="OrderIDOrNum">
                        订单号/点卡号
                    </th>
                    <th axis="UserID">
                        玩家ID
                    </th>
                    <th axis="UserName">
                        玩家账号
                    </th>
                    <th axis="AgencyName">
                        所属代理商
                    </th>
                    <th axis="PayMoney">
                        充值金额
                    </th>
                    <th axis="AddTime">
                        充值时间
                    </th>
                    <th axis="PayType">
                        充值类型
                    </th>
                </tr>
                <tbody id="tbdDataList">
                    <asp:Repeater runat="server" ID="rptDataList">
                        <ItemTemplate>
                            <tr>
                                <td align="center">
                                    <%# "<input type='checkbox' name='cbxData' id='cbx_" + Container.ItemIndex.ToString() + "' value='" + Eval( "UserID" ).ToString() + "' />"%>
                                </td>
                                <td align="center">
                                    <%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
                                </td>
                                <td align="center">
                                    <%# Eval( "PayType" ).ToString() == "1" ? "<span style='color:red;'>" + Eval( "OrderIDOrNum" ).ToString() + "点卡号</red>" : Eval( "OrderIDOrNum" ).ToString()%>
                                </td>
                                <td align="center">
                                    <%# Eval( "UserID" ).ToString()%>
                                </td>
                                <td align="center">
                                    <%# Eval( "UserName" ).ToString()%>
                                </td>
                                <td align="center">
                                    <%# Eval( "AgencyName" ).ToString()%>
                                </td>
                                <td align="center">
                                    <%--已经除过100--%>
                                    <%# Eval( "PayMoney" ).ToString()%>
                                </td>
                                <td align="center">
                                    <%# Eval( "AddTime","{0:yyyy-MM-dd HH:mm:ss}" )%>
                                </td>
                                <td align="center">
                                    <%# Eval( "PayType" ).ToString()=="1"?"<span style='color:red;'>点卡</red>":"网银"%>
                                </td>
                            </tr>
                        </ItemTemplate>
                    </asp:Repeater>
                    <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>还没有任何数据。</td></tr>"></asp:Literal></tbody></table>
            <div class="pager">
                <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="共%PageCount%页，当前第%CurrentPageIndex%页，每页%PageSize%条，共%RecordCount%条。"
                    FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                    PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                    SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True"
                    PageSize="20">
                </webdiyer:AspNetPager>
            </div>
            <div class="clear">
            </div>
        </div>
    </div>
    </form>
</body>
</html>
